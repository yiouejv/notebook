
package main

import "fmt"

/*
    func function_name( [parameter list] ) [return_types] {
           函数体
       }
*/
func max(a, b int) int {
    ret := a
    if b > a {
        ret = b
    }
    return ret
}

func swap(s1, s2 string) (string, string) {
    return s2, s1
}

func wapper() func(a, b int) int {
    return max
}

func main() {
    fmt.Println(max(1, 2))

    a, b := swap("hello", "world")
    fmt.Println(a, b)

    fmt.Println(wapper()(1, 2))
}
