
## IO密集型程序

    在程序执行过程中存在大量IO操作, 而CPU运算操作较少
    特点
        消耗cpu较少运行效率较低

## 计算密集型程序(cpu密集型程序)

    在程序执行中, cpu 运算较多, io 操作相对较少.
    特点
        消耗cpu大, 运行速度快

## IO 分类

    阻塞IO     非阻塞IO     IO多路复用

    阻塞IO: IO的默认形态, 是效率较低的一种IO情形.
        阻塞情况
            1. 因为某种条件没有达成造成的阻塞
                如: accept, input, recv

            2. 处理IO 数据传输时间较长形成的阻塞
                如: 网络传输过程, 文件读写过程

    非阻塞IO
        通过修改IO事件的属性使其变为非阻塞状态(让一些条件阻塞函数不再阻塞)

        *非阻塞IO 往往和循环判断一起使用

        #####套接字.setblocking(False)
            将套接字设置为非阻塞状态

    超时检测
        将原本阻塞的函数设置一个最长阻塞时间, 如果时间内阻塞达成则正常运行,
        如果仍然阻塞则视为超时, 继续向下运行或产生异常

    s.settimeout(sec)
    设置套接字的超时时间


## IO多路复用

    同时监控多个IO事件, 当哪个IO事件准备就绪就执行哪个事件.
    以此形成同时操作多个IO的行为, 避免IO阻塞造成素有的IO都无法执行.

## IO多路复用编程的实现

    1. 将IO设置为关注IO
    2. 将关注IO提交给内核监测
    3. 处理内核给我们反馈的准备就绪的IO

    具体实现方案
        select  -- > 支持winodws, linux unix
        poll    --> linux unix
        epoll  --> linux unix

    import select

    rs, ws, xs = select(rlist, wlist, xlist[, timeout])
    功能
        监控IO事件,阻塞等待IO事件发生
    参数
        rlist           --> 存放等待处理的IO事件
        wlist           --> 存放我们要主动操作的IO事件
        xlist           --> 要关注出错的处理的IO事件
        timeout         --> 超时时间
    返回值
        rs  列表 -->  rlist 准备就绪的IO
        ws  列表 -->  wlist 准备就绪的IO
        xs  列表 -->  xlist 准备就绪的IO

    注意
        1. wlist 如果有IO事件, 则select 立即返回给ws
        2. 在处理IO过程中, 不要出现一个客户端长期占有服务端, 使服务端无法执行到select的情况
        3. IO多路复用占用计算机资源少, IO效率高


## poll

    1. 创建poll对象
        p = select.poll()
    2. 添加注册事件
        p.register(sockfd, POLLIN | POLLERR)

        POLLIN          -->rlist
        POLLOUT         -->wlist
        POLLERR         -->xlist
        POLLHUP         -->断开
        POLLNVAL        -->无效数据

        # 从关注事件中移除
        p.unregister(sockfd)

    3. 阻塞等待IO发生
        events = p.poll()
        功能:
            阻塞等待IO发生
        返回值:
            events 是一个列表, 列表中没一个元素都是一个元组, 代表发生的IO事件
            [(fileno, event), (), ()]

            fileno: 就绪的IO的文件描述符
            event: 就绪的事件

        * 需要通过文件描述符找到对象的IO对象
        {sockfd.fileno(): sockfds}

    4. 处理具体的IO


## epoll方法

    使用方法基本相同
    * 将生成对象poll（）改为epoll
    * 将所有poll对象事件改为epoll对象事件

区别

epoll 的效率要比poll 和select 高
epoll 的事件触发方式更多

## 本地套接字

	Linux 文件
	bcd-lsp

	b 块设备文件
	c 字符设备文件
	d 目录
	- 普通文件
	l 链接
 	s 套接字
	p 管道

    作用
        用于本地不同的程序间进行通信
        创建流程
            1. 创建本地套接字
               sockfd = socket(AF_UNIX, SOCK_STREAM)
            2. 绑定本地套接字文件
                   选定文件位置和名称
               sockfd.bing(path)
            3. 监听 listen
            4. 消息收发， recv, send

