from select import select
from socket import *

# 创建套接字作为关注的IO
sockfd = socket()
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind(('0.0.0.0', 8888))
sockfd.listen(10)

rlist = [sockfd]
wlist = []
xlist = [sockfd]

while True:
    # 提交监测我们关注的IO, 阻塞等待IO发生
    rs, ws, xs = select(rlist, wlist, xlist)
    for r in rs:
        if r is sockfd:
            connfd, addr = sockfd.accept()
            rlist.append(connfd)  # 将对象添加到关注列表
            print('Connect from', addr)
        else:  # 如果不是sockfd, 则是connfd
            data = r.recv(1024).decode()
            if data in ('\r\n', '\n'):
                rlist.remove(r)
                r.send('关闭')
                r.close()
            else:
                print(data.encode())
                wlist.append(r)
                r.send(b'Receive your message')

    for w in ws:
        pass
    for x in xs:
        if x is sockfd:
            sockfd.close()









