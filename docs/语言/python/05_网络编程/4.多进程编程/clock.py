from multiprocessing import Process
import time


class ClockProcess(Process):
    def __init__(self, value):
        self.value = value
        super(ClockProcess, self).__init__()

    # 重写run方法
    def run(self):
        # super(ClockProcess, self).start()
        for i in range(5):
            print('The time is {}'.format(time.ctime()))
            time.sleep(self.value)


# 创建自定义进程类的对象
p = ClockProcess(1)
# 自动调用run方法
p.start()
p.join()
