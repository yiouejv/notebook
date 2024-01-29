
操作步骤
1.生成公钥

```
ssh-keygen -t rsa -C "yiouejv@126.com"
```

2.进入路径

```
vim ~/.ssh/id_rsa.pub
```

3.复制公钥到GitHub设置SSH and GPG keys中的SSH keys

错误原因：格式不正确

解决方法：

第2步使用如下命令后复制

```
cat ~/.ssh/id_rsa.pub
```
