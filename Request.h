#ifndef REQUEST_H_
#define REQUEST_H_ 1

#include "Header.h"

#include <string>
#include <vector>

struct Request
{
   std::string method;
   std::string uri;
   int http_version_major;
   int http_version_minor;
   std::vector<Header> headers;
};

#endif
