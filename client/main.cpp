#include "cloud_client.hpp"
#include "get_file_size_in_bytes.hpp"

int main()
{
    boost::asio::io_context ios;
    network::cloud_client client(ios, "127.0.0.1", "8080");
    client.start_listening();

    std::size_t size = get_file_size_in_bytes("file.txt");
    if (size != static_cast<std::size_t>(-1))
    {
        std::string size_str = std::to_string(size);
        std::string message_str = "file|txt|" + size_str;
        std::cout << "Send message: " << message_str << std::endl;
        client.send_message(message_str);
        client.send_file("file.txt");
    }
    else
    {
        std::cerr << "Failed to get file size." << std::endl;
    }

    ios.run();

    return 0;
}
