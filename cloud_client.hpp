#ifndef CLOUD_CLIENT_HPP
#define CLOUD_CLIENT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <boost/asio.hpp>

namespace network
{
    class cloud_client
    {
    public:
        cloud_client(boost::asio::io_context& ios, const std::string& server_ip, 
            const std::string& server_port);
        void start_listening();
        void send_message(const std::string& message);
        void send_file(const std::string& file_path);
    private:
        boost::asio::ip::tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
    };
}

#endif