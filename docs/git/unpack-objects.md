
## 问题

在git pull 时发生unpack-objects failed

~~~
remote: Counting objects: 80, done.
remote: Compressing objects: 100% (79/79), done.
Connection to bitbucket.org closed by remote host.
fatal: The remote end hung up unexpectedly
fatal: early EOF
fatal: unpack-objects failed
~~~


## 解决方案

在.git/config中添加


~~~
[core]
    packedGitLimit = 512m
    packedGitWindowSize = 512m
[pack]
    deltaCacheSize = 2047m
    packSizeLimit = 2047m
    windowMemory = 2047m


~~~