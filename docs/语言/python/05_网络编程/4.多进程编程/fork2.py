#encoding: utf-8
import os
import time

print('**********************')
a = 1
pid = os.fork()

if pid < 0:
    print('创建进程失败')
elif pid == 0:
    print('这是新的进程')
    print('a =', a)
    a = 10000
else:
    time.sleep(1)
    print('这是原有的进程')
    print('parent a =', a)

print('##演示完毕')

### 子进程复制父进程的全部代码段和运行空间



