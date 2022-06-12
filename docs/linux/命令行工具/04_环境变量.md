
功能说明：设置或显示环境变量。

语法：export [-fnp][变量名称]=[变量设置值]

- f 　代表[变量名称]中为函数名称。
- n 　删除指定的变量。变量实际上并未删除，只是不会输出到后续指令的执行环境中。 ( export -n KKK )
- p 　列出所有的shell赋予程序的环境变量  ( export -p )

export设置环境变量是暂时的，只在本次登录中有效，可修改如下文件来使命令长久有效

针对所有用户：

- vi /etc/profile

在里面加入 export PATH="$PATH:/your/path"

针对当前登录用户：

- vi `/home/curuse/.bash_profile`

在里面加入  export PATH="$PATH:/your/path"

PATH表示原先设定的路径 仍然有效，注意不要漏掉。

某些软件可能还有“PATH”以外类型的环境变量需要添加，但方法与此相同，并且也需要注意“$”

注意：

1、执行脚本时是在一个子shell环境运行的，脚本执行完后该子shell自动退出；

2、一个shell中的系统环境变量才会被复制到子shell中（用export定义的变量）；

3、一个shell中的系统环境变量只对该shell或者它的子shell有效，该shell结束时变量消失（并不能返回到父shell中）。

4、不用export定义的变量只对该shell有效，对子shell也是无效的。


