#### 下载pptpd
```
sudo apt-get install pptpd
```
#### 设置pptpd服务器本地ip与拨号进入的用户的IP地址范围
使用pptpd建立的vpn会在本地建立一个服务器，有一个本地的服务器ip，另外就是拨号进入这个服务器的都会被安排一个用户ip，这里需要设置pptp服务器的本地ip，以及拨号进入这个服务器的用户ip地址的范围。

编辑pptpd.conf文件：
```
sudo vi /etc/pptpd.conf 
```
添加如下行（用文件中默认的就行了）：
```
localip 192.168.0.1

remoteip 192.168.0.234-238,192.168.0.245
```
#### 修改pptp的dns配置（可选）
修改：
```
/etc/ppp/pptpd-options
```
增加ms-dns 的值为192.168.1.1，这一步是可选的，不配置也可以
#### 配置用户信息
修改：
```
/etc/ppp/chap-secrets
```
这里是对拨号的用户信息进行配置，添加如下：
```
# client        server  secret                  IP addresses

yiouejv pptpd 123456 *
```
这里按照：

用户名（tab） 主机名（tab） 密码（tab） 分配到的ip地址

这样的格式来填写，其中的主机名可以用“*”代替，也可以随便填一个；如果不强制指定给拨号用户分配到哪一个ip地址，可以将最后一项也改为“*”。

#### 重启pptpds
```
sudo /etc/init.d/pptpd restart
```

#### 修改/etc/sysctl.conf

修改sysctl.conf文件：
```
sudo vi /etc/sysctl.conf
```
去掉
```
“net.ipv4.ip_forward=1”
```
前的注释号，修改完之后使用命令：
```
sudo sysctl -p
```
来使配置生效。

#### 转发规则命令
```
iptables -t nat -A POSTROUTING -s 192.168.2.0/16 -o eth0 -j MASQUERADE  //是ifconfig得到的IP
iptables-save > /etc/iptables.pptp
```

#### 重启pptpd
```
sudo /etc/init.d/pptpd restart  
```