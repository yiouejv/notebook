# encoding:utf-8
from multiprocessing import Process
from time import sleep


# 带参数的进程参数
def worker(sec, name):
    for i in range(3):
        sleep(sec)
        print("I'm %s " % name)
        print("I'm working...")


p = Process(target=worker, args=(2, 'zhang'), name='worker')
p.start()

print('Process name', p.name)
print('Process PID', p.pid)
# 进程生存情况
print('Process is alive', p.is_alive())

p.join()
