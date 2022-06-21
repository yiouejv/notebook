from multiprocessing import Pool
import time


def fun(n):
    time.sleep(1)
    print('执行 pool map 事件')
    return n**2


pool = Pool(processes=4)
# 使用map将事件放入进程池
r = pool.map(fun, [1, 2, 3, 4, 5])
for i in range(10):
    s = pool.apply_async(fun, args=(i,))
    print(s.get())
print(r)
pool.close()
pool.join()