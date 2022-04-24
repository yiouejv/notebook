
package main

import "fmt"

func main() {
    for i := 0; i < 10; i++ {
        fmt.Println(i)
    }

    var arr = []string{"h", "e", "l"}
    for i, arr := range arr {
        fmt.Println(i, arr)
    }

    // 死循环
    for {
        fmt.Println(0)
    }
}
