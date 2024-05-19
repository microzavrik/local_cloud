#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>
#include <boost/asio.hpp>

#include "received_type.hpp"
#include "log.hpp"

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
        enum { max_length = 2048 };
        char data_[max_length];

        bool file_received_mode {false};
        std::string file_received_extension;
        std::string file_received_name;
        std::string name_file_saved;
        uint64_t file_received_size = 0;
        uint64_t received_bytes = 0;

        types::received_type current_type_station = types::received_type::none;
    };
}

#endif