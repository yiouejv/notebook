
## ip地址转换函数


```c++ title="inet_addr"
// inet_addr 将点分十进制转换成网络字节序表示的ipv4地址, 失败时返回 INADDR_NONE
#include<iostream>
#include<arpa/inet.h>
using namespace std;


int main(int argc, const char *argv[]) {
    in_addr_t ret = inet_addr("192.168.0.1");
    if (ret == INADDR_NONE) {
        cout << "inet_addr failed" << endl;
    } else {
        cout << ret << endl;
    }
    return 0;
}
```
