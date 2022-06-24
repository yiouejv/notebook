

有些游戏为了防止在运行的过程中被截图，从而开启了安卓的 `FLAG_SECURE` 功能，禁止截图, 从而增加了一些图色脚本的难度。

下面记录一下破解的过程，需要安装 xposed 框架。

Xposed（也被称作Xposed框架、XP框架、Xposed framework），是一个运行于Android操作系统的钩子框架。

其通过替换Android系统的关键文件，可以拦截几乎所有Java函数的调用，并允许通过Xposed模块中的自定义代码更改调用这些函数时的行为。

因此，Xposed常被用来修改Android系统和应用程序的功能。

## 安装 xposed 框架

`系统/XposedInstaller_3.1.5.apk`

安装过程需要下载东西，下载的东西在国外的服务器上，需要翻墙

## 安装 DisableFlagSecure

打开 xposedInstall 软件，从 `menu->下载` 安装 DisableFlagSecure 模块, 安装完启动

## 其他插件

- XPrivacy: 隐私管理
