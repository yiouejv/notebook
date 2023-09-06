
# 安装svn

sudo apt-get update

在线安装命令：

sudo apt-get install subversion

mkdir ~/svn_repo

sudo chmod -R 777 ~/svn_repo

sudo svnadmin create ~/svn_repo

主要的配置文件在conf文件夹下面：svnserve.conf，passwd，authz 

sudo chmod -R 777 ~/svn_repo/db

# 修改conf文件

## conf配置

'''
anon-access = read（可改成none，即不可读，不改成none，show log看不了）

#权限用户可写
auth-access = write
#密码文件为passwd
password-db = passwd
#权限文件为authz
authz-db = authz

去掉前面的#，并且顶格，不然可能会报错
'''

## authz 配置

'''
[groups]
admin = yiouejv
member = yule,shuiguo

[/]
@admin = rw
@member = rw
'''

# 启动服务

svnserve -d -r ~/svn_repo
