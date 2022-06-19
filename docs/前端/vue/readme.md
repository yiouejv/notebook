
## vue 源码

<a href="../vue3.js">vue.js</a>

## 简单的vue应用

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="counter">
        <p>{{ num }}</p>
        <p>{{ name }}</p>
    </div>
    <script>
        const Counter = {
            data:function() {
                return {
                    num : 0,
                    name : "xxx",
                }
            }
        }
        var app = Vue.createApp(Counter).mount("#counter")  // mount 挂载
    </script>
</body>
</html>
```

## 指令

指令 (Directives) 是带有 v- 前缀的特殊 attribute。指令 attribute 的值预期是单个 JavaScript 表达式 (v-for 和 v-on 是例外情况，稍后我们再讨论)。

指令的职责是，当表达式的值改变时，将其产生的连带影响，响应式地作用于 DOM。

```html
<p v-if="seen">现在你看到我了</p>
```

这里，v-if 指令将根据表达式 seen 的值的真假来插入/移除 <p> 元素。

### v-once

通过使用 v-once 指令，你也能执行一次性地插值，当数据改变时，插值处的内容不会更新。

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <p>{{ name }}</p>
        <p v-once>{{ name }}</p>
        <button @click="clickChangeName">改变名字</button>
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    name : "yiouejv",
                };
            },
            methods: {
                clickChangeName: function() {
                    this.name = "yangxiaoge"
                },
            },
        }).mount("#app");
    </script>
</body>
</html>
```

### v-html

双大括号会将数据解释为普通文本，而非 HTML 代码。为了输出真正的 HTML，你需要使用v-html 指令

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <p>{{ msg }}</p>
        <p v-html="msg"></p>
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    msg : "<h2>title</h2>",
                };
            },
        }).mount("#app");
    </script>
</body>
</html>
```

### 动态绑定属性的内容

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <img v-bind:src="src">
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    src : "https://img12.360buyimg.com/seckillcms/s750x360_jfs/t1/214447/10/20191/15346/62aaf7c9Ec0432cd2/ea3e421343a22f9c.jpg!cc_750x360.webp",
                };
            },
        }).mount("#app");
    </script>
</body>
</html>
```

## 计算属性

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <p>{{ msg }}</p>
        <p>{{ reverseMsg }}</p>
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    msg : "hello world",
                };
            },
            computed: {
                reverseMsg : function() {
                    return this.msg.split("").reverse().join("")
                },
            },
        }).mount("#app");
    </script>
</body>
</html>
```

计算属性, 只要依赖值不变, 那么就不会重新计算。

## 侦听器

虽然计算属性在大多数情况下更合适，但有时也需要一个自定义的侦听器。

这就是为什么 Vue 通过 watch 选项提供了一个更通用的方法来响应数据的变化。

当需要在数据变化时执行异步或开销较大的操作时，这个方式是最有用的。

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <p>{{ msg }}</p>
        <button @click="msg='你好'">改变</button>
        <input v-model="msg">
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    msg : "hello world xxxx",
                };
            },
            watch: {
                msg : {
                    immediate : true,  // 初始化的时候调用函数
                    handler : function(newValue, oldValue) {
                        console.log(newValue);
                        console.log(oldValue);
                        // 执行异步操作，或者复杂逻辑代码
                        if (newValue.length < 5 || newValue.length > 10) {
                            console.log("tips")
                        }
                    },
                    deep : true,  // 深度监听，会监听到对象内部属性的变化
                },
            },
        }).mount("#app");
    </script>
</body>
</html>
```

## Class 与 Style 绑定

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
    <style type="text/css">
        .active {
            color : blue;
            font-size : 18px;
        }
        .default {
            font-weight : bold;
        }
    </style>
</head>
<body>
    <div id="app">
        <p :class="{ active: isActive }" class="default">{{ msg }}</p>
        <p :class="classObj" class="default">{{ msg }}</p>
        <p :class="calcClassObj" class="default">{{ msg }}</p>
        <button @click="isActive=!isActive">改变</button>
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    msg : "hello world xxxx",
                    isActive : true,
                    error : false,
                    classObj : {
                        active : true,
                    }
                };
            },
            computed : {
                calcClassObj : function() {
                    return { active : this.isActive && !this.error };
                }
            },
        }).mount("#app");
    </script>
</body>
</html>
```

## v-if

v-if 指令用于条件性地渲染一块内容。这块内容只会在指令的表达式返回 truthy 值的时候被渲染。

也可以用 v-else 添加一个“else 块”：

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <p v-if="age > 18">我是个成年人</p>
        <p v-else-if="age==18">我今天正好18</p>
        <p v-else>我是个小朋友</p>
        <button @click="age=18">改变年龄为18</button>
    </div>

    <script>
        let app = Vue.createApp({
            data : function() {
                return {
                    age : 13,
                };
            }
        }).mount("#app")
    </script>
</body>
</html>
```

在 <template> 元素上使用 v-if 条件渲染分组

因为 v-if 是一个指令，所以必须将它添加到一个元素上。但是如果想切换多个元素呢？此时可以把一个 <template> 元素当做不可见的包裹元素，并在上面使用 v-if。最终的渲染结果将不包含 <template> 元素。

```html
<template v-if="ok">
  <h1>Title</h1>
  <p>Paragraph 1</p>
  <p>Paragraph 2</p>
</template>
```

## v-for

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>title</title>
    <script src="vue3.js"></script>
</head>
<body>
    <div id="app">
        <ul>
            <li v-for="(person, index) in persons" :key="index">
                {{person}} -- {{index}}
            </li>
            <li v-for="(value, key, index) in obj" :key="index">
                {{ value }} -- {{ key }} -- {{ index }}
            </li>
        </ul>
    </div>

    <script>
        let app = Vue.createApp({
            data : function() {
                return {
                    persons : ["xxx1", "xxx2", "xxx3"],
                    obj : {
                        name : "xxx",
                        age : 18,
                    },
                };
            }
        }).mount("#app")
    </script>
</body>
</html>
```
