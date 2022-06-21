# encoding: utf-8
from threading import Thread, current_thread  # 当前线程对象
from time import sleep


def fun(sec):
    print('线程属性测试')
    sleep(sec)
    # 线程对象的getName()方法获取线程名称
    print('%s 线程结束' % current_thread().getName())


# 线程列表
thread = []

for i in range(3):
    t = Thread(target=fun, args=(1,), name='yang%d' % i)
    thread.append(t)
    t.start()

# 查看线程状态
print('is_alive:', t.is_alive())
print(t.getName())

# 设置线程名称
thread[1].setName('wen')
print(thread[1].getName())

# 回收线程
for i in thread:
    i.join()
