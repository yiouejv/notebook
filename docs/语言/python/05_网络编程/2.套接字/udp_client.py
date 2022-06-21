from socket import *
import sys

sockfd = socket(AF_INET, SOCK_DGRAM)
while True:
    mess = bytes(input('发送>>'), encoding='utf-8')
    sockfd.sendto(mess, ('127.0.0.1', 8888))
    data, addr = sockfd.recvfrom(1024)
    print('客户端收到消息:', data.decode(encoding='utf-8'))

sockfd.close()
