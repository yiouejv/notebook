# encoding: utf-8
from threading import Thread
from time import sleep


def fun():
    sleep(3)
    print('Daemon测试')


# t = Thread(target=fun)
t = Thread(target=fun, daemon=True)
print(t.isDaemon())
t.start()
print('''-------------主线程结束-------------''')
