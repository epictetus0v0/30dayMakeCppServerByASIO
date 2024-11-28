#include "../dependency/asio.hpp"
#include <iostream>
#include <cstring>

int main()
{
    asio::io_context context;
    asio::ip::tcp::socket socket(context);
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 8888);
    socket.connect(ep);

    std::cerr << "client: hello world!" << std::endl;
    // std::string buff;
    char buff[1024];
    asio::async_read(socket, asio::buffer(buff, 1024), 
        [&buff](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cerr << "recieve len:" << length << "," << buff << std::endl;
            }
            else
            {
                std::cerr << "async_read error" << std::endl;
            }
        }
    );

    context.run();

    return 0;
}