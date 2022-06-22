
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

每个进程都有一张属于自己的句柄表，句柄表示为 __HANDLE__

操作内核有一个全局句柄表，句柄表示为 __HWND__

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

## 线程互斥

### 临界资源, 临界区

- 临界资源：系统需要，必须互斥访问的资源.
- 临界区: 访问临界资源的一段代码.

### 临界区实现线程锁

```c++ title="创建全局变量"
CRITICAL_SECTION cs;
```

```c++ title="初始化全局变量"
InitializeCriticalSection(&cs);
```

```c++ title="实现临界区"
EnterCriticalSection(&cs);
// 使用临界资源
LeaveCriticalSection(&cs);
```

```c++ title="临界区使用示例"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

CRITICAL_SECTION cs;
int g_count = 10;

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    EnterCriticalSection(&cs);
    while (g_count > 0) {
        printf("还有%d张票\n", g_count);
        --g_count;
        printf("卖出1张还有 %d 张\n", g_count);
    }
    LeaveCriticalSection(&cs);
    return 0;
}

int main(int argc, const char *argv) {
    int n = 10;
    const int arrSize = 2;
    DWORD r1 = -1, r2 = -1;
    HANDLE arrHandle[arrSize]{};
    InitializeCriticalSection(&cs);

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
        ThreadProc,
        &n,
        0,
        NULL
    );
    WaitForMultipleObjects(2, arrHandle, TRUE, INFINITE);
    GetExitCodeThread(arrHandle[0], &r1);
    GetExitCodeThread(arrHandle[1], &r2);
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    return 0;
};
```

该示例展示了全局变量的临界资源实现的线程锁。

内核级的临界资源怎么办？

### 互斥体

互斥体，和临界资源很像，但是互斥体属于内核级别的临界资源

可以作用于不同进程之间的线程互斥。

```c++ title="process A"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv) {
    // 创建一个互斥体
    HANDLE mutex = CreateMutex(NULL, TRUE, TEXT("XYZ"));

    // 等待获取互斥体
    WaitForSingleObject(mutex, INFINITE);

    for (int i = 0; i < 10; ++i) {
        cout << "Process A: " << i << endl;
        Sleep(1000);
    }

    ReleaseMutex(mutex);
    return 0;
};
```

```c++ title="process B"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv) {
    // 创建一个互斥体
    HANDLE mutex = CreateMutex(NULL, TRUE, TEXT("XYZ"));

    // 等待获取互斥体
    WaitForSingleObject(mutex, INFINITE);

    for (int i = 0; i < 10; ++i) {
        cout << "Process B: " << i << endl;
        Sleep(1000);
    }

    ReleaseMutex(mutex);
    return 0;
};
```

运行两个程序，你会发现只有当一个进程执行结束，释放了互斥体之后，另一个进程才会运行到for循环。

#### CreateMutex

```c++
HANDLE CreateMutex( 
  LPSECURITY_ATTRIBUTES lpMutexAttributes, 
  BOOL bInitialOwner, 
  LPCTSTR lpName 
);
```

- 第二个参数：

如果此值为 TRUE 并且调用者创建了互斥锁，则调用线程将获得互斥锁对象的所有权。

否则，调用线程不会获得互斥锁的所有权。要确定调用者是否创建了互斥锁，

- 函数返回值:

如果函数执行成功，则返回互斥对象的句柄，如果在函数调用之前命名的互斥对象存在，则函数返回现有对象的句柄, GetLastError 返回 ERROR\_ALREADY\_EXISTS。

创建互斥体失败, NULL 表示失败。要获取扩展错误信息，请调用 GetLastError

#### 利用互斥体防止多开

```c++ title="防止多开"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv) {
    // 创建一个互斥体
    HANDLE mutex = CreateMutex(NULL, TRUE, TEXT("XYZ"));
    if (mutex != NULL) {
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            // 说明是第二次打开程序
            CloseHandle(mutex);
            return 0;
        }
    } else {
        // 创建互斥体失败
        int err = GetLastError();
        cout << "createMutex failed, errorno: " << err << endl;
        CloseHandle(mutex);
        return 0;
    }

    // 等待获取互斥体
    WaitForSingleObject(mutex, INFINITE);

    for (int i = 0; i < 10; ++i) {
        cout << "Process A: " << i << endl;
        Sleep(1000);
    }

    ReleaseMutex(mutex);
    return 0;
};
```

#### 线程锁和互斥体的区别

1. 线程锁只能用于单个进程间的线程控制
2. 互斥体可以设置等待超时，线程锁不能, 线程意外终止时，mutex 可以避免无限等待
3. mutex 效率没有线程锁高

## 线程同步

### Event

```c++
HANDLE CreateEvent(
    LPSECURITY_ATTRIBUTES lpEventAttributes,  // 安全描述符
    BOOL bManualReset,
    BOOL bInitialState,                       // 初始状态
    LPCTSTR lpName,                           // object name
)
```

- bManualReset:
    - true: 需手动重置事件对象
    - false: 自动重置事件对象
- bInitialState:
    - true: 有信号
    - false: 无信号

切换信号需要使用SetEvent 函数

```c++ title="Event实现线程同步，生产者消费者模型"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int g_count = 0;
HANDLE g_setEvent;
HANDLE g_getEvent;

// 生产者线程
DWORD WINAPI ThreadProc1(LPVOID lpParameter) {
    for (int i = 0; i < 10; ++i) {
        WaitForSingleObject(g_setEvent, INFINITE);
        ++g_count;
        cout << "生产者生产了一个产品: " << g_count << endl;
        SetEvent(g_getEvent);
    }
    return 0;
}

// 消费者线程
DWORD WINAPI ThreadProc2(LPVOID lpParameter) {
    for (int i = 0; i < 10; ++i) {
        WaitForSingleObject(g_getEvent, INFINITE);
        --g_count;
        cout << "消费者消费了一个产品: " << g_count << endl;
        SetEvent(g_setEvent);

    }
    return 0;
}

int main(int argc, const char *argv) {
    g_setEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
    g_getEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE arrHandle[2]{};

    arrHandle[0] = CreateThread(
        NULL,
        0,
        ThreadProc1,
        NULL,
        0,
        NULL
    );
    arrHandle[1] = CreateThread(
        NULL,
        0,
        ThreadProc2,
        NULL,
        0,
        NULL
    );
    WaitForMultipleObjects(2, arrHandle, TRUE, INFINITE);
    CloseHandle(arrHandle[0]);
    CloseHandle(arrHandle[1]);
    CloseHandle(g_setEvent);
    CloseHandle(g_getEvent);
    return 0;
};
```

## windows 三个重要的模块

- kernel32.dll: 进程，线程，内存管理等. 
- user32.dll: 提供 gui 编程, 基于存在的图形界面编程
- gdi32.dll: 提供 gdi 编程，自定义图形界面

kernel32.dll 实际上只是提供了接口，真正的实现是由内核中的 ntoskrnl.exe 实现的

user32.dll, gdi32.dll 都是基于内核的 win32k.sys 实现的
