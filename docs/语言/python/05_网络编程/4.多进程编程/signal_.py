# encoding: utf-8
# from signal import signal, SIGALRM, alarm, SIG_DFL
import signal
from time import sleep


signal.alarm(5)
# 使用默认方法处理信号
# signal.signal(signal.SIGALRM, signal.SIG_DFL)

# 忽略信号
signal.signal(signal.SIGALRM, signal.SIG_IGN)
signal.signal(signal.SIGINT, signal.SIG_IGN)

while True:
    sleep(1)
    print('摁 Ctrl + C 啊')
    print('等待时钟...')