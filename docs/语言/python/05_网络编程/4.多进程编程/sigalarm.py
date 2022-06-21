import signal
import time

signal.alarm(3)
time.sleep(2)
signal.alarm(5)
signal.pause()  # 等待阻塞信号
signal.signal()
while True:
    time.sleep(1)
    print('等待时钟信号...')
