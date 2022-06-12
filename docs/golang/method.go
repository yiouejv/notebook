
package main

import "fmt"

type Circle struct {
    radius float64
}

// 所有给定类型的方法属于该类型的方法集。语法格式如下：
// func (variable_name variable_data_type) function_name() [return_type]{
       /* 函数体*/
// }
func (c Circle) getArea() float64 {
    return 3.14 * c.radius * c.radius
}


func main() {
    var c1 Circle
    c1.radius = 1
    fmt.Println(c1.getArea())
}
