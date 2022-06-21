from socket import *
import time
sockfd = socket(AF_INET, SOCK_STREAM)
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind(('0.0.0.0', 8888))
sockfd.listen(10)
# 将套接字设置为超时时间
sockfd.settimeout(5)

while True:
    print('Wait for Connect...')
    try:
        connfd, addr = sockfd.accept()
    except timeout:
        print(time.ctime())
        continue
    else:
        print('Connect from', addr)
        while True:
            data = connfd.recv(1024).decode()
            if not data:
                break
            print(data)
            connfd.send(time.ctime().encode())
        connfd.close()

sockfd.close()

