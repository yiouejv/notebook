## 部署php项目及安装php相关插件

### 安装环境

nginx: sudo apt-get install nginx

mysql: sudo apt-get install mysql-server

php:  sudo apt install php php-fpm php-mysql 

### 配置步骤

1. 修改/etc/php/7.0/fpm/pool.d/www.conf
```
sudo vim ./www.conf
listen修改为127.0.0.1:9000             在(36行)
```
- sudo php-fpm7.0启动fpm，用netstat -tlnp检查9000端口占用
- 修改/usr/local/ nginx/conf/ nginx.conf
	可以根据你自己的需求把配置文件包含进行就行了
```
可以复制下面的对应修改
server {
    listen 80;
    server_name: quan.kongping.net;
    access_log /var/log/nginx/access_php.log;
    location / {
        root /www/web;
        index index.php index.html index.htm;
    }
    location ~\.php${
        root /www/web;
        fastcgi_pass 127.0.0.1:9000;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;
    }
}
```
- 创建文件夹，上传程序代码，路径和3中填写的路径保持一致
index.php内容为
```php
<?php phpinfo(); ?>  
```
- 启动nginx
```shell
service nginx reload
service nginx start
```

### 插件安装
```
sudo apt-get install php-curl
sudo apt-get install php-mbstring
```
### 参考文章：
<https://blog.csdn.net/qq_38711394/article/details/80819895>