
最常用的 Linux 包管理命令都被分散在了 apt-get、 apt-cache 和 apt-config 这三条命令当中。

apt 命令的引入就是为了解决命令过于分散的问题，它包括了 apt-get 命令出现以来使用最广泛的功能选项，以及 apt-cache 和 apt-config 命令中很少用到的功能。

在使用 apt 命令时，用户不必再由 apt-get 转到 apt-cache 或 apt-config，而且 apt 更加结构化，并为用户提供了管理软件包所需的必要选项。

简单来说就是：apt = apt-get、apt-cache 和 apt-config 中最常用命令选项的集合。

- apt install: apt-get install 安装软件包
- apt remove: apt-get remove 移除软件包
- apt purge: apt-get purge 移除软件包及配置文件
- apt update: apt-get update 刷新存储库索引
- apt upgrade: apt-get upgrade 升级所有可升级的软件包
- apt autoremove: apt-get autoremove 自动删除不需要的包
- apt full-upgrade: apt-get dist-upgrade 在升级软件包时自动处理依赖关系
- apt search: apt-cache search 搜索应用程序
- apt show: apt-cache show 显示装细节


