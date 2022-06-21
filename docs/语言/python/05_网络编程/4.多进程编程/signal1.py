import signal
import os


# 向4130发送信号
os.kill(4130, signal.SIGKILL)