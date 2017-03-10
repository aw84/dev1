#ifndef REQUEST_HANDLER_
#define REQUEST_HANDLER_ 1

#include <boost/noncopyable.hpp>

#include <string>

struct request;
struct reply;

class RequestHandler : private boost::noncopyable
{
public:
   explicit RequestHandler(const std::string& doc_root);
   void handle_request(const request& req, reply& rep);
private:
   std::string doc_root;
   static bool url_decode(const std::string& in, std::string& out);
};

#endif
