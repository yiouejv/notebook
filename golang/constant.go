
package main

import "fmt"
import "unsafe"

func main() {

// 常量中的数据类型只可以是布尔型、数字型（整数型、浮点型和复数）和字符串型。
    // 显式类型定义：
    const b string = "abc"
    // 隐式类型定义：
    const c = "abc"
    fmt.Println(b, c)


// 常量还可以用作枚举
    const (
        Unknown = 0
        Female = 1
        Male = 2
    )


// 常量可以用len(), cap(), unsafe.Sizeof()函数计算表达式的值。
// 常量表达式中，函数必须是内置函数，否则编译不过：
    const (
        aa = "abc"
        bb = len(aa)
        cc = unsafe.Sizeof(aa)
    )


// iota，特殊常量，可以认为是一个可以被编译器修改的常量。
// iota 在 const关键字出现时将被重置为 0(const 内部的第一行之前)，const 中每新增一行常量声明将使 iota 计数一次(iota 可理解为 const 语句块中的行索引)
    const (
        m = iota
        n = iota
        k = iota
    )
    fmt.Println(m, n, k)

    // 可以简写成
    const (
        mm = iota
        nn
        kk
    )
    fmt.Println(mm, nn, kk)

    const (
        i = 1 << iota
        j
        z
    )
    fmt.Println(i, j, z)


}
