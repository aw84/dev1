#include "Server.h"

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

server::server(std::size_t thread_pool_size)
   : thread_pool_size(thread_pool_size),
   signals(io_service),
   acceptor(io_service),
   new_connection(),
   request_handler("/")
{
   signals.add(SIGTERM);
   signals.add(SIGINT);
   signals.async_wait(boost::bind(&server::handle_stop, this));

   boost::asio::ip::tcp::resolver resolver(io_service);
   std::string address="0.0.0.0";
   std::string port="8833";
   boost::asio::ip::tcp::resolver::query query(address, port);
   boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

   acceptor.open(endpoint.protocol());
   acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
   acceptor.bind(endpoint);
   acceptor.listen();

   start_accept();
}

void server::run()
{
   std::vector<boost::shared_ptr<boost::thread> > threads;
   for(std::size_t i=0; i<thread_pool_size; i++) {
      boost::shared_ptr<boost::thread> thread(
         new boost::thread(
            boost::bind(
               &boost::asio::io_service::run, &io_service)));
         threads.push_back(thread);
   }

   for(std::size_t i=0; i<thread_pool_size; i++) {
      threads[i]->join();
   }
}

void server::start_accept()
{
   new_connection.reset(
      new Connection(io_service, request_handler));

   acceptor.async_accept(new_connection->socket(),
      boost::bind(
         &server::handle_accept, this, boost::asio::placeholders::error));
}

void server::handle_accept(const boost::system::error_code& e)
{
   if (!e) {
      new_connection->start();
   }

   start_accept();
}

void server::handle_stop()
{
   io_service.stop();
}
