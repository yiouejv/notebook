
## 在win32 中使用字符串

```c
TCHAR str[] = TEXT("中国");
```

## 进程创建的过程

1. 映射exe文件
2. 创建内核对象EPROCESS
3. 映射系统DLL(ntdll.dll)
4. 创建线程内核对象ETHREAD
5. 系统启动线程
    映射DLL(ntdll.LdrlnitializeThunk)
    线程开始执行

## 内核对象

进程，线程，文件，互斥体，事件等在内核都有一个对应的结构体，这些结构体由内核负责管理。我们管这样的对象叫内核对象。

## 句柄表

为什么要有句柄表 ?

进程在运行过程中，可能会创建一些内核对象，操作系统不会把内核地址暴露给用户。

句柄的存在就是把内核层和用户层隔离开，让用户没法直接操作内核层。

每个进程都有一张属于自己的句柄表，操作内核有一个全局句柄表。

## 进程API

### CreateProcess

```c++
if( !CreateProcess(
    filepath,       // 对象名称, 打开哪个exe
    NULL,           // 命令行
    NULL,           // 不继承进程句柄
    NULL,           // 不继承线程句柄
    FALSE,          // 不继承句柄
    0,              // 创建标识（可以做一些挂起操作）
    NULL,           // 使用父进程环境变量
    NULL,           // 使用父进程目录作为当前目录，可以自己设置目录
    &si,            // STARTUPINFO结构体详细信息
    &pi )           // PROCESS_INFORMATION 结构体进程信息
)
{
    printf( "CreateProcess failed (%d).\n", GetLastError() );
    return;
}
```

### GetCurrentProcessId

获取进程pid

### GetCurrentProcess

获取进程句柄

### GetCommandLine

获取命令行

### GetStartupInfo

获取启动信息

### EnumProcess

遍历进程ID

### CreateToolhelp32Snapshot

快照

## 线程API

### CreateThread

### Sleep

### SuspendThread

### ResumeThread

```c++ title="线程创建，挂起，唤醒"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    int *p = static_cast<int *>(lpParameter);
    for (int i = 0; i < *p; ++i) {
        cout << "thread i: " << i << endl;
        Sleep(500);
    }
    return 0;
}

int main(int argc, const char *argv) {
    int n = 10;
    HANDLE handle = CreateThread(
        NULL,
        0,
        ThreadProc,
        &n,
        0,
        NULL
    );
    SuspendThread(handle);
    for (int i = 0; i < 100; ++i) {
        cout << "i: " << i << endl;
        Sleep(50);
    }
    Sleep(3000);
    ResumeThread(handle);
    CloseHandle(handle);
    getchar();
    return 0;
};
```

### 等待线程结束

- WaitForSingleObject: 等待单个线程结束
- WaitForMultipleObjects: 等待多个线程结束
- GetExitCodeThread: 获取线程函数的返回值

```c++ title="等待线程结束"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    int *p = static_cast<int *>(lpParameter);
    for (int i = 0; i < *p; ++i) {
        cout << "thread i: " << i << endl;
        Sleep(500);
    }
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter) {
    int *p = static_cast<int *>(lpParameter);
    for (int i = 0; i < *p; ++i) {
        cout << "thread i: " << i << endl;
        Sleep(500);
    }
    return 1;
}

int main(int argc, const char *argv) {
    int n = 10;
    HANDLE arrHandle[2];
    DWORD dw1 = 0;
    DWORD dw2 = 0;

    arrHandle[0] = CreateThread(
        NULL,
        0,
        ThreadProc,
        &n,
        0,
        NULL
    );
    arrHandle[1] = CreateThread(
        NULL,
        0,
        ThreadProc2,
        &n,
        0,
        NULL
    );
    WaitForSingleObject(arrHandle[0], INFINITE);
    cout << "线程返回结束, single" << endl;

    WaitForMultipleObjects(2, arrHandle, TRUE, INFINITE);
    cout << "线程返回结束, multi" << endl;

    GetExitCodeThread(arrHandle[0], &dw1);
    GetExitCodeThread(arrHandle[1], &dw2);
    cout << "dw1: " << dw1 << endl;
    cout << "dw2: " << dw2 << endl;
    getchar();
    CloseHandle(arrHandle[0]);
    CloseHandle(arrHandle[1]);
    return 0;
};
```
### 设置、获取线程上下文

- GetThreadContext
- SetThreadContext

```c++ title="获取线程上下文"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    int *p = static_cast<int *>(lpParameter);
    for (int i = 0; i < *p; ++i) {
        cout << "thread i: " << i << endl;
        Sleep(500);
    }
    return 0;
}

int main(int argc, const char *argv) {
    int n = 10;
    HANDLE handle;

    handle = CreateThread(
        NULL,
        0,
        ThreadProc,
        &n,
        0,
        NULL
    );
    CONTEXT context;
    context.ContextFlags = CONTEXT_INTEGER;
    GetThreadContext(handle, &context);
    printf("%x %x\n", context.Rax, context.Rcx);
    CloseHandle(handle);
    return 0;
};
```
