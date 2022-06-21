import socket

sockfd = socket.socket()

sockfd.connect(('127.0.0.1', 8888))

while True:
    mess = bytes(input('发送消息:'), encoding='utf-8')
    print(mess)
    sockfd.send(mess)
    recv_mess = sockfd.recv(1024)
    print('收到消息:', recv_mess.decode('utf-8'))

sockfd.close()



