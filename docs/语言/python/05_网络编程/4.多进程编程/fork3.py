import os
import time
pid = os.fork()

if pid < 0:
    print('Create process Failed')
elif pid == 0:
    time.sleep(2)
    # 获取当前进程的PID
    print('Child process PID', os.getpid())
    # 获取父进程的PID
    print('Chile get parent pif', os.getppid())
else:
    print('Parene get child pid', pid)
    print('parent get pid', os.getpid())
