


### 字节对齐


1. 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；

备注：编译器在给结构体开辟空间时，首先找到结构体中最宽的基本数据类型，然后寻找内存地址能被该基本数据类型所整除的位置，作为结构体的首地址。将这个最宽的基本数据类型的大小作为上面介绍的对齐模数。

2. 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节（internal adding）；

备注:为结构体的一个成员开辟空间之前，编译器首先检查预开辟空间的首地址相对于结构体首地址的偏移是否是本成员的整数倍，若是，则存放本成员，反之，则在本成员和上一个成员之间填充一定的字节，以达到整数倍的要求，也就是将预开辟空间的首地址后移几个字节。

3. 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要，编译器会在最末一个成员之后加上填充字节（trailing padding）。

```cpp
class A { int a = 1; short b = 1; int c = 1; char d = 'A'; };  // 16
class B { double a = 1; short b = 1; int c = 1; char d = 'A'; };  // 24
```


### 数组初始化

1. 未初始化的全局数组为0；
2. 未初始化的局部数组为随机值；
3. 初始化部分的全局数组与局部数组，初始化部分为初始化值，未初始化部分都为0；（不管全局还是局部）

### 逗号表达式

`int a,b;b=(a=3*5,a*4,a*5); printf("%d",b);`

逗号表达式是将括号中所有表达式的值算出来，但是只使用最后一个表达式。


### 构造函数初始化列表

```cpp
// 下面的程序输出可能是什么?
class Printer{
    public:
        Printer(std::string name) {std::cout << name;}
};
class Container{
    public:
        Container() : b("b"), a("a") {}
    Printer a;
    Printer b;
};
int main(){
    Container c;
    return 0;
}
```

初始化列表要注意，这道题故意写成b("b"), a("a") ，其实还是按类中声明变量的先后顺序来初始化，与初始化列表的顺序无关。


### 数组指针, 指针数组

```cpp
int a = 1, b = 2;
int arr[2]{1, 2};
int* p[2] = {&a, &b};
int(*q)[2] = &arr;
```


