

pymongo
```
安装sudo pip3 install pymongo
```

#### 操作步骤
1. 创建mongodb的数据库链接对象
```python
conn = pymongo.MongoClient('localhost', 27017)
```

2. 生成数据库对象(__setitem__, __getitem__)
```python
db = conn.stu
# 或
db = conn['stu']
```
3. 生成集合对象
```python
myset = db.collection
# 或
myset = db['collection']
```
4. 进行集合操作（增删改查索引聚合）

5. 关闭数据库链接
```
conn.close
```


#### 插入操作
```python
insert()
insert_one()
insert_many()
# id相同则修改，不同则插入
save()
```

#### 查找操作
```
find()
    功能
        查找数据库内容
    参数
        同mongo shell find()
    返回值
        返回一个结果游标对象
find_one()
    功能
        查询第一条符合条件的数据
    参数
        同find()
    返回值
        返回一个字典

*在pymongo 中所有操作符的用法同mongo shell相同，只是
操作时加引号，以字符串的方式写入python代码
示例
   cursor = myset.find({'age':{'$gt':18}},{'_id':0})
```
```
cursor 对象的属性
   next()
   limit()
        myset.skip(1).limit(3):
   skip()
   count()
   sort()
        pymongo
            myset.sort([('age',1), ('name',-1)]):
        mongo shell
            sort({'age'：1, 'name':-1})

    myset.find({'$or':[{'age':{'$lt':19}}, {'sex':'女'}]},{})

使用for或者是next使游标位置不再指向开头位置的时候，调用limit, skip, sort就会报错

修改操作
    update(query, update, upsert=false, multi=false)
    示例
        mongo_update

删除操作
    remove(qusery, multi=True)
    multi 默认是True表示删除所有query过滤文档
    设置False表示只删除第一个

    ＊(python中)True  == true(mongo shell)
    ＊(python中)False  == false(mongo shell)
    ＊(python中)None  == null(mongo shell)

索引操作
    ensure_index()
    list_indexes()
    drop_index()
    drop_indexes()

聚合操作
    aggregate()
    参数
        和mongo shell一样
    返回
        返回和find()函数相同的游标对象


练习
grade 数据库，　class集合
1. 为所有人添加分数域
    {'chinese': 88, 'math': 77, 'english': 78}

2. 按照性别分组统计每组人数

3. 统计每名男生的语文成绩

4. 将女生按照英语成绩降序排列


# 文件操作
pymongo 实现gridfs存储

import gridfs
GridFS()
功能
    生成grid数据库对象



import bson
bson.binary.Binary()
功能
    将bytes格式子串转换为mongodb的二进制存储格式
```