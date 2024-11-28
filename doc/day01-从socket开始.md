# day01-从asio::ip::tcp::socket开始

socket套接字是网络通信中最基础的单元，是网络io的接入口，也是我们首要的切入点。

不同于linux系统调用的int类型简单描述，由于丰富的设计，asio中套接字的构造要复杂得多。以最常用的tcp长连接为例：

```c++
#include "asio/ip/tcp.hpp"
...
typedef basic_stream_socket<tcp> socket;
...    

```

```c++
#include "asio/basic_stream_socket.hpp"
...
template <typename Protocol, typename Executor>
...
class basic_stream_socket
 : public basic_socket<Protocol, Executor>
{
...
  typedef Executor executor_type;
...
  explicit basic_socket(const executor_type& ex)
    : impl_(0, ex)
  {
  }
...
```

```c++
#include "asio/basic_socket.hpp"
... 
// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = any_io_executor>
class basic_socket;
...
```

asio里所有的套接字均实例化自模板类asio::basic_stream_socket，该模板类又继承自asio::basic_socket，这两个socket模板基类均有两个类型参数，第一个为支持的协议，即tcp；第二个实际上是源自asio::basic_socket声明时的默认参数any_io_executor。事实上，Executor的概念相当复杂，我们姑且认为这是asio进行任务调度的方法。

在这里我们简单构造一个asio::ip::tcp::socket实例：

```c++
#include "asio.hpp" // asio为head only库，该文件为统一的include入口
asio::io_context context;
asio::ip::tcp::socket socket(context);
```

asio::io_context是asio中任务调度运行的基本上下文环境，这里创建了一个受context调度的socket套接字。**对于客户端**，需要将服务器的端点数据绑定至客户端socket上，在asio中，asio::ip::tcp::endpoint用于表示一个网络端点，socket能调用connect方法直接建立tcp连接。

```c++
asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 8888);
socket.connect(ep);
```

尽管构造时相对复杂，作为客户端asio::ip::tcp::socket建立连接非常简洁，封装隐藏了socket系统调用的基本配置。**对于服务端**，asio封装了asio::ip::tcp::acceptor类，统一承担监听任务。

```c++
asio::io_context context;
size_t port = 8888;
asio::ip::tcp::acceptor acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
acceptor.async_accept(
    [](std::error_code ec, asio::ip::tcp::socket socket)
    {
        if(!ec)
        {
            // 监听到socket连接
            socket.send("this is server!");
            socket.close();
        }
        else
        {
            std::cerr << ec.value() << std::endl;
        }
    }
);
```





