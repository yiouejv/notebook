from socket import *
import os

# 确定套接字文件
sock_file = 'sock_file'
# 判断文件是否已经存在
if os.path.exists(sock_file):  # 存在删除
    os.remove(sock_file)
# 创建本地套接字
sockfd = socket(AF_UNIX, SOCK_STREAM)
# 绑定套接字文件
sockfd.bind(sock_file)
# 监听
sockfd.listen(10)
# 等待消息收发
while True:
    print('等待链接...')
    connfd, addr = sockfd.accept()
    print(addr, '已链接')
    # 消息收发
    while True:
        data = connfd.recv(1024).decode()
        print(data)
        connfd.send(b'Receive')
    connfd.close()
sockfd.close()


