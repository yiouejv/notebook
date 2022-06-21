# encoding: utf-8
from socket import *
import os, sys
from signal import *


# 创建套接字
HOST = ""
PORT = 8888
sockfd = socket()
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind((HOST, PORT))
sockfd.listen(10)
# 等待客户端链接
print('进程%d等待客户端链接' % os.getpid())
# 在父进程中忽略子进程状态改变，子进程退出自动由系统处理
signal(SIGCHLD, SIG_IGN)


def client_handler(c):
    '''客户端处理函数'''
    print('处理子进程的请求', c.getpeername())
    try:
        while True:
            data = c.recv(1024)
            if not data:
                break
            print(data)
            c.send('收到客户端请求'.encode())
    except (KeyboardInterrupt, SystemError):
        sys.exit('客户端退出')
    except Exception as err:
        print(err)
    c.close()


while True:
    try:
        connfd, addr = sockfd.accept()
    except KeyboardInterrupt as err:
        sys.exit('服务器退出')
    except Exception as e:
        print('Error:', e)
        continue
    #　为客户端创建新的进程处理请求
    pid = os.fork()
    # 子进程处理
    if pid == 0:
        # 子进程服务器套接字没用
        sockfd.close()
        client_handler(connfd)
        sys.exit()
    # 父进程或者创建失败都继续等待下个客户端链接
    else:
        # 父进程链接套接字没用
        connfd.close()
        continue



