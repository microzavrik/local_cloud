#ifndef CLOUD_SERVER_HPP
#define CLOUD_SERVER_HPP

#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "session.hpp"
#include "log.hpp"

namespace network
{
    class cloud_server
    {
    public:
        cloud_server(boost::asio::io_context& ios, short port);
    private:
        void do_accept();
    private:
        boost::asio::ip::tcp::acceptor acceptor_;
    };
}

#endif