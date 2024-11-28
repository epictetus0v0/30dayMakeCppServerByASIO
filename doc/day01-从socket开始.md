# day01-从socket开始
socket套接字是网络通信中最基础的单元，是网络io的接入口，也是我们首要的切入点。
不同于

```c++
#include "asio/ip/tcp.hpp"
typedef basic_stream_socket<tcp> socket;

#include "asio/basic_stream_socket.hpp"
...
template <typename Protocol, typename Executor>
class basic_stream_socket
 : public basic_socket<Protocol, Executor>
{
...
```