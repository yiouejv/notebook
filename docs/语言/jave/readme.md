
## 安装java

jdk 安装好之后设置环境变量

Path 增加下面两个

```
D:\Java\jdk1.8.0_111\bin
D:\Java\jdk1.8.0_111\jre1.8.0_111\bin
```

## 安装android sdk

增加两个环境变量

```
D:\Java\android-sdk-windows\tools
D:\Java\android-sdk-windows\platform-tools
```

## 安装ndk

```
D:\Java\android-ndk-r23c
```

## java虚拟机

```java
> 获取虚拟机的默认初始化参数
JNI_GetDefaultJavaVmInitArgs

> 在进程总创建虚拟机实例
JNI_CreateJavaVM

> 获取进程中创建的虚拟机实例
JNI_GetCreeatedJavaVMs
```

判断虚拟机是哪种机制，通过系统目录下的文件类型区分

- jit机制(Dalvik 虚拟机 ==> dex 字节码)：/system/bin/dexopt
- aot机制(ART 虚拟机 ==> 本地机器码): /system/bin/dex2oat


## apk文件结构

- asserts: 静态文件, 用来存放需要打包的Android 应用程序的静态资源文件, 例如图片资源文件，json配置文件，渠道配置文件，二进制数据文件，html5 离线资源文件等。
- res: 该目录下面的文件会生成资源id, 存放应用资源文件。 包括图片资源，字符串资源，颜色资源，尺寸资源等. 这个目录下的资源都会出现在资源清单文件R.java 的索引中
- lib: 文件夹代表的是当前app用到的so文件, 利用c，c++文件实现的。
- META-INF: 所用到的证书签名文件 MANIFEST.MF (摘要文件), 程序遍历apk包中的所有文件，对非文件夹非签名文件的文件，逐个用SHA1 生成摘要信息，再用base64进行编码。如果apk包的文件被修改，在apk安装校验时，被修改的文件与MANIFEST.MF 的校验信息不同，程序将无法正常安装。
- CERT.SF (对摘要文件的签名文件): 对于生成的MANIFEST.MF 文件利用SHA1-RSA 算法对开发者的私钥进行签名。在安装时只有公共密钥才能对其解密。 解密之后将其与未加密的摘要信息进行比对，如果相符则文件没有被修改。
- INDEX.LIST apk 索引文件目录 CERT.RSA 保存公钥，加密算法等信息。
- AndroidManifest.xml: Android 项目的系统清单文件，Android 应用的四大组件(Activity, Serivce, BroadcastReceiver 和 ContentProvider) 均在此配置和声明。
- classes.dex：应用程序的可执行文件。可以看到此app有多个dex，是因为当前的方法数超过65535，进行了分包处理，如果未超过，则只有一个dex。Android 的所有代码都集中在此。可以通过反编译工具dex2jar转化为jar包，再通过jd-gui查看其代码
- resources.arsc: 资源索引表，用来描述具有id值的资源的配置信息.


## apk安装流程

安装过程：

复制apk安装包到data/app目录下，解压并扫描安装包，把dex文件（Dalvik字节码)保存到 dalvik-cache 目录，并data/data 目录下创建对应的应用数据目录

卸载过程：

删除安装过程中上述的三个目录下创建的文件及目录

安装涉及的目录:

- system/app: 系统自带的应用程序，获得adb root 权限才能删掉
- data/app: 用户程序安装的目录，安装时把apk文件复制到此目录
- data/data: 存放应用程序的数据
- data/dalvik-cache: 将apk中的dex文件安装到dalvik-cache 目录下(dex 文件是dalvik 虚拟机的可执行文件, 其大小约为原始apk文件大小的四分之一)

## android 查看启动页

xml 中一起包含这两行配置的是启动页

```
<action android:name="android.intent.action.MAIN"/>
<category android:name="android.intent.category.LAUNCHER"/>
```

cmd 中查看当前置顶的活动页

```
adb devices
adb shell dumpsys activity top
```


## android 四大组件

- activity: 用于表现功能
- service: 后台运行服务, 不提供界面呈现
- Broadcast Recevie: 用于接收广播
- Content Provider: 支持多个应用中存取和读取数据，相当于数据库

### activity

- onCreate(): 在活动第一次创建的时候调用
- onStart(): 活动由不可见变为可见的时候调用
- onResume(): 活动准备好和用户进行交互的时候调用，此时活动一定属于返回栈的栈顶, 并且处于活动状态
- onPause(): 在系统准备去启动或者恢复一个活动的时候调用，通常会在这个方法中将一些消耗cpu的资源释放掉，以及保存一些关键的数据，但是这个方法的执行速度一定要快，不然会影响新的栈顶活动的使用
- onStop(): 在活动完全不可见的时候调用。如果启动的新活动是一个对话框式的活动，执行onPause(), 不执行onStop()
- onDestroy(): 在活动被销毁之前被调用。
- onRestart(): 活动由停止状态变为运行状态之前被调用。
