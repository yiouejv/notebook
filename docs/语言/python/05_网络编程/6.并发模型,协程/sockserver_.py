from socketserver import *


# 创建服务器类
class Server(ForkingMixIn, TCPServer):
    pass


class Hanlder(StreamRequestHandler):
    def handle(self):
        # self.request <==>  accept 返回的套接字
        # self.request()
        print('Connect form', self.request.getpeername())
        while True:
            data = self.request.recv(1024)
            if not data:
                break
            print(data.decode())
            self.request.send(b'aaa')


if __name__ == '__main__':
    server_addr = ('0.0.0.0', 9999)
    # 创建服务器对象
    server = Server(server_addr, Hanlder)
    # 启动服务器
    server.serve_forever()