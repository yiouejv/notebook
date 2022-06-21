# encoding: utf-8
from multiprocessing import Process, Lock
from time import sleep
import sys

# 创建锁
lock = Lock()


def write1():
    lock.acquire()
    for i in range(20):
        sys.stdout.write('write1想先向终端写入\n')
    lock.release()


def write2():
    lock.acquire()
    for i in range(20):
        sys.stdout.write('write2想先向终端写入\n')
    lock.release()


p1 = Process(target=write1)
p2 = Process(target=write2)
p1.start()
p2.start()

p1.join()
p2.join()
