#include "cloud_server.hpp"
#include <boost/asio.hpp>
#include <thread>

int main()
{
    try
    {
        boost::asio::io_context ios;
        network::cloud_server* server = new network::cloud_server(ios, 8080);
        
        std::thread t([&]()
        {
            ios.run();
        });

        ios.run();
        t.join();

        delete server; // Освобождаем память после завершения работы сервера
    }
    catch(std::exception& ex) 
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
