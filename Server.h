#ifndef SERVER_H_
#define SERVER_H_ 1

#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "Connection.h"
#include "RequestHandler.h"


class server : private boost::noncopyable
{
public:
   explicit server(std::size_t thread_pool_size);
   void run();
private:
   void start_accept();
   void handle_accept(const boost::system::error_code& e);
   void handle_stop();

   std::size_t thread_pool_size;
   boost::asio::io_service io_service;
   boost::asio::signal_set signals;
   boost::asio::ip::tcp::acceptor acceptor;
   ConnectionPtr new_connection;
   RequestHandler request_handler;
};

#endif
