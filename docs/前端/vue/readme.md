
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

```
在 <template> 元素上使用 v-if 条件渲染分组

因为 v-if 是一个指令，所以必须将它添加到一个元素上。但是如果想切换多个元素呢？此时可以把一个 <template> 元素当做不可见的包裹元素，并在上面使用 v-if。最终的渲染结果将不包含 <template> 元素。
```

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

## 事件修饰符

在事件处理程序中调用 event.preventDefault() 或 event.stopPropagation() 是非常常见的需求。

尽管我们可以在方法中轻松实现这点，但更好的方式是：方法只有纯粹的数据逻辑，而不是去处理 DOM 事件细节。

为了解决这个问题，Vue.js 为 v-on 提供了事件修饰符。

- .stop
- .prevent
- .capture
- .self
- .once : 只会触发一次
- .passive

```html
<!-- 阻止单击事件继续冒泡 -->
<a @click.stop="doThis"></a>

<!-- 提交事件不再重载页面 -->
<form @submit.prevent="onSubmit"></form>

<!-- 修饰符可以串联 -->
<a @click.stop.prevent="doThat"></a>

<!-- 只有修饰符 -->
<form @submit.prevent></form>

<!-- 添加事件监听器时使用事件捕获模式 -->
<!-- 即内部元素触发的事件先在此处理，然后才交由内部元素进行处理 -->
<div @click.capture="doThis">...</div>

<!-- 只当在 event.target 是当前元素自身时触发处理函数 -->
<!-- 即事件不是从内部元素触发的 -->
<div @click.self="doThat">...</div>
```

### 按键修饰符

在监听键盘事件时，我们经常需要检查特定的按键。Vue 允许为 v-on 或者 @ 在监听键盘事件时添加按键修饰符：

```html
<!-- 只有在 `key` 是 `Enter` 时调用 `vm.submit()` -->
<input @keyup.enter="submit" />
```
Vue 为最常用的键提供了别名：

- .enter
- .tab
- .delete (捕获“删除”和“退格”键)
- .esc
- .space
- .up
- .down
- .left
- .right

## 表单输入绑定

```
你可以用 v-model 指令在表单 <input>、<textarea> 及 <select> 元素上创建双向数据绑定。它会根据控件类型自动选取正确的方法来更新元素。

尽管有些神奇，但 v-model 本质上不过是语法糖。它负责监听用户的输入事件来更新数据，并在某种极端场景下进行一些特殊处理。
```


### 文本 (Text)

```html
你可以用 v-model 指令在表单 <input>、<textarea> 及 <select> 元素上创建双向数据绑定。它会根据控件类型自动选取正确的方法来更新元素。尽管有些神奇，但 v-model 本质上不过是语法糖。它负责监听用户的输入事件来更新数据，并在某种极端场景下进行一些特殊处理。
```

### 复选框 checkbox

#### 单个复选框

单个复选框，绑定到布尔值：

```html
<input type="checkbox" id="checkbox" v-model="checked" />
<label for="checkbox">{{ checked }}</label>
```

#### 多个复选框

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
        <input type="checkbox" id="checkbox" v-model="checked" />
        <h2>{{ checked }}</h2>

        <input type="checkbox" v-model="fruits" value="苹果">苹果
        <input type="checkbox" v-model="fruits" value="西瓜">西瓜
        <input type="checkbox" v-model="fruits" value="葡萄">葡萄
        <input type="checkbox" v-model="fruits" value="哈密瓜">哈密瓜
        <h2>{{ fruits }}</h2>
    </div>

    <script>
        let app = Vue.createApp({
            data : function() {
                return {
                    fruits : [],
                    checked : false,
                };
            }
        }).mount("#app")
    </script>
</body>
</html>
```

### 单选框

```html
<input type="radio" v-model="sex" value="男">男
<input type="radio" v-model="sex" value="女">女
```

### 选项框

#### 单选项框

```html
<select v-model="city">
    <option value="张家界">张家界</option>
    <option value="长沙">长沙</option>
    <option value="益阳">益阳</option>
</select>
<h2>{{ city }}</h2>
```

#### 多选项框

```html
<select v-model="citys" multiple>
    <option value="张家界">张家界</option>
    <option value="长沙">长沙</option>
    <option value="益阳">益阳</option>
</select>
```

## v-model 修饰符

### .lazy

在默认情况下，v-model 在每次 input 事件触发后将输入框的值与数据进行同步 (除了上述输入法组织文字时)。你可以添加 lazy 修饰符，从而转为在 change 事件之后进行同步：

```html title="在“change”时而非“input”时更新"
<input v-model.lazy="msg" />
```

### .number

如果想自动将用户的输入值转为数值类型，可以给 v-model 添加 number 修饰符：

```html title="自动将原始字符串转换为数字"
<input v-model.number="age" type="text" />
```

当输入类型为 text 时这通常很有用。如果输入类型是 number，Vue 能够自动将原始字符串转换为数字，无需为 v-model 添加 .number 修饰符。如果这个值无法被 parseFloat() 解析，则返回原始的值。

### .trim

如果要自动过滤用户输入的首尾空白字符，可以给 v-model 添加 trim 修饰符：

```html title="自动过滤用户输入的首尾空白字符"
<input v-model.trim="msg" />
```
