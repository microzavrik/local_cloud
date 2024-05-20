#include "session.hpp"

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
                    std::cout << "Type: " << data_[0] << std::endl;
                    current_type_station = types::char_to_rectype(data_[0]);
                    std::string message(data_, length);
                    std::cout << "Received: " << message << std::endl;

                    switch(current_type_station)
                    {
                        case types::received_type::text:
                            std::cout << "Its text: " << message << std::endl;
                            break;
                        case types::received_type::file:
                            std::cout << "Its file: " << message << std::endl;
                            break;
                        case types::received_type::video:
                            std::cout << "Its video: " << message << std::endl;
                            break;
                        case types::received_type::photo:
                            std::cout << "Its photo: " << message << std::endl;
                            break;
                        case types::received_type::json:
                            std::cout << "Its json: " << message << std::endl;
                            break;
                        default:
                            std::cout << "None Type" << std::endl; 
                    }

                    do_write(length);
                }
                else
                {

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

                }
            });
    }
}
