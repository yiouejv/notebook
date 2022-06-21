

## socket 套接字编程

套接字的分类:

1. 流式套接字(SOCK\_STREAM)

    传输层基于TCP协议的套接字编程方案

2. 数据报套接字(SOCK\_DGRAM)

    传输层基于UDP协议的套接字编程方案

3. 底层套接字(SOCK\_RAM)

    访问底层协议的套接字编程

面向链接的传输 -- > TCP--> 可靠的 --->流式套接字

面向无链接的传输 -- > UDP--> 不可靠的 -->数据报套接字


TCP套接字服务端编程

    import socket
    1. 创建套接字
        sockfd = socket.socket(socket_family=AF_INET, socket_type=SOCK_STREAM, proto=0)

        功能: 创建套接字
        参数: socket_family ---> 选择套接字的地址族类型, AF_INET(基于IPv4的网络地址族通信)
             socket_type ---> 套接字类型, SOCK_STREAM 流式套接字, SOCK_DGRAM 数据报套接字
             proto  ---> 选择子协议类型, 0表示不选择任何的类型, TCP/UDP没有子协议
        返回值: 返回套接字对象

    2. 绑定服务端地址
        sockfd.bind(addr)
        功能:
            绑定IP地址
        参数: tuple --> (ip, port)

        localhost -- > 可以被本机用 127.0.0.1 访问
        127.0.0.1 -- > 可以被本机用 127.0.0.1 访问
        本机IP     -- > 可以被所有人用本机IP访问
        0.0.0.0   -- > 可以被别人用本机IP访问, 也可以被自己用127.0.0.1访问

    3. 设置监听套接字
        sockfd.listen(n)
        功能:
            将套接字设置为监听套接字,　创建监听队列
        参数:
            n 表示监听队列的大小
        说明:
            一个监听套接字可以连接多个客户端套接字

    4. 等待处理客户端的连接请求
        connfd, addr = sockfd.accept()
        功能:
            阻塞等待处理客户端链接
        返回值:
            connfd 客户端链接套接字
            addr 链接的客户端地址
    说明:
        阻塞函数: 程序运行过程中遇到阻塞函数则暂停运行, 直到某种阻塞条件达成再继续运行.

    5. 消息收发
        data = connfd.recv(buffersize)
        功能:
            接收对应客户端消息
        参数:
            一次最多接受多少字节
        返回值:
            接受到的内容
            如果没有消息则阻塞

    6. 消息发送
        n = connf.send(data)
        功能:
            发送消息给对应客户端
        参数:
            要发送的内容, 必须是bytes格式
        返回值:
            返回实际发送消息的大小

    7. 关闭套接字
        sockfd.close()
        功能:
            关闭套接字

TCP套接字客户端编程

    1. 创建套接字(必须相同类型的套接字才能通信)

    2. 建立连接
        sockfd.connect(servr_addr)
        功能:
            建立连接
        参数:
            元组, 服务端地址
    3. 消息收发
        消息收发要和服务端配合, 避免两边都出现recv阻塞
    4. 关闭套接字

## 套接字传输注意事项

1. 监听套接字存在客户端即可发起链接, 但是最终链接的处理需要accept进行处理
2. 如果链接的另外一端退出, 则recv立即返回空字符串, 不再阻塞
3. 当链接的另一端再试图send发送就会产生BrokenPipeError


## 网络的收发缓冲区

    send 和 recv 实际上是和缓冲区进行交互, 发送缓冲区满时就无法发送, 接受缓冲区满时recv才阻塞
    作用
        协调收发(处理)速度
        减少交互次数

## TCP粘包

    产生的愿因
        TCP套接字以字节流传输, 没有消息边界, 发送和接受并不能保证被及时地接收
    影响
        如果每次发送内容表达独立的含义, 此时可能需要处理粘包, 防止产生歧义
    处理方法
        1. 每次发送的消息, 添加结尾标志(人为增加消息边界)
        2. 发送数据结构体
        3. 协调收发速度,每次发生后都预留接收时间

## 基于UDP套接字的服务端

    1. 创建数据报套接字
        sockfd = socket(AF_INET, SOCK_DGRAM)

    2. 绑定地址
        sockfd.bind(tuple)

    3. 消息的收发
        接收
            data, addr = sockfd.recvfrom(buffersize)
            功能:
                接收UDP消息
            参数:
                每次最多接收多大的消息
            返回值:
                data 接受到的数据
                addr 消息发送端的地址
            * 一次接受一个数据包, 如果数据报大小大于buffersize 则会丢失部分消息

        发送
            sockfd.sendto(data, addr)
            功能:
                发送UDP消息
            参数:
                data 发送消息, bytes格式
                addr 目标地址
            返回值:
                发送的字节数
    4. 关闭套接字
        sockfd.close()



