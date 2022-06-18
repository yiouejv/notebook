
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
    </div>
    <script>
        let app = Vue.createApp({
            data: function() {
                return {
                    msg : "hello world",
                };
            },
            watch: {
                // 每当msg发生变化时都会调用这个函数
                msg : function(newValue, oldValue) {
                    console.log(newValue);
                    console.log(oldValue);
                    // 执行异步操作，或者复杂逻辑代码
                },
            },
        }).mount("#app");
    </script>
</body>
</html>
```
