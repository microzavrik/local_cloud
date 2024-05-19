#include "cloud_server.hpp"

namespace network
{
    cloud_server::cloud_server(boost::asio::io_context& ios, short port)
        : acceptor_(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        logger::logInfo("Started server");

        do_accept();
    }

    void cloud_server::do_accept() {
        acceptor_.async_accept(
            [this](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    logger::logInfo("Connected new user");
                    std::make_shared<session>(std::move(socket))->start();
                }

                do_accept();
            });
    }
}