## 基于UDP套接字的客户端

    1. 创建套接字
        socket(AF_INET, SOCK_DGRAM)
    2. 消息发送
        recvfrom / sendto
    3. 关闭套接字
        close()


## tcp 套接字编程和udp套接字编程的区别

    1. 流式套接字使用字节流的方式传输, 数据报套接字以数据报形式传输数据
    2. tcp会有粘包现象, udp有消息边界不会形成粘包
    3. tcp可以保障数据传输的完整性, udp不保证
    4. tcp需要进行listen, accept 操作, udp 不需要
    5. tcp收发消息使用新的套接字, recv, send,
       udp使用 recvfrom, sendto

## 补充函数

    sendall()
    功能:
        发送TCP消息
    参数
        要发送的内容, bytes格式
    返回值
        成功返回None 失败产生异常


## 套接字对象

    # 获取套接字的地址族
        sockfd.family
    # 获取套接字的类型
        sockfd.type
    # 获取套接字的绑定地址
        sockfd.getsockname()
    # 获取套接字的文件描述符
        s.fileno()

        文件描述符
            每一个IO事件操作系统都会分配一个不同的非负整数作为编号, 该正整数即为IO操作的文件描述符
            作用:
                文件描述符是操作系统识别IO操作的唯一标志
                sys.stdin.fileno()          0
                sys.stdout.fileno()         1
                sys.stderr.fileno()         2

    # 获取客户端链接套接字的对应地址
    connfd, addr = sockfd.accept()
    connfd.getpeername()

    # sockfd.setsockopt(level, option, value)     option
        功能:
            设置套接字选项, 丰富或修改套接字属性功能
        参数
            level  选项类别  SOL_SOCKET
            option 具体选项
            value  选项值

            sockfd.setsockopt(SOL_SOCK, SO_REUSEADDR, True)

    # sockfd.getsockopt(level, option)
        功能:
            获取套接字的选项值
        参数
            level  选项类别  SOL_SOCKET
            option 具体选项

            sockfd.getsockopt(SOL_SOCK, SO_REUSEADDR)
    #####注意
        如果要设置套接字选项, 最好在创建套接字之后立即设置


## TCP/UDP的应用

    UDP应用广播
        广播
            一点发送, 多点接收
        广播地址
            一个网段内有一个指定的广播地址, 是该网段的最大地址

        广播风暴
            一个网络中有大量的广播就会产生广播风暴占用大量带宽, 影响正常访问速度.


    TCP应用
        http协议:
            超文本传输协议, 是一个应用层协议
        主要用途
            网页数据的传输
            数据传输方法
        特点
            1. 应用层协议, 传输层使用TCP服务
            2. 简单,灵活, 多种语言都有HTTP相关操作接口
            3. 无状态协议, 不记录用户传输的信息
            4. http1.1 支持持久连接


        一端通过http请求的格式,发送具体请求的内容, 另一端接收http请求,
        按照协议格式解析, 获取实是请求后按照http协议响应格式组织回复内容,
        回发请求方,完成一次数据交互

        http请求(request)
            请求格式
                1. 请求行: 具体的请求类别和请求内容
                    格式:
                            GET      /     HTTP/1.1
                           请求类别  请求内容  协议版本
                       请求类别: 表示请求的种类
                            GET             获取网络资源
                            POST            提交一定的附加信息得到返回结果
                            HEAD            获取响应头
                            PUT             更新服务器资源
                            DELETE          删除服务器资源
                            CONNECT
                            TRACE           用于测试
                            OPTIONS         用于获取服务器性能信息

                2. 请求头:
                    对请求内容的具体描述信息
                3. 空行
                4. 请求体
                    请求参数或者是提交的内容

        http响应(response)
            响应行: 反馈响应的情况
                格式: HTTP/1.1   200     OK
                    协议版本      响应码   附加信息
                响应码: 响应的具体情况
                    1xx: 提示信息, 表示请求成功
                    2xx: 响应成功
                    3xx: 响应需要重定向
                    4xx: 客户端错误
                    5xx: 服务端错误

                常见的相应码:
                           200 成功
                           404 请求内容不存在
                           401 没有访问权限
                           500 服务器发生未知错误
                           503 暂时无法执行
            响应头:
                对响应内容的具体描述
            空行
            响应体:
                返回给请求端的具体内容
