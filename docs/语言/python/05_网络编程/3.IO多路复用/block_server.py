from socket import *
import time
sockfd = socket(AF_INET, SOCK_STREAM)
sockfd.bind(('0.0.0.0', 8888))
sockfd.listen(10)
# 将套接字设置为非阻塞
sockfd.setblocking(False)

while True:
    print('Wait for Connect...')
    try:
        connfd, addr = sockfd.accept()
    except BlockingIOError:
        time.sleep(1)
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

