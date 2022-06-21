# encoding: utf-8
import signal
import time


def handler(sig, frame):
    if sig == signal.SIGALRM:
        print('收到时钟信号', sig)
    elif sig == signal.SIGINT:
        print('收到Ctrl + C 信号, 但是我就不结束', sig)



signal.alarm(5)

signal.signal(signal.SIGALRM, handler)
signal.signal(signal.SIGINT, handler)

while True:
    print('Waiting for a signal')
    time.sleep(2)