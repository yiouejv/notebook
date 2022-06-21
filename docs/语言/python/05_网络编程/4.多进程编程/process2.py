# encoding:utf-8
from multiprocessing import Process
from time import sleep, ctime


def tm():
    while True:
        sleep(2)
        print(ctime())


p = Process(target=tm, daemon=True)
p.start()
sleep(5)

print('main process exit')
