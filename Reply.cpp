#include "Reply.h"

#include <boost/lexical_cast.hpp>

#include <string>

namespace status_strings
{
const std::string ok="HTTP/1.0 200 OK\r\n";
const std::string internal_server_error = "HTTP/1.0 500 Internal Server Error\r\n";

boost::asio::const_buffer to_buffer(Reply::status_type status)
{
   switch(status) {
   case Reply::ok:
      return boost::asio::buffer(ok);
   }
   return boost::asio::buffer(internal_server_error);
}
}

std::vector<boost::asio::const_buffer> Reply::to_buffers()
{
   std::vector<boost::asio::const_buffer> buffers;
   buffers.push_back(status_strings::to_buffer(status));
   for (std::size_t i=0; i< headers.size(); ++i) {
      Header& h = headers[i];
      buffers.push_back(boost::asio::buffer(h.name));
      buffers.push_back(boost::asio::buffer(h.value));
   }
   buffers.push_back(boost::asio::buffer(content));
   return buffers;
}

namespace stock_replies
{
const char ok[] = "";
const char internal_server_error[] = "500 Internal Server Error";
std::string to_string(Reply::status_type status)
{
   switch(status) {
   case Reply::ok:
      return ok;
   }

   return internal_server_error;
}
}//namespace stock_replies

Reply Reply::stock_reply(Reply::status_type status)
{
   Reply rep;
   rep.status = status;
   rep.content = stock_replies::to_string(status);
   rep.headers.resize(2);
   rep.headers[0].name = "Content-Length:";
   rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
   rep.headers[1].name = "Content-Type:";
   rep.headers[1].value = "text/html";
   return rep;
}

