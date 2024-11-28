#include "../dependency/asio.hpp"
#include <iostream>

int main()
{
    asio::io_context context;
    size_t port = 8888;
    asio::ip::tcp::acceptor acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    acceptor.async_accept(
        [](std::error_code ec, asio::ip::tcp::socket socket)
        {
            if(!ec)
            {
                // 监听到socket连接
                asio::write(socket, asio::buffer("this is server!"));
                // Sleep(10000);
                std::cerr << "send data" << std::endl;
                // socket.close();
            }
            else
            {
                std::cerr << ec.value() << std::endl;
            }
        }
    );
    std::cerr << "server: hello world!" << std::endl;
    context.run();

    return 0;
}