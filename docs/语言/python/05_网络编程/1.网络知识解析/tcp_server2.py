from socket import *

sockfd = socket(AF_INET, SOCK_STREAM)
sockfd.bind(('0.0.0.0', 10026))
sockfd.listen(10)


def run():
    print('等待链接...')
    connfd, addr = sockfd.accept()
    print('连接成功', addr)
    while True:
        data = connfd.recv(3).decode(encoding='utf-8')
        if data == '\r\n':
            connfd.close()
            break
        connfd.send(b'recive message')
        print('已经收到消息:', data)
    run()


run()
sockfd.close()




