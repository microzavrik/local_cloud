#include "session.hpp"
#include <fstream>

namespace network
{
    session::session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket))
    {
    }

    void session::start()
    {
        do_read();
    }

    void session::do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](const boost::system::error_code& ec, size_t length)
            {
                if (!ec)
                {
                    std::string message(data_, length);
                    if(!file_received_mode)
                    {
                        std::cout << "Received: " << message << std::endl;

                        std::vector<std::string> parts;
                        std::stringstream ss(message);
                        std::string part;

                        while(std::getline(ss, part, '|'))
                        {
                            parts.push_back(part);
                        }

                        file_received_name = parts[0];
                        file_received_extension = parts[1];
                        file_received_mode = true;
                        file_received_size = std::stoul(parts[2]);
                        received_bytes = 0;

                        name_file_saved = file_received_name + "." + file_received_extension;

                        std::cout << "[!] Received new file: " << name_file_saved << std::endl;
                        std::cout << "[!] Size: " << file_received_size << std::endl;

                        do_write(length);
                    }
                    else
                    {
                        std::ofstream outfile(name_file_saved, std::ios::binary | std::ios::app);
                        if (outfile.is_open())
                        {
                            outfile.write(message.c_str(), length);
                            outfile.close();
                            received_bytes += length;
                        }
                        else
                        {
                            std::cerr << "Failed to save the received file" << std::endl;
                        }

                        if (length == max_length)
                        {
                            do_read(); // Continue reading next chunk
                        }
                        else
                        {
                            if(received_bytes == file_received_size)
                            {
                                logger::logInfo("Partial file received: " + std::to_string(received_bytes) + "/" + std::to_string(file_received_size) + " bytes");
                                logger::logInfo("File received and saved as '" + name_file_saved + "'");
                                file_received_mode = false;
                            }
                            else
                            {
                                logger::logInfo("Partial file received: " + std::to_string(received_bytes) + "/" + std::to_string(file_received_size) + " bytes");
                            }
                            do_write(length);
                        }
                    }
                }
                else if (ec == boost::asio::error::eof)
                {
                    logger::logInfo("User disconnect");
                }
                else
                {
                    std::cout << "Unknown error" << std::endl;
                }
        });
    }

     void session::do_write(size_t length)
    {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](const boost::system::error_code& ec, size_t /*length*/)
            {
                if (!ec)
                {
                    do_read();
                }
                else
                {
                    // Handle write error
                }
            });
    }
}
