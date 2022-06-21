from socket import *

# 创建TCP套接字
sockfd = socket(AF_INET, SOCK_STREAM)
sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sockfd.bind(('0.0.0.0', 8002))

sockfd.listen(10)

while True:
    connfd, addr = sockfd.accept()
    print('Connect from', addr)

    data = connfd.recv(4096)
    print("*******************")
    for i in str(data).split('\\r\\n'):
        print(i)
    print("*******************")
    # 组织响应内容
    response = '''HTTP/1.1 200 OK
Content-Type: text/html

<h1>Welcome to Tedu</h1>
    '''
    connfd.send(response.encode())
    print('ok')
    connfd.close()

sockfd.close()
