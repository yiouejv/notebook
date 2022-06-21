from socket import *
from time import sleep
sockfd = socket(AF_INET, SOCK_DGRAM)
sockfd.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
# sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

while True:
    sockfd.sendto('注意啦!'.encode(), ('192.168.131.255', 9999))
    print('ok')
    sleep(2)

sockfd.close()

