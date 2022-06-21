
# 解决apt-get安装中的E: Sub-process /usr/bin/dpkg returned an error code (1)问题

 在用apt-get安装软件包的时候遇到E: Sub-process /usr/bin/dpkg returned an error code (1)问题，解决方法如下：

```sh
cd /var/lib/dpkg/
sudo mv info/ info_bak          # 现将info文件夹更名
sudo mkdir info                 # 再新建一个新的info文件夹
sudo apt-get update             # 更新
sudo apt-get -f install         # 修复
sudo mv info/* info_bak/        # 执行完上一步操作后会在新的info文件夹下生成一些文件，现将这些文件全部移到info_bak文件夹下
sudo rm -rf info                # 把自己新建的info文件夹删掉
sudo mv info_bak info           # 把以前的info文件夹重新改回名
```
