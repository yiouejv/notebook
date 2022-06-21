import socket

# 创建一个服务端套接字
sockfd = socket.socket()

# 绑定服务地址
sockfd.bind(('0.0.0.0', 10013))

# 创建监听
sockfd.listen(5)
print('wait from connect...')

# 等待接受连接
connfd, addr = sockfd.accept()
print('connect from', addr)

# 收发消息
while True:
    data = connfd.recv(2*10)
    print('收到消息:', data.decode(encoding='utf-8'))
    mess = input('发送消息:')
    n = connfd.send(bytes(mess, encoding='utf-8'))

# 关闭套接字
connfd.close()
sockfd.close()