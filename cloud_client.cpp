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
                    start_listening();
                }
            });
    }
    
    void cloud_client::send_message(const std::string& message)
    {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }

    void cloud_client::send_file(const std::string& file_path)
    {
        std::ifstream file(file_path, std::ios::binary);
        if(!file.is_open())
        {
            std::cerr << "Failed to open file: " << file_path << std::endl;
            return;
        }

        const size_t chunk_size = 2048; // Define chunk size
        std::vector<char> buffer(chunk_size);

        while (!file.eof())
        {
            file.read(buffer.data(), chunk_size);
            size_t bytes_read = file.gcount();

            if (bytes_read > 0)
            {
                boost::asio::write(socket_, boost::asio::buffer(buffer.data(), bytes_read));
            }
        }

        std::cout << "File sent in parts: " << file_path << std::endl;
    }

}
