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
}

