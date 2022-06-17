
### 与python交互

模块名：pymysql  
安装:  
1. 在线： sudo pip3 insatll pymysql  
2. 离线： pymysql.tar.gz  
	解压： setup.py  
    	   python3 setup.py install  

### pymysql 使用流程

```python
1. 建立数据库连接对象(db=pymysql.connect(...))
2. 创建游标对象cur(操作数据库的对象)
3. 游标对象方法： cur.execute('insert into ...')
4. 提交到数据库执行： db.commit()
5. 关闭游标对象cur.close()
6. 关闭数据库连接对象db.close()
```

#### connect连接对象

```mysql
db = pymysql.conncet(参数列表)
    1. host:主机地址
    2. user：用户名
    3. password: 密码
    4. database: 数据库
    5. charset: utf8
    6. port: 端口（3306）

db(数据库连接对象)的方法
db.cursor() 创建游标对象, 用来执行sql命令
db.commit() 提交到数据库执行
db.close()  断开与数据库连接
db.rollback() 回滚
```

#### cursor 对象的方法

```python
execute(sql命令):  # 执行sql命令
fetchone():  # 获取查询结果的第一条数据
fetchmany(n):  # 获取n条数据
fetchall():  # 获取所有数据
close():  # 关闭游标对象
```