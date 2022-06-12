
package main
import "fmt"

func f(arr [3]int) {
    fmt.Println("f", arr)
}

func main() {
// 一维数组
    var arr1[10] int
    fmt.Println(arr1)

    arr2 := [10]int {1, 2, 3}
    fmt.Println(arr2)

    // 如果数组长度不确定，可以使用 ... 代替数组的长度，
    // 编译器会根据元素个数自行推断数组的长度
    arr3 := [...]int {4, 5, 6}
    fmt.Println(arr3)

// 多维数组
    var arrr1[10] [2]int
    for i := 0; i < 2; i++ {
        arrr1[i] = [2]int{1, 2}
    }
    fmt.Println(arrr1)

    var arrr2 [1][2][3]int
    fmt.Println(arrr2)

    var arrr3 [2][2]int = {
        { 1, 2 },
        { 2, 3 },
    }
    fmt.Println(arrr3)

// 往函数里传数组
    f(arr3)
}
