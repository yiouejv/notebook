
<h3>查询系统版本</h3>

- 查看Linux系统版本:

```
$uname -a
$lsb_release -a
```

<h3>查询CPU信息</h3>

```
$cat /proc/cpuinfo
```

- 查看CPU的核的个数:

```
$cat /proc/cpuinfo | grep processor | wc -l
```

<h3>查看内存信息</h3>

```
$cat /proc/meminfo
```

- 显示架构:

```
$arch
```

<h3>设置系统时间</h3>

- 显示当前系统时间

```
$date
```

- 设置系统日期和时间(格式为2014-09-15 17:05:00)

```
$date -s 2014-09-15 17:05:00
$date -s 2014-09-15
$date -s 17:05:00
```

- 设置时区

选择时区信息。命令为：tzselect

根据系统提示，选择相应的时区信息。

强制把系统时间写入CMOS（这样，重启后时间也正确了）:

$clock -w
