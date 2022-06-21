from socket import *

# 创建本地套接字
sockfd = socket(AF_UNIX, SOCK_STREAM)
# 链接另一端
sockfd.connect('sock_file')
# 消息收发
while True:
    send_data = input('>>').encode()
    sockfd.send(send_data)
    data = sockfd.recv(1024).decode()
    print(data)

sockfd.close()
