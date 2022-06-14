

```python
def md5(string):
    import hashlib
    import time

    ctime = str(time.time())  # 获取当前时间转为字符串
    m = hashlib.md5(bytes(string, encoding="utf-8"))
    m.update(bytes(ctime, encoding='utf-8'))
    return m.hexdigest()


if __name__ == '__main__':
    print(md5('要加密的字符串'))

```