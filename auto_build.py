#!/usr/bin/python3
# coding=utf-8
#Author: yiouejv
#Email: yiouejv@126.com
#Time: 2022-06-11 17:15:50

import time
import os, os.path

root = "./"

file_ts_dict = {}

def is_file_changed(filename):
    ts = os.path.getmtime(filename)
    if ts != file_ts_dict.get(filename, 0):
        file_ts_dict[filename] = ts
        return True
    return False

def get_changed_file(root):
    ret = []
    for sub in os.listdir(root):
        filename = root + "/" + sub
        if os.path.isdir(filename):
            if sub.startswith("."): continue
            ret.extend(get_changed_file(filename))
        elif os.path.isfile(filename):
            if is_file_changed(filename):
                ret.append(filename)
    return ret

def main():
    watch_root_list = [
    ]
    docs_root = root + "docs"
    for sub in os.listdir(docs_root):
        if os.path.isdir(docs_root + "/" + sub):
            watch_root_list.append(docs_root + "/" + sub)
    print(watch_root_list)

    first_loop = True
    while True:
        changed_list = []
        while True:
            is_changing = False
            for watch_root in watch_root_list:
                tmp = get_changed_file(watch_root)
                if tmp:
                    is_changing = True
                    for x in tmp:
                        x = "./" + x
                        if x not in changed_list:
                            changed_list.append(x)

            if not is_changing:
                break
            else:
                time.sleep(1)

        if first_loop:
            first_loop = False
        elif changed_list:
            os.system("mkdocs build")
            print(time.strftime("%Y-%m-%d %H:%M:%S"), " mkdocs build", changed_list)
        time.sleep(1)


if __name__ == "__main__":
    main()
