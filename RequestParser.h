#ifndef REQUEST_PARSER_H_
#define REQUEST_PARSER_H_ 1

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

struct Request;

class RequestParser
{
public:
   RequestParser();
   void reset();
   template <typename InputIterator>
   boost::tuple<boost::tribool, InputIterator> parse(Request& request, InputIterator begin, InputIterator end)
   {
      while(begin != end) {
         boost::tribool result = consume(request, *begin++);
         if (result || !result) {
            return boost::make_tuple(result, begin);
         }
      }
      boost::tribool result = boost::indeterminate;
      return boost::make_tuple(result, begin);
   }
private:
   boost::tribool consume(Request& request, char input);
   static bool is_char(int c);
   static bool is_ctl(int c);
   static bool is_tspecial(int c);
   static bool is_digit(int c);

   enum state {
      method_start,
      method,
      uri
   } state_;
};

#endif
