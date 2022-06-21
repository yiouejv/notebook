import os
from time import sleep

pid = os.fork()

if pid < 0:
    print('create process failed')
elif pid == 0:
    print('chile process:', os.getpid())
    print('chile process exit')
else:
    sleep(1)
    print('parent process', os.getpid())
    while True:
        pass