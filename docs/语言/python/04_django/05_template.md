##  django 中的模板，Templates 

## 模板的定义

模板就是要动态呈现给用户的网页

模板的本质就是网页，前后端， 动静结合的网页

django中的模板引擎是由django自己提供的，而并非Jinja2，所以Django中的模板的语法与flask(Jinja2)的语法会稍有不同

##  Django模板的设置 

在setting.py中设置 TEMPLATES 的变量

```python
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]
```

**参数说明**

 `BACKEND` ： 指定使用的模板的引擎 

 `DIRS` ： 指定模板的存放目录们，一般用根目录下的这种（第一种）

```python
# 在项目的根目录的templates目录中存放所有模板 
DIRS = [os.path.join(BASE_DIR, 'templates')]

# 在项目的index应用中的temp目录中存放模板，以及在项目的music应用中的temp目录中存放模板
DIRS = ['index.temp', 'music.temp']
```

 `APP_DIRS` ： 表示是否自动搜索应用中的目录 ， True: 表示要自动搜索应用中的templates的目录。

##  模板的加载方式 

1.  通过loader 对象获取模板，再通过HttpResponse进行响应

   ```python
   # 先导入loader
   # 通过loader加载模板
   # 将加载好的模板渲染成字符串
   # 通过HttpResponse 将字符串进行响应
   from django.template import loader
   
   def index_view(self, request, *args, **kwargs):
       template = loader.get_template('index.html')
       template = template.render()
   	return HttpResponse(template)
   ```

2.  使用render 直接加载并响应模板 

   ```python
   return render(request, "name")
   ```

## 模板的语法

### 变量

作用： 将后端的数据传递到模板上进行显示。

数据类型： 字符串,  整数,  列表,  元祖,  字典,  函数对象。

语法规范：变量必须要封装到字典中参能传递给模板。

```python
# views.py
def var(request):
    context = {
        'name': '王老师',
        'age': 30,
        'gender': '男',
        "message": '天下没有吃不散的宴席',
        'tuple': ('王老师', 'MrRang', 'Rap Wang'),
        'list': ['!!!!!', '@@@@@', '#####'],
        'dic': {
            'bj': '北京',
            'sy': '沈阳',
            'cc': '长春',
        },
        'show_message': show_message,
        'dog': Dog(name='旺财'),
        'lst': [1, 2, 3, 4, 5, 6]
    }
    return render(request, "two_day/var.html", context)

#var.html
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>变量演示</title>
</head>
<body> 
    {% comment "注释name" %}
        <h3>喜欢的一句话: {{ message }}</h3>
    {% endcomment %}

    <h3>姓名：{{ name }}</h3>
    <h3>年龄：{{ age }}</h3>
    <h3>性别：{{ gender }}</h3>
    <h3>tuple[0]: {{ tuple.0 }}</h3>
    <h3>tuple[1]: {{ tuple.1 }}</h3>
    <h3>tuple[2]: {{ tuple.2 }}</h3>
    <h3>list[0]: {{ list.0 }}</h3>
    <h3>{{ dic.bj }}</h3>
    <h3>{{ show_message }}</h3>
    <h3>{{ dog.name }}</h3>
    <h3>{{ dog.age }}</h3>
    <h3>{{ dog.eat }}</h3>

    {% for l in list %}
        {% if forloop.first %}
            <h2 style="background: red;">
        {% elif forloop.last %}
            <h2 style="background-color: yellow;">
        {% else %}
            <h2 style="background-color: pink;">
        {% endif %}
            <p>姓名{{ l }}</p>
            <p>counter: {{ forloop.counter }}</p>
            <p>counter0: {{ forloop.counter0 }}</p>
            <p>revcounter: {{ forloop.revcounter }}</p>
            <p>revcounter0: {{ forloop.revcounter0 }}</p>
        </h2>
    {% endfor %}

    {% for l in lst %}
        {% if forloop.counter|divisibleby:"2" %}
            <p style="background-color: red">{{ l }}</p>
        {% else %}
            <p>{{ l }}</p>
        {% endif %}
    {% endfor %}
</body>
</html>
```

### 标签

作用：将服务器的功能嵌入到模板中。

语法：

```python
{% 标签名 %}

{% end标签名 %}
```

常用的标签

```python
if
    {% if %}

    {% elif %}

    {% else %}

    {% endif %}
for
    {% for 变量 in iterable %}

    {% endfor %}
    
    内置变量 forloop
    在循环中允许使用forloop内置变量来获取循环的信息
    forloop.counter: 记录当前循环遍历的次数
    forloop.counter0: 记录当前循环遍历的次数，从0开始
    forloop.revcounter: 记录当前元素从后向前算的位置
    forloop.revcounter0: 记录当前元素从后向前算的

    forloop.first: 判断是否是第一次的循环
    forloop.last: 判断是否是最后一次的循环
```

### 过滤器

作用： 在变量输出之前，对变量的数据进行筛选和过滤 。

语法： {{ 变量|过滤器:参数 }} 

常用过滤器:

​	 (其他需求可以参考官网，也可以自己定义过滤器)

```python
{{ value | upper }}
	将value转为大写
{{ value | lower }}
	将value转为小写
{{ value | add:num }}
	将num追加到value之后, value 和 num 可以是列表
{{ value | truncatechars:n }}
	将value截取n为字符，后面以...来显示
```

### 静态文件的处理

定义：无法与服务器进行动态交互的文件。

django中静态文件的处理：在`setting.py`中设置有关静态文件的信息

1. 设置静态文件的访问路径

   在浏览器中通过那个地址能够找到静态文件

   ```python
   STATIC_URL = '/static/'
   ```


   如果访问路径是 http://localhost:8000/static/...，一律都按照静态文件的方式去查找，不经过路由

2. 设置静态文件的存储路径

    指定静态文件要保存在服务器上哪个目录处 

   ```python
   STATICFILES_DIRS = (os.path.join(BASE_DIR, 'static'),)
   ```

    静态文件目录的存放位置 : 在项目的根目录去创建一个static，用来保存静态文件

3. 访问静态文件

   1. 直接使用静态文件访问路径进行访问

       http://localhost:8000/static/... 

   2. 使用{% static %} 访问静态资源

      - 在使用之前需要通过{% load static %} 加载static	
      - 使用静态资源时: `<img src="{% static "images/1.jpg" %}">`

## 模板的继承

作用：不同的模板block标签里内容有差别，不在block里的内容原样输出，参数类继承就明白了。

继承语法：

```python
# 父模板
    {% block 名称 %}

    {% endblock %}
# 子模板
    {% extends "父模板的名称" %}
```

反向解析: 路由匹配是通过url找对应的试图函数，反向解析则相反。

```python
# 模板里的反向解析
{% url "name" "arg" "" %}

# 视图里的反向解析
reverse(name, agrs=(arg1, arg2))
```
