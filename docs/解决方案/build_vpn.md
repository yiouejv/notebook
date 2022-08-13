
```
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocksR.sh

mod +x shadowsocksR.sh

./shadowsocksR.sh 2>&1 | tee shadowsocksR.log
```

docs/解决方案下有备份

安装过后如果想要修改，运行如下相关命令

启动：/etc/init.d/shadowsocks start

停止：/etc/init.d/shadowsocks stop

重启：/etc/init.d/shadowsocks restart

状态：/etc/init.d/shadowsocks status

配置文件路径：/etc/shadowsocks.json 修改文件用vi 或者 vim命令，使用方法百度

日志文件路径：/var/log/shadowsocks.log

安装路径：/usr/local/shadowsocks/shadowsoks

卸载./shadowsocksR.sh uninstall



如果SSR成功安装，但是不能正常启动，在centOS中主要原因是缺少python环境，利用以下指令进行安装

yum -y install python36

cd /usr/bin

ln -s python3 python
