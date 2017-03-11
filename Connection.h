#ifndef CONNECTION_
#define CONNECTION_ 1

#include "Reply.h"
#include "Request.h"
#include "RequestHandler.h"
#include "RequestParser.h"

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class Connection : public boost::enable_shared_from_this<Connection>, private boost::noncopyable
{
public:
   explicit Connection(boost::asio::io_service& io_service, RequestHandler& handler);
   boost::asio::ip::tcp::socket& socket();

   void start();

private:
   void handle_read(const boost::system::error_code& ec, std::size_t bytes_transfered);
   void handle_write(const boost::system::error_code& ec);
   boost::asio::io_service::strand starnd;
   boost::asio::ip::tcp::socket socket_;
   RequestHandler& request_handler;
   boost::array<char, 8192> buffer;
   Request request;
   RequestParser request_parser;
   Reply reply;
};

typedef boost::shared_ptr<Connection> ConnectionPtr;

#endif
