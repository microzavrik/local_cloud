#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>
#include <boost/asio.hpp>

#include "received_type.hpp"

namespace network
{
    class session : public std::enable_shared_from_this<session>
    {
    public:
        session(boost::asio::ip::tcp::socket socket);
        void start();
    private:
        void do_read();
        void do_write(size_t length);
    private:
        boost::asio::ip::tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];

        types::received_type current_type_station = types::received_type::none;
    };
}

#endif