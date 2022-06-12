```golang
// 你必须在源文件中非注释的第一行指明这个文件属于哪个包
package main

// 告诉 Go 编译器这个程序需要使用 fmt 包
import "fmt"

// 程序开始执行的函数。main 函数是每一个可执行程序所必须包含的
func main() {  // 需要注意的是 { 不能单独放在一行
    // 可以将字符串输出到控制台，并在最后自动增加换行字符 \n
    // 使用 fmt.Print("hello, world\n") 可以得到相同的结果。
    fmt.Println("hello world!")
    fmt.Print("hello world!\n")
}

// go run hello.go

// 生成二进制文件
// go build hello.go

// 当标识符（包括常量、变量、类型、函数名、结构字段等等）以一个大写字母开头，如：Group1，那么使用这种形式的标识符的对象就可以被外部包的代码所使用（客户端程序需要先导入这个包），这被称为导出（像面向对象语言中的 public）；标识符如果以小写字母开头，则对包外是不可见的，但是他们在整个包的内部是可见并且可用的（像面向对象语言中的 protected ）。
```
