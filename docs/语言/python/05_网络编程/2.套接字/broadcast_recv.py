from socket import *
sockfd = socket(AF_INET, SOCK_DGRAM)

# 设置套接字可以发送接收广播
sockfd.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

# 固定接收端口
sockfd.bind(('0.0.0.0', 9999))

while True:
    try:
        mess, addr = sockfd.recvfrom(1024)
        print('来自{addr}的消息:{mess}'.format(addr=addr, mess=mess.decode(encoding='utf-8')))
    # KeyboardIntertupt, SyntaxError
    except:
        raise

sockfd.close()