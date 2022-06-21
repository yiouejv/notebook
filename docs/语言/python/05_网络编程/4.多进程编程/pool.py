from multiprocessing import Pool
import time

def fun1(msg):
    time.sleep(1)
    print(msg)
    return time.ctime()

result = []
# 创建进程池
pool = Pool(processes=4)
for i in range(10):
    msg = 'hello %d ' % i
    r = pool.apply_async(func=fun1, args=(msg,))
    result.append(r)

# 关闭进程池
pool.close()
# 回收进程池
pool.join()
for i in result:
    print(i.get())  # 获取事件的返回值
