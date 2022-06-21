import gevent
import time

from gevent import monkey
monkey.patch_all()

from socket import *
from time import sleep


def server(port):
    s = socket()
    s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    s.bind(('0.0.0.0', port))
    s.listen(10)
    while True:
        c, addr = s.accept()
        print('Connect from', addr)
        # handler(c)  # 循环服务器
        gevent.spawn(handler, c)  # 协程服务器


def handler(c):
    while True:
        data = c.recv(1024)
        if not data:
            break
        print(data.decode())
        c.send(time.ctime().encode())
    c.close()


if __name__ == '__main__':
    server(8888)