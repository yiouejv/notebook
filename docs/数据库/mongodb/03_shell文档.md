

### 非关系型数据库和关系型数据库的区别

- 不是以关系模型构建的，结构比较自由   
- Nosql不保障数据的一致性   
- Nosql弥补了关系型数据库的一些不足，比如高并发，海量数据读取   
- Nosql读写能力强   
- Nosql技术还在不断的快速发展，功能没有关系型数据库成熟强大   

### 查找操作

#### mysql
select 字段名　from 表名　where 条件

#### mongodb
##### find()
db.collection.find(query, field)  

功能: 查找文档

参数
```mongo
query 查找条件，相当与where子句
    以键值对的方式传递参数，如果是空{}表示查找内容
field 查找的域
    以键值对的方式传递参数，给出要查找（不查找的域），以域名为键，以0，1为值表示不查找，查找
```

返回值: 查找到的所有的文档

- 如果某一个或者多个域设置为0表示这些域不查找，其他域均查找   
- 如果某一个或者多个域设置为1表示这些域查找，其他域均不查找， id除非设置为0，则否均会查找   
- 除_id域其他域不能有的设置为1有的设置为0   

示例
```mongo
查找结果只有name域
    db.class0.find({'sex': '男'}, {_id:0, name:1})
```
查找所有内容  
```mongo
db.collection.find()　　－－－－＞　select * from table
```
通过find查找结果，可以使用序列号获取具体某一项
```mongo
获取查找结果中的第二项
db.class.find({},{_id:0, hobby:0})[1]
```

##### findOne()
findOne(query, field)
功能: 查找第一条符合条件的文档   
参数: 同find   
返回值: 返回查找到的文档   
示例   
```mongo
db.class0.findOne({sex: '男'}, {'name': 1, _id:0, age:1})
```
##### query更多的筛选用法
操作符
```mongo
使用$注明的特殊字符串，表达一定的含义，比如'$lt'表示小于

比较操作符使用
    $eq  等于 ==
        示例：db.class0.find({age:{$eq:19}})

    $ne  不等于　!=
        示例：db.class0.find({age:{$ne:18}},{_id:0})

    $lt  小于　　<
        示例：db.class0.find({age:{$lt:19}})

    $lte  小于等于  <=
        示例：db.class0.find({age:{$lte:18}},{_id:0})

    $gt　大于     >
        示例：db.class0.find({age:{$gt:17}}, {_id:0})

    $gte  大于等于  >=
        示例: db.class0.find({age:{$gte:17}}, {_id:0})

    $in  包含
        示例：db.class0.find({age:{$in:[17,18,19]}}, {_id:0})

    $nin 不包含
        示例： db.class0.find({age:{$nin:[17,18]}}, {_id:0})

    综合使用
        年龄大于16，小于19的信息
             db.class0.find({age:{$gt:16, $lt:19}}, {_id:0})

    ＊　在mongodb中字符串可以比较大小
    ＊　在mongodb中所有的{} []　都可以写多个条件，但根据参数的不同表达的意思不一样
    ＊　使用ne查找也会找到该域不存在的文档

逻辑操作符
    $and
        1. 在query中如果写多个条件默认即为and关系

        2.　逻辑与 $and
            db.class0.find({$and:[{age:{$gt:14}}, {sex:'男'}]})

    $or
        1. 年龄小于16　或　年龄大于18
            db.class0.find({$or:[{age:{$lt:16}}, {age:{$gt:18}}]})

    $not
         db.class0.find({sex:{$not:{$eq:'m'}}})
         db.class0.find({age:{$not:{$gt:14}}}, {_id:0})

    $nor  既不是也不是
       既不是18岁，也不是男的
        　  db.class0.find({$nor:[{age:18}, {sex:'男'}]})

    逻辑条件混合
        年龄大于17岁并且为男性或者姓名叫Abby

            db.class0.find({$or:[{age:{$gt:17}, sex:'男'}, {name: 'Abby'}]})

        年龄不大于18　或者为女性，并且名字叫Lucy
            db.class0.find({$or:[{age:{$lte:18}}, {sex:'女'}]}, {_id:0})
            db.class0.find({$or:[{age:{$lte:18}}, {sex:'女'}], name:"Lucy"}, {_id:0})
            db.class0.find({$and:[{$or:[{age:{$lte:18}}, {sex:'女'}]}, {name:"Lucy"}]}, {_id:0})
```

##### Array
[1, 2, 3, 4, 5]
```mongo
* 数组是有序是数据集合
* mongo中数组也可以有多种数据元素混合

查找数组中包含某一条件的元素
    db.class1.find({socre:{$lt:60}}, {_id:0})

$all
查找数组中同时包含多项的文档
    db.class1.find([score:{$all:[49,67]}])

$size
通过数组元素个数查找
    db.ccc.find({score:{$size:2}}, {_id:0})

$slice
显示数组中指定项
    显示两项
        db.ccc.find({},{_id:0, score:{$slice:2}})
    显示跳过第一个显示后面两个
        db.ccc.find({},{_id:0, score:{$slice:[1,2]}})

$exists
查找某个域是否存在筛选
    db.ccc.find({sex:{$exists:false}},{_id:0})

$mod
余数查找
    { field: { $mod: [ divisor, remainder ] } }
找出年龄为单数的文档
    db.ccc.find({age:{$mod:[2,1]}}, {_id:0})

$type
找出指定数据类型的文档
找出name域值类型为2的文档
    db.ccc.find({name:{$type:2}},{_id:0})
```

##### 查找结果的操作函数
```mongo
db.collection.distinct(field)
功能
    查看某个域的值范围
示例
    db.ccc.distinct('name')


pretty()
功能
    格式化显示查询结果
示例
    db.ccc.find().pretty()


limit(n)
功能
    显示前n条结果
示例
    db.ccc.find().limit(2)


skip(n)
功能
    跳过前n条显示，显示后面的查询结果
示例
    db.ccc.find({},{_id:0}).skip(2)


count()
功能：
    统计查询结果数量
统计性别为w的文档个数
    db.ccc.find({sex:'w'}, {_id:0}).count()


sort({field:1/-1})
功能
    对查找结果排序
参数
    以键值对表示按照哪个field排序
    1 表示升序
    -1 表示降序
示例
    按照年龄升序排序
        db.ccc.find({},{_id:0}).sort({age:1})
复合排序
    # 按照年龄升序排序，年龄相同时按照分数升序排序
    db.ccc.find({},{_id:0}).sort({age:1, score: 1})
```
练习

1. 创建数据名称 grade
2. 创建集合　class
3. 集合中插入若干文档，文档格式

    {name:'zhangsan', age:10, sex:'m', hobby:['a', 'b']}

    年龄范围: 6-15   

    爱好选择: draw sing dance basketball football pingpong computer   

    每个同学选择2-5项   

4. 查找练习
```mongo
查看班级所有学生信息
    db.class.find()
查看班级中年龄为8岁的学生信息
    db.class.find({age:8}, {_id:0})
查看班级中年龄大于10岁的学生信息
    db.class.find({age:{$gt:10}}, {_id:0})
查看班级中年龄在8-11岁之间的学生信息
    db.class.find({$and:[{age:{$gte:8}}, {age:{$lte:11}}]},{_id:0, hobby:0})
查看班级中年龄为10岁且为男性的学生信息
    db.class.find({$and:[{age:10}, {sex:'m'}]},{_id:0,hobby:0})
查看班级中小于7岁或者大于14岁的学生信息
    db.class.find({$or:[{age:{$lt:7}}, {age:{$gt:14}}]}, {_id:0, hobby:0})
查看班级年龄为8岁或者11岁的学生信息
    db.class.find({$or:[{age:8}, {age:11}]},{_id:0, hobby:0})
找到有2项兴趣爱好的学生
    db.class.find({hobby:{$size:2}},{_id:0})
找到兴趣中有draw的学生
    db.class.find({hobby:'draw'},{_id:0})
找到即喜欢画画又喜欢跳舞的学生
    db.class.find({hobby:'dance', hobby:'draw'},{_id:0})
统计兴趣有４项的学生人数
    db.class.find({hobby:{$size:4}},{_id:0}).count()
找出本班年龄第二大的学生
    db.class.find({},{_id:0}).sort({age:-1}).skip(1).limit(1)
查看本班学生兴趣爱好涵盖哪些方面
    db.class.distinct('hobby')
找到年龄最大的三个学生
    db.class.find({},{_id:0}).sort({age:-1}).limit(3)
删除所有年龄大于16或者小于7岁的学生除非他的爱好有三项以上
    db.class.find({$and:[{$or:[{age:{$gt:16}}, {age:{$lt:7}}]}, {hobby:{$size:2}}]}, {_id:0})
```

答案

```
创建数据库
    use grade

插入
    db.class.insert([
    {name:'zhangsan', age:10, sex:'m', hobby:['draw', 'sing', 'dance']},
    {name:'lisi', age:5, sex:'m', hobby:['draw', 'sing', 'dance', 'computer']},
    {name:'wangwu', age:15, sex:'m', hobby:['pingpong', 'computer']},
    {name:'阿宝', age:8, sex:'m', hobby:['pingpong', 'computer']},
    {name:'阿蓉', age:14, sex:'w', hobby:['pingpong', 'computer', 'basketball']},
    {name:'阿喆', age:10, sex:'m', hobby:['dance', 'computer', 'basketball', 'football']},
    {name:'百合', age:18, sex:'w', hobby:['dance', 'computer', 'basketball', 'football']},
    ])
```

###  删除文档
#### mysql
```mysql
delete from 表名 where 条件;
删除字段
    alter table 表名 drop 字段名;
```

#### mongodb
```mongo
db.collection.remove(query, justOne)
功能
    删除文档
参数
    query 用法同查找
    justOne  布尔值
            默认为false表示删除所有符合条件的文档，设置为true则表示只删除一条文档
示例
    删除所有不存在sex域的文档
        db.ccc.remove({sex:{$exists: false}})
    删除一条name为'阿宝'的文档
        db.ccc.remove({name:{$eq:'阿宝'}}, true)
    删除ccc集合中所有文档
        db.ccc.remove({})
```


### 修改文档
#### mysql
```mysql
update table 表名　set 字段＝值 where ..
```

#### mongodb
```mongo
db.collection.update(query, update, upsert, multi)

update(query, update, upsert, multi)
功能
    修改文档
参数
    query   筛选条件　用法同find
    update 　要修改成什么内容，通常配合修改操作符()使用
            $set  修改器
    upsert  如果是bool值，默认是false，如果query没有筛选到文档则不做任何操作
            如果设置为true,　则如果query没有筛选到文档则根据query和update
            内容插入新的文档
    multi   布尔值，默认为false,　表示有多条符合条件文档，则修改第一条
            如果设置为true,　表示则修改所有符合条件文档
示例
    将'阿蓉'的sex改成'女'
        db.class.update({name:'阿蓉'}, {$set:{sex:'女'}})
    没有小陈则插入一条文档
        db.class.update({name:'小陈'}, {$set:{sex:'男'}}, true)
    将［所有］女性的年龄改为18
        db.class.update({sex:'女'}, {$set:{age:18}}, true, true)
```
##### 修改操作符(修改器)
```
$set
    修改一个域的值

    当文档中不存在的时候会自动增加一个域

$unset
    删除一个域

$rename
    将性别改成gender
        db.class.update({},{$rename:{sex:'gender'}},false,true)

$setOnInsert
    如果使用update插入了文档，则将修改器内容作为插入文档的一部分
        db.class.update({name:'Jame'}, {$set:{age:18}, $setOnInsert:{gender:'男'}}, true)

$inc
    加法修改器
        将所有年龄小于17的人的年龄加1
            db.class.update({age:{$lt:17}},{$inc:{age:1}}, false, true)

$mul
    乘法修改器
        将所有年龄乘以两倍
            db.class.update({},{$mul:{age:2}},false,true)

$min
    如果筛选文档的指定域值小于min值则不修改，大于min值则修改为min值
        所有人的如果年龄大于10则修改为10
            db.class.update({},{$min:{age:10}}, false,true)

$max
    如果筛选文档的指定域值大于max值则不修改，小于max值则修改为max值
        所有人的如果年龄小于15则修改为15
            db.class.update({},{$max:{age:15}}, false,true)

数组修改器
$push
    向数组中添加一项
         db.class1.update({name:'小红'},{$push:{score:100}})

$pushAll
    向数组中添加多项
        db.class1.update({name:'小乔'},{$pushAll:{score:[100,99]}})

$pull
    从数组中删除一项
        db.class1.update({name:'小红'},{$pull:{score:100}})

$pullAll
    向数组中删除多项
        db.class1.update({name:'小乔'},{$pullAll:{score:[100,99]}})

$each
    对多个值逐个进行操作
        分别插入99，10
        db.class1.update({name:'小乔'},{$push:{socre:{$each:[99, 10]}}})

$position
    指定插入位置
        db.class1.update({name:'小明'},{$push:{score:{$each:[67], $position:1}}})

$sort
    数组排序
    将含有score的文档score数组排序
        db.class1.update({},{$push:{score:{$each:[],$sort:1}}}, false, true)
$pop
    弹出一项
        1表示弹出最后一项，-1表示弹出第一项

        弹出小乔的最后一项
            db.class1.update({name:'小乔'},{$pop:{score:1}})

$addToSet
    向数组中添加一项，但是不能添加重复的内容
        给小刚添加一项,如果数组中有88则不添加
            db.class1.update({name:'小刚'}, {$addToSet:{score:88}})
···
```

练习
```
1. 将小红年龄改为12岁,兴趣爱好变为跳舞画画
    db.exe.update({'name': '小红'}, {$set:{'hobby': ['跳舞', '画画']}})
2. 追加小明爱好唱歌
    db.exe.update({'name':'小明'},{$push:{'hobby':'唱歌'}})
3. 追加小王兴趣爱好吹牛,打篮球
    db.exe.update({'name':'小王'}, {$pushAll:{'hobby':['吹牛', '打篮球']}})
4. 小李兴趣多了跑步和唱歌,但是要确保和以前不重复
    #db.exe.update({'name':'小李'}, {$addToSet:{$each:['唱歌', '跳舞']}})
5. 将班级所有男同学年龄加1
    db.exe.update({sex:'男'}, {$inc:{age:1}}, false, true)
6. 删除小明的sex属性
    db.exe.update({'name':'小明'},{$unset:{sex:''}})
7. 修改小刘的年龄为15, 如果不存在该同学则添加,同时套添加兴趣爱好和性别男
    db.exe.update({'name':'小刘'},{$set:{age:15},$setOnInsert:{sex:'男', hobby:['跳舞']}})
8. 删除小李兴趣中的第一项
    db.exe.update({'name':'小李'}, {$unset: {'hobby.0':''}})
9. 删除小红爱好中画画和跳舞
    db.exe.update({'name':'小红'}, {$pullAll: {hobby:['画画','跳舞']}})

db.exe.insert([
    {'name': '小红', 'age': 18, 'sex': '女', 'hobby': ['跳舞']},
    {'name': '小明', 'age': 17, 'sex': '男', 'hobby': []},
    {'name': '小王', 'age': 19, 'sex': '男', 'hobby': []},
    {'name': '小李', 'age': 18, 'sex': '男', 'hobby': ['唱歌']},
    {'name': '小刘', 'age': 16, 'sex': '男', 'hobby': ['唱歌']}
])
```