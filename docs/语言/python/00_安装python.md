## 安装python

```
# wget https://www.python.org/ftp/python/3.6.2/Python-3.6.2.tar.xz
# tar -xvf Python-3.6.2.tar.xz
# cd Python-3.6.2
# ./configure
# make
# make install
```

如果出现错误：

can’t decompress data; zlib not available

说明缺少依赖：zlib。

安装依赖zlib、zlib-devel# 在ubuntu里，zlib叫zlib1g，相应的zlib-devel叫zlib1g-dev

```
$ sudo apt-get install zlib1g
$ sudo apt-get install zlib1g-dev
```

添加快捷方式:

```
ln -s /usr/local/bin/python3 /usr/bin/python3
```

## 可能出现的问题

安装python3.6之后，pip3无法正常使用

```
curl https://bootstrap.pypa.io/pip/3.6/get-pip.py -o get-pip.py
python3 get-pip.py --force-reinstall
```
