//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "asio.hpp"

using asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    asio::io_service io_service;

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    asio::connect(s, resolver.resolve({argv[1], argv[2]}));

    
    char request[max_length];
    size_t request_length = std::strlen(request);
    asio::write(s, asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = asio::read(s,
        asio::buffer(reply, request_length));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
