# encoding:utf-8
'''
    1. 多线程并发
    2. 可以请求简单数据
    3. 能进行简单请求解析
    4.结构使用类进行封装
'''

from socket import *
from threading import Thread
import sys
import traceback


HOST = '0.0.0.0'
PORT = 8888


# httpserver类,封装具体的服务器功能
class HTTPServer():
    def __init__(self, server_addr, server_static, Handler=None):
        # 添加服务器对象属性
        self.ip = server_addr[0]
        self.port = server_addr[1]
        self.server_static = server_static
        self.server_address = server_addr
        # 创建套接字
        self.create_socket()
        # self.sockfd.request = Handler(self.sockfd)

    def create_socket(self):
        self.sockfd = socket(AF_INET, SOCK_STREAM)
        self.sockfd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        self.sockfd.bind(self.server_address)

    def server_forever(self):
        # 设置监听等待客户端链接
        self.sockfd.listen(1000)
        print('Listen the port', self.port)
        while True:
            try:
                connfd, addr = self.sockfd.accept()
            except KeyboardInterrupt:
                sys.exit('服务器退出')
            except Exception as e:
                traceback.print_exc()
                continue
            print('Connect the from', addr)
            # 创建新的线程处理请求
            client_thread = Thread(target=self.handler_request, args=(connfd,))
            client_thread.setDaemon(True)
            client_thread.start()

    def handler_request(self, connfd):
        '''客户端请求函数'''
        # 接收客户端请求
        request = connfd.recv(4096)
        # 解析请求内容
        requestHeaders = request.splitlines()[:-1]
        #　获取具体的请求内容
        get_request = str(requestHeaders[0]).split(' ')[1]
        print(get_request)
        if get_request == '/' or get_request[-5:] == '.html':  # 请求静态网页
            self.get_html(get_request, connfd)
        else:
            self.get_data(connfd, get_request)
        connfd.close()

    def get_html(self, get_request, connfd):
        data = b'HTTP/1.1 200 OK\n'
        data += b'Content-Type: text/html\n'
        data += b'\n'
        if get_request == '/':  # 首页
            # 返回首页
            try:
                rf = open(self.server_static+r'/index.html', 'rb')
                data += rf.read()
                connfd.send(data)
            except:
                # 没有找到页面
                data = b''
                data = b'HTTP/1.1 404 NOT FOUND\n'
                data += b'Content-Type: text/html\n'
                data += '\n'
                data += b'Sorry NOT FOUND\n'
                connfd.send(data)
        else:
            with open(self.server_static+r'/'+get_request[1:], 'rb') as rf:
                data += rf.read()
                print(data)
                connfd.send(data)

    def get_data(self, connfd, get_request):
        urls = ['/time', '/tude', '/python']
        if get_request in urls:
            response = 'HTTP/1.1 200 OK\n'
            response += 'Content-Type: text/html charset=utf-8\n'
            response += '\n'
            if get_request == r'/time':
                import time
                response += r'/time'
            elif get_request == r'/tude':
                response += 'welcome to tude'
            elif get_request == r'/python':
                response += '人生苦短我用python'
            response = response.encode(encoding='utf-8')
        else:
            response = b'HTTP/1.1 404 NOT FOUND\n'
            response += b'Content-Type: text/html\n'
            response += '\n'
            response += b'Sorry NOT FOUND\n'
        connfd.send(response)


def main():
    # 静态页面存储目录
    static_dir = "./static"
    # 服务器地址
    server_addr = (HOST, PORT)
    # 生成对象
    httpd = HTTPServer(server_addr, static_dir)
    # 启动服务器
    httpd.server_forever()


if __name__ == '__main__':
    main()
