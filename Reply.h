#ifndef REPLY_H_
#define REPLY_H_ 1

#include "Header.h"

#include <boost/asio.hpp>

#include <string>
#include <vector>

struct Reply
{
   enum status_type {
      ok = 200
   } status;

   std::vector<Header> headers;

   std::string content;

   std::vector<boost::asio::const_buffer> to_buffers();

   static Reply stoc_reply(status_type status);
};

#endif
