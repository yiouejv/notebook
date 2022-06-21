from socket import *
from select import *
# 创建套接字
sockfd = socket(AF_INET, SOCK_STREAM)
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind(('0.0.0.0', 8888))
sockfd.listen(10)
# 创建io字典
fdmap = {
    sockfd.fileno() : sockfd
}

# 创建poll对象
p = poll()
p.register(sockfd, POLLIN | POLLERR)

while True:
    # 进行IO监控
    events = p.poll()
    for fd, event in events:
        if fd == sockfd.fileno():  # 如果是客户端链接
            connfd, addr = fdmap[fd].accept()
            print('Connect from', addr)
            p.register(connfd, POLLIN | POLLHUP)
            fdmap[connfd.fileno()] = connfd
        elif event == POLLIN:  # 如果是客户端消息交互
            data = fdmap[fd].recv(1024).decode()
            print(data)
            # 客户端退出, 移除关注事件, 维护字典
            if not data:
                p.unregister(fd)  # 填对象或文件描述符
                del fdmap[fd]
            else:
                fdmap[fd].send(b'Receive')

