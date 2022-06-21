from socket import *
sockfd = socket(AF_INET, SOCK_DGRAM)
sockfd.bind(('0.0.0.0', 8888))
print('等待连接...')
while True:
    data, addr = sockfd.recvfrom(1024)
    print('来自%s的消息:%s' % (addr, data.decode(encoding='utf-8')))
    sockfd.sendto('已经收到消息'.encode(), addr)

sockfd.close()
