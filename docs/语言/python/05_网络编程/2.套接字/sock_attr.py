from socket import *
import sys

sockfd = socket(AF_INET, SOCK_STREAM)

# 获取套接字打地址族类型
print(sockfd.family)

# 获取套接字打类型
print(sockfd.type)

sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, True)
sockfd.bind(('0.0.0.0', 10003))

print(sockfd.getsockopt(SOL_SOCKET, SO_REUSEADDR))
# 获取套接字的绑定地址
print(sockfd.getsockname())

print(sockfd.fileno())

print(sys.stdin.fileno())

sockfd.listen(10)
print('等待链接...')
connfd, addr = sockfd.accept()
print(connfd.getpeername())
data = connfd.recv(1024).decode(encoding='utf-8')
print(data)





for i in dir(sockfd):
    # print(i)
    pass


