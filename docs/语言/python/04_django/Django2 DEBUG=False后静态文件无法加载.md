
出现的问题根本原因是：当我们在开发django应用时如果设置了 DEBUG = True，那么django便会自动帮我们对静态文件进行路由；
但是当我们设置DEBUG = False后，这一功能便没有了，此时静态文件就会出现加载失败的情况，想要让静态文件正常显示，
我们就需要配置静态文件服务了。

参考官方文档 https://docs.djangoproject.com/en/2.0/howto/static-files/

### 首先修改项目的setting.py文件

~~~python
STATIC_URL = '/static/'
STATIC_ROOT = 'static' ## 新增行
~~~

### 修改urls.py
~~~python

from django.views import static # 新增
from django.conf import settings # 新增
from django.conf.urls import url  # 新增

urlpatterns = [
  path('', include('user.urls')),  
    # 以下是新增
  	url(r'^static/(?P<path>.*)$', static.serve, {'document_root': settings.STATIC_ROOT}, name='static'),
]
~~~