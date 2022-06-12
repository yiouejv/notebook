
package main
import (
    "fmt"
    "time"
)

func say(s string) {
    for i := 0; i < 5; i++ {
        time.Sleep(100 * time.Millisecond)
        fmt.Println(s)
    }
}

func sum(arr []int, c chan int) {
    sum := 0
    for _, v := range arr {
        sum += v
    }
    // 把结果传入通道
    c <- sum
}

func main() {
    go say("world")
    say("hello")

    arr := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
    // 创建通道
    c := make(chan int)
    go sum(arr[:len(arr) / 2], c)
    go sum(arr[len(arr) / 2:], c)
    // 从通道取出数据
    x, y := <-c, <-c
    fmt.Println(x, y, x+y)
}


/*
通道缓冲区
通道可以设置缓冲区，通过 make 的第二个参数指定缓冲区大小：

ch := make(chan int, 100)
带缓冲区的通道允许发送端的数据发送和接收端的数据获取处于异步状态，就是说发送端发送的数据可以放在缓冲区里面，可以等待接收端去获取数据，而不是立刻需要接收端去获取数据。

不过由于缓冲区的大小是有限的，所以还是必须有接收端来接收数据的，否则缓冲区一满，数据发送端就无法再发送数据了。

注意：如果通道不带缓冲，发送方会阻塞直到接收方从通道中接收了值。如果通道带缓冲，发送方则会阻塞直到发送的值被拷贝到缓冲区内；如果缓冲区已满，则意味着需要等待直到某个接收方获取到一个值。接收方在有值可以接收之前会一直阻塞。
*/
