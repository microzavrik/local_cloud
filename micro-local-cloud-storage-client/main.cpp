#include "cloud_client.hpp"

int main()
{
    boost::asio::io_context ios;
    network::cloud_client client(ios, "127.0.0.1", "8080");
    client.start_listening();
    client.send_message("thellso");
    ios.run();

    return 0;
}