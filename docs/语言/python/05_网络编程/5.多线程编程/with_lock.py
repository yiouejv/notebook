# encoding: utf-8
from threading import Thread, Lock
from time import sleep

a = 0
b = 0
lock = Lock()

def value():
    while True:
        sleep(0.2)
        lock.acquire()
        if a != b:
            print('a = %d, b = %d' % (a, b))
        lock.release()


t = Thread(target=value)
t.start()

while True:
    # with方式上锁
    with lock:
        a += 1
        b += 1

t.join()
