
在 vm 的设置->选项->共享文件夹, 添加需要共享的文件夹, 重启计算机

挂载: 在linux执行命令

mkdir /mnt/win

`sudo mount -t fuse.vmhgfs-fuse .host:/ /mnt/win -o allow_other,defaults`

之后就可以看到自己共享的文件夹目录了
