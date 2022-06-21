from socket import *

def handle_client(connfd):
    requests = connfd.recv(4096)
    print(requests)
    with open('index.html', 'rt') as rf:
        html = rf.read()
    response = '''
HTTP/1.1 200 OK
Content-Type: text/html    
''' + '\r\n' + html
    if connfd.sendall(response.encode()) is not None:  # 发送不完整

        res_404 = '''
HTTP/1.1 404 NOT FOUND



'''.encode()
        connfd.send(res_404)


# 创建套接字
def main():
    sockfd =socket()
    sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    sockfd.bind(('0.0.0.0', 8888))
    sockfd.listen(3)
    print('Listen to the port 8888')
    while True:
        connfd, addr = sockfd.accept()
        # 处理请求
        handle_client(connfd)
        connfd.close()


if __name__ == '__main__':
    main()
