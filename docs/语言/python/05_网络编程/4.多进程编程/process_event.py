# encoding: utf-8
'''控制进程的执行顺序
'''
from multiprocessing import Event, Process
from time import sleep

# 创建事件对象
e = Event()


def wait_event():
    print('想操作临界区')
    e.wait()
    print('开始操作临界区资源', e.is_set())
    with open('file', 'r') as f:
        print(f.read())


def wait_event_time():
    print('也想操作临界区')
    e.wait(2)
    if e.is_set():
        print('开始操作临界区资源', e.is_set())
        with open('file', 'r') as f:
            print(f.read())
    else:
        print('!!!不能读取文件')


p1 = Process(target=wait_event)
p2 = Process(target=wait_event_time)
p1.start()
p2.start()
print('主进程操作')
with open('file', 'w') as f:
    sleep(3)
    f.write('I Love China')

e.set()
print('释放临界区')
p1.join()
p2.join()
