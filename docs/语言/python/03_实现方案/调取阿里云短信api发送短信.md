
### python 调取阿里云短信api发送短信

#### 用途
报警，告知，每日定时发送消息等，用途太多

#### 实现方式，两种都可以

##### 使用阿里云的core模块，不用sms的模块
```python
# 需要安装的的模块
pip install aliyun-python-sdk-core
```
```python
#!/usr/bin/env python
#coding=utf-8
from aliyunsdkcore.client import AcsClient
from aliyunsdkcore.request import CommonRequest
import json
 
accessKeyId="accessKeyId"
accessSecret="accessSecret"
phone='电话'
SignName="短信模板"
TemplateCode="短信签名"
 
#data是内容，里面变量是阿里云短信模板的变量，几个就写几个
data={
    "hostname":"我是内容",
    "message":""
}
 
client = AcsClient(accessKeyId, accessSecret, 'default')
request = CommonRequest()
request.set_accept_format('json')
request.set_domain('dysmsapi.aliyuncs.com')
request.set_method('POST')
request.set_version('2017-05-25')
request.set_action_name('SendSms')
request.add_query_param('PhoneNumbers', phone)
request.add_query_param('SignName', SignName)
request.add_query_param('TemplateCode', TemplateCode)
request.add_query_param('TemplateParam', json.dumps(data))
response = client.do_action_with_exception(request)
print(response)
```

##### 通过阿里云的短信api模块+core模块实现
```python
需要安装的模块 aliyun-python-sdk-core以及dysms

aliyun-python-sdk-core直接可以pip安装

dysms是通过https://help.aliyun.com/找到下载地址，然后找到sdk下载地址

目前下载地址是dysms_python.zip

然后 python setup.py install执行安装
```
```python
#!/usr/bin/env python
#coding=utf-8
from aliyunsdkcore.client import AcsClient
from aliyunsdkdysmsapi.request.v20170525.SendSmsRequest import SendSmsRequest
from aliyunsdkcore.profile import region_provider
import json
 
REGION = "cn-hangzhou"
PRODUCT_NAME = "Dysmsapi"
DOMAIN = "dysmsapi.aliyuncs.com"
 
accessKeyId="accessKeyId"
accessSecret="accessSecret"
SignName="短信模板"
TemplateCode="短信签名"
phone='发送的电话号码'
data={
    "fail_reason":"我是内容",
    "telephone": phone
}
 
client = AcsClient(accessKeyId, accessSecret,REGION)
region_provider.add_endpoint(PRODUCT_NAME, REGION, DOMAIN)
request = SendSmsRequest()
request.set_PhoneNumbers(phone)
request.set_SignName(SignName)
request.set_TemplateCode(TemplateCode)
request.set_TemplateParam(json.dumps(data))
 
response = client.do_action_with_exception(request)
print(response)
```
##### 需要修改的参数说明
- accessKeyId ：阿里云控制台登录具有短信管理权限的账号的编程accessKeyId
- accessSecret：阿里云对应accessKeyId的accessSecret
- phone       ：需要发送给对方的电话
- SignName    ：  短信模板，需要审核通过的
- TemplateCode：短信签名，需要审核通过的
- data        ：一个json，对应的键名是短信模板里面定义的变量，定义几个变量，这里就写几个对应的值