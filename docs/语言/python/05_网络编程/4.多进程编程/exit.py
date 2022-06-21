import os, sys

# 结束进程后不再执行后面的语句
# os._exit(1)
try:
    sys.exit('exit')
except SystemExit as e:
    print('系统退出', e)  # e就是退出信息，传入的字符串

# print('process exit')








