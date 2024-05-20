#include "cloud_client.hpp"

namespace network
{
    cloud_client::cloud_client(boost::asio::io_context& ios, const std::string& server_ip, 
            const std::string& server_port) : socket_(ios)
    {
        boost::asio::ip::tcp::resolver resolver(ios);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(server_ip, server_port);

        boost::asio::connect(socket_, endpoints);
    }
    
    void cloud_client::start_listening()
    {
        boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length),
            [this](const boost::system::error_code& ec, size_t length)
            {
                if(!ec)
                {
                    std::cout << "Received: " << data_ << std::endl;
                    start_listening();
                }
            });
    }
    
    void cloud_client::send_message(const std::string& message)
    {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }
}