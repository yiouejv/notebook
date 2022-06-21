from multiprocessing import Queue
from time import sleep


# 创建队列
q = Queue(3)
q.put(1)
sleep(0.5)
print(q.empty())
q.put(2)
q.put(3)
print(q.full())
print(q.get())
q.close()
