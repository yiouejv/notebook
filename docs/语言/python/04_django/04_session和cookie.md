## session 和 cookie

## django 中使用 cookies

- 设置cookies 的值（将数据保存到客户端）

  语法：**响应对象.set_cookie(key, value, expires)**

  ```python
  # 不使用模板
  resp = HttpResponse('xxx')
  resp.set_cookie(key, value, expires)
  return resp
  
  # 使用模板
  resp = render(request, 'xxx.html', context)
  resp.set_cookie(key, value, expires)
  return resp
  
  # 使用重定向
  resp = redirect(request, 'xxx.html')
  resp.set_cookie(key, value, expires)
  return resp
  ```

- 获取cookies 的值

  伴随请求对象到达服务器后再获取cookie的值
  request.COOKIES:  封装了当前访问站点下所有cookie的信息

- 删除cookie 的值

  - 客户端：清除浏览器cookie
  - 服务端：resp.delete_cookie(key)

## django 中使用 session

- 设置session的值（将数据保存到服务端）

  语法：**request.session['key'] = value**

- 获取session 的值

  ```python
  request.session['key']
  request.session.get('key')
  ```

- 删除session的值

  ```python
  del request.session['key']
  ```

- 有关 session 的配置

  在 `settings.py` 中有关session的设置	

  - `SESSION_COOKIE_AGE`  设置sessionID在cookies中的存活时间

    ```python
    SESSION_COOKIE_AGE = 60*30  # 30s
    ```

  - `SESSION_EXPIRE_AT_BROWSER_CLOSE`  设置浏览器关闭时则清除服务器上对应的session空间

    ```python
    SESSION_EXPIRE_AT_BROWSER_CLOSE = True
    ```

    

