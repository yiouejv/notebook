## django中的HttpRequest对象

## 什么是HttpRequest

HttpRequest 对请求对象的封装， 里面封装的是请求过程中的所有信息，在Django中HttpRequest 被封装成`request`对象并封装到视图处理函数中，在调用视图时自动导入

## HttpRequest 中的主要内容

```python
1. request.scheme: 表示请求方案（http或https 通常）的字符串
2. request.post: 请求主体
3. request.path: 请求路径
4. request.get_full_path: 请求完整路径
5. request.get_host(): 请求主机地址 / 域名
6. request.method: 请求方法
7. request.GET: 封裝了get請求方式提交的數據
8. request.POST: 封裝了POST請求方式提交的數據
9. request.cookies: 封裝了 cookies中的所有數據
10. request.META: 封裝了請求的元數據
	request.META.HTTP_REFERER: 封裝了請求的源地址
11. request.FILES: 上传文件的类字典对象
12. request.is_secure(): True如果请求是安全的，则返回; 也就是说，如果它是用HTTPS制作的
13. request.is_ajax(): 返回True如果请求被经由制成XMLHttpRequest
```

## 获取请求提交的数据

### get 请求

- 获取数据

  ```python
  request.GET['名称']
  request.GET.get('名称')
  request.GET.getlist('名称')
  ```

### POST请求

- 获取数据

  ```python
  request.GET['名称']
  request.GET.get('名称')
  request.GET.getlist('名称')
  ```

## request.META

包含所有可用HTTP标头的字典。可用的标头取决于客户端和服务器，以下是一些示例

CONTENT_LENGTH - 请求正文的长度（作为字符串）。

CONTENT_TYPE - 请求正文的MIME类型。

HTTP_ACCEPT - 响应的可接受内容类型。

HTTP_ACCEPT_ENCODING - 可接受的响应编码。

HTTP_ACCEPT_LANGUAGE - 响应的可接受语言。

HTTP_HOST - 客户端发送的HTTP主机头。

HTTP_REFERER - 引用页面，如果有的话。

HTTP_USER_AGENT - 客户端的用户代理字符串。

QUERY_STRING - 查询字符串，作为单个（未解析的）字符串。

REMOTE_ADDR - 客户端的IP地址。

REMOTE_HOST - 客户端的主机名。

REMOTE_USER - Web服务器验证的用户（如果有）。

REQUEST_METHOD- 一个字符串，如"GET"或"POST"。

SERVER_NAME - 服务器的主机名。

SERVER_PORT - 服务器的端口（作为字符串）。

除了CONTENT_LENGTH和之外CONTENT_TYPE，如上所述，请求中的任何HTTP头都将转换为META键，方法是将所有字符转换为大写，用下划线替换任何连字符并HTTP_在名称中添加前缀。因此，例如，调用的标头X-Bender将映射到META密钥 HTTP_X_BENDER。
