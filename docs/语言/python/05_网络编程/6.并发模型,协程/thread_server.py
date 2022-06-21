# encoding: utf-8
from socket import *
import os, sys
from threading import *
import traceback


HOST="0.0.0.0"
PORT = 9999
ADDR = (HOST, PORT)

sockfd = socket()
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind(ADDR)
sockfd.listen(10)


# 客户端处理请求
def hanlder(connfd):
    print('Connetc from', connfd.getpeername())
    while True:
        data = connfd.recv(1024)
        if not data:
            break
        print(data.decode())
        connfd.send(b'Receive request')
    connfd.close()


# 等待客户端请求
while True:
    try:
        print('Server listen port %s...' % PORT)
        connfd, addr = sockfd.accept()
    except KeyboardInterrupt:
        sockfd.close()
        sys.exit('服务器退出')
    except Exception as e:
        traceback.print_exc()
        continue

    t = Thread(target=hanlder, args=(connfd,))
    t.setDaemon(True)
    t.start()





