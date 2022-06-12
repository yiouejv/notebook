
```golang
package main

import "fmt"

func main() {
// 第一种，指定变量类型，如果没有初始化，则变量默认为零值。

    var a string = "test string"
    var b, c int = 1, 2
    fmt.Println(a)
    fmt.Println(b, c)


    // 变量没有初始化则为0
    var d int     // 0
    var e string  // ""
    var f bool    // false
    fmt.Println(d)
    fmt.Println(e)
    fmt.Println(f)

    // 以下几种类型为nil
    var a1 *int
    var a2 []int
    var a3 map[string] int
    var a4 chan int
    var a5 func(string) int
    var a6 error // error 是接口
    fmt.Println(a1, a2, a3, a4, a5, a6)


// 第二种，根据值自行判定变量类型。

    var bb = true
    fmt.Println(bb)


// 第三种，如果变量已经使用 var 声明过了，再使用 := 声明变量，就产生编译错误，格式：

    var aa int
    // aa := 1  // 这时候会产生编译错误，因为 intVal 已经声明，不需要重新声明
    cc := 1
    ff := "Runoob" // var f string = "Runoob"
    fmt.Println(aa, cc, ff)


    //类型相同多个变量, 非全局变量
    var vname1, vname2, vname3 int
    vname1, vname2, vname3 = 1, 2, 3

    var vname11, vname22, vname33 = 1, 2, 3 // 和 python 很像,不需要显示声明类型，自动推断

    // 出现在 := 左侧的变量不应该是已经被声明过的，否则会导致编译错误
    // 这种不带声明格式的只能在函数体中出现
    vname111, vname222, vname333 := 1, 2, 3

    // 这种因式分解关键字的写法一般用于声明全局变量
    var (
        vname1111 int
        vname2222 string
    )
    fmt.Println(vname1, vname2, vname3, vname11, vname22, vname33, vname111, vname222, vname333, vname1111, vname2222)


// 空白标识符 _ 也被用于抛弃值，如值 5 在：_, b = 5, 7 中被抛弃。

    // _ 实际上是一个只写变量，你不能得到它的值。这样做是因为 Go 语言中你必须使用所有被声明的变量，但有时你并不需要使用从一个函数得到的所有返回值。
    _, n := 5, 7
    fmt.Println(n)  // _ 不能被使用
}

/*
我们知道可以在变量的初始化时省略变量的类型而由系统自动推断，声明语句写上 var 关键字其实是显得有些多余了，因此我们可以将它们简写为 a := 50 或 b := false。

a 和 b 的类型（int 和 bool）将由编译器自动推断。

这是使用变量的首选形式，但是它只能被用在函数体内，而不可以用于全局变量的声明与赋值。使用操作符 := 可以高效地创建一个新的变量，称之为初始化声明。
*/
```
