

1、卸载python2.7
```
sudo apt-get remove python2.7
```

2、卸载python2.7及其依赖

```
sudo apt-get remove --auto-remove python2.7
```

3、清除python2.7
```shell
sudo apt-get purge python2.7
or
sudo apt-get purge --auto-remove python2.7
```
注释： 
此方法卸载python比较彻底，所以适合更换python版本时使用。 
——对于既想完全卸载python，又无法接受完全卸载后某些python组件无法使用的童鞋，请慎重！！