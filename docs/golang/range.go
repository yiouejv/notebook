
package main

import "fmt"

func main() {
    nums := [...]int {0, 1, 2, 3}
    for i, n := range nums {
        fmt.Println(i, n)
    }

    // range也可以用来枚举Unicode字符串
    for i, c := range "golang" {
        fmt.Println(i, c)
    }
}
