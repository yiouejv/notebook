import os
from time import sleep

pid = os.fork()

if pid < 0:
    print('创建子进程失败')
elif pid == 0:
    sleep(3)
    print('子进程退出', os.getpid())
    os._exit(3)
else:
    while True:
        sleep(1)
        # 通过非阻塞打形式捕获子进程的退出状态
        pid, status = os.waitpid(-1, os.WNOHANG)
        print(pid, status)
        print(os.WEXITSTATUS(status))  # 获取子进程退出状态 wexit status
    while True:
        pass