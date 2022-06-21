import socket
hostname = socket.gethostname()

address = socket.gethostbyname(hostname)

# 通过地址获取主机网络信息
host_byaddr = socket.gethostbyaddr('127.0.0.1')   # (主机名, 别名, 网络地址)


b = socket.inet_aton('192.168.1.2')

ip = socket.inet_ntoa(b'\xc0\xa8\x01\x02')

# 获取一个应用的端口号
port = socket.getservbyname('http')

print(hostname)
print(address)
print(host_byaddr)
print(b)
print(ip)
print(port)
