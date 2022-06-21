# encoding: utf-8
from threading import Thread
from time import sleep
import os

a = 1


# 线程函数
def music():
    for i in range(5):
        global a
        sleep(2)
        a = 10000
        print('播放葫芦娃', os.getpid())


# 线程函数
def flim():
    for i in range(5):
        sleep(1)
        print('放电影', os.getpid())
        print(a)


# 创建线程对象
t1 = Thread(target=music)
t2 = Thread(target=flim)
t1.start()
t2.start()
t1.join()
t2.join()
