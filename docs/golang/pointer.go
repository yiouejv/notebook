
package main

import "fmt"
import "reflect"

func max(a, b int) int {
    ret := a
    if b > a {
        ret = b
    }
    return ret
}

func main() {
    a := 10
    fmt.Println("&a", &a)

    var p *int
    p = &a
    fmt.Println(p)

    fmt.Println(max(1, 2))
    var fp func(int, int) int
    fp = max
    fmt.Println(fp(1, 2))
    fmt.Println(reflect.TypeOf(fp))

}
