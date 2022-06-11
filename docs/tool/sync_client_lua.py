#conding=utf8
import os
import copy
import time

'''
检查目录文件改变，自动复制到指定目录
'''

is_window = True
source_path = "//172.16.8.30/server/trunk/client/LuaScripts"
target_path = r"d:\\client2\LuaScripts"

file2time = {}

def is_update_file(path, time):
    path = str(path)
    old_time = file2time.get(path, 0)
    file2time[path] = time

    # print(path, old_time)
    return old_time > 0 and time > old_time


def mv_to_window(path):
    rep = copy.copy(source_path)
    # window 需要换行符转换
    if is_window:
        path = path.replace(r'/', '\\')
        rep = rep.replace(r'/', '\\')

    newpath = path.replace(rep, target_path)
    print("newpath: " + newpath)
    cmd = "copy {oldpath} {newpath}".format(newpath=newpath, oldpath=path)
    print("cmd: " + cmd)
    print("\n")
    os.popen(cmd)

def main():
    # g = os.walk("/home/yangwenjun/trunk/client/LuaScripts")
    g = os.walk(source_path)
    for path, dir_list, file_list in g:
        for file_name in file_list:
            full_path = os.path.join(path, file_name)
            # print(full_path)

            modify_time = os.path.getmtime(full_path)
            # print(modify_time)
            if not file_name.endswith("swp") and is_update_file(full_path, modify_time):
                print("update file: " + full_path)
                mv_to_window(full_path)


if __name__ == "__main__":
    i = 0
    while True:
        time.sleep(1)
        i += 1
        print("watch file change ...: " + str(i))
        main()
