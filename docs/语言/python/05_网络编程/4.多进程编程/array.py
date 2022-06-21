from multiprocessing import Array, Process
import time


# # 创建共享内存，开辟5个整型空间
# shm = Array('i', 5)

# 存入字符串, 要求bytes格式
shm = Array('c', b'Hello')

# # 放入初始化整型列表
# shm = Array('i', [1, 2, 3, 4])

def fun():
    for i in shm:
        print(i)
    shm[0] = b'h'


p = Process(target=fun)
p.start()
p.join()

for i in shm:
    print(i)

print(shm.value)
