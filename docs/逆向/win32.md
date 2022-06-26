
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

### 获取进程句柄

```c++ title="获取进程句柄"
HWND gameHandle = FindWindow(CString("MainWindow"), CString("植物大战僵尸中文版"));
DWORD pid;
GetWindowThreadProcessId(gameHandle, &pid);
HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
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

## 虚拟内存地址划分

|分区 | x86 32 位windows|
|----- |-----------|
|空指针赋值区| 0x00000000 - 0x0000ffff |
| 用户模式去 | 0x00010000 - 0x7ffeffff |
| 64kb禁入区 | 0x7fff0000 - 0x7fffffff |
| 内核       | 0x80000000 - 0xffffffff |

## 内存的申请和释放

- private memory: 某一个进程独占的物理内存
- mapped memory: 多个进程共享的物理内存

### VirtualAlloc, VirtualAllocEx 申请private memory

```c++ title="VirtualAlloc"
LPVOID VirtualAlloc (
    LPVOID lpAddress,  // 要分配的内存区域的地址, 通常为NULL
    DWORD dwSize,      // 分配的大小, 通常为页的整数倍, 0x1000 一页 4kb
    DWORD flAllocationType,  // 分配的类型
    DWORD flProtect         // 该内存的初始保护属性
);
```

```c++ title="申请8k独占的内存"
#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, const char *argv) {
    // MEM_COMMIT: 分配真实的物理内存
    // MEM_RESERVE: 占用虚拟内存的空间，不分配真实的物理内存
    LPVOID p = VirtualAlloc(NULL, 0x1000 * 2, MEM_COMMIT, PAGE_READONLY);
    cout << p << endl;

    VirtualFree(p, 0, MEM_RELEASE);
    return 0;
};
```

### VirtualFree  释放内存

```c++
BOOL VirtualFree(
  LPVOID lpAddress,  // 指向要释放的页面区域的基地址的指针
  DWORD dwSize,      // 释放的大小，申请多大，释放多大
  DWORD dwFreeType
);

// dwFreeType
MEM_DECOMMIT: 取消申请的物理内存，虚拟内存还会占用
MEM_RELEASE: 释放虚拟内存的占用, dwSize 必需为0
```

### CreateFileMapping 申请 mapped memory

MapViewOffile 绑定物理页与线性地址(虚拟内存)的映射


## 文件系统

文件系统是操作系统用于管理磁盘上文件的方法和数据结构。

|   | NTFS | FAT32 |
----|------|-------|
|磁盘分区容量| 2T | 32G |
|单个文件容量| 4G以上 | 最大4G |
|EFS 加密 | 支持 | 不支持 |
|磁盘配额 | 支持 | 不支持 |

### 文件相关api

- CreateFile: 创建文件
- CloseHandle: 关闭文件的句柄
- GetFileSize: 获取文件的长度
- GetFileAttributes, GetFileAttributesEx: 获取文件的属性和信息
- ReadFile, WriteFile, CopyFile, DeleteFile: 操作文件
- FindFirstFile, FindNextFile: 查找文件

### 卷相关api

卷: 每一个磁盘分区

- GetLogicalDrives: 获取卷
- GetLogicalDrivesStrings: 获取一个卷的昵称
- GetDriveType: 获取卷的类型
- GetVolumeInformation: 获取卷的信息 

### 目录相关api

- CreateDirectory: 创建目录
- RemoveDirectory: 删除目录
- MoveFile: 修改目录名称
- GetCurrentDirectory: 获取程序当前目录
- SetCurrentDirectory: 设置程序当前目录

```c++
#include <iostream>
#include <windows.h>
#include <cstdio>
using namespace std;

int main(int argc, const char *argv) {
    // 1. 创建目录
    CreateDirectory(TEXT("E:\\testDir"), NULL);

    // 2. 移除目录
    /* RemoveDirectory(TEXT("E:\\testDir")); */

    // 3. 修改目录名称
    MoveFile(TEXT("E:\\testDir"), TEXT("E:\\testDir2"));

    // 4. 获取当前目录
    TCHAR szCurrentDir[MAX_PATH]{};
    GetCurrentDirectory(MAX_PATH, szCurrentDir);
    printf("currentDir: %ws \n", szCurrentDir);

    // 5. 设置程序当前目录
    SetCurrentDirectory(TEXT("C:\\"));
    CreateDirectory(TEXT("aaaa"), NULL);
    return 0;
};
```

## 链接库

### 动态链接库

动态链接库可以只在调用的时候加载，使用完即卸载，解决了静态链接库生成的可执行文件体积大的问题.

所有的链接库都只会加载一份，内核中存在一份其他进程再加载都不会重复加载。

下面演示一个动态链接库的例子：

#### dll 创建

```c++ title="dllmain.cpp"
#include "pch.h"
#include <stdio.h>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("DLL_PROCESS_ATTACH\n");
        break;

    case DLL_THREAD_ATTACH:
        printf("DLL_THREAD_ATTACH\n");
        break;

    case DLL_THREAD_DETACH:
        printf("DLL_THREAD_DETACH\n");
        break;

    case DLL_PROCESS_DETACH:
        printf("DLL_PROCESS_DETACH\n");
        break;
    }
    return TRUE;
}
```

- HMODULE hModule: 谁加载了这个模块
- `ul_reason_for_call`: 什么情况执行了DllMain函数


```c++ title="mydll.h"
#pragma once

extern "C" _declspec(dllexport) int add(int x, int y);
extern "C" _declspec(dllexport) int sub(int x, int y);
```

```c++ title="mydll.cpp"
#include "pch.h"
#include "mydll.h"

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}
```

#### 显式链接

```c++ title="动态链接库显示加载的方式使用dll"
#include <iostream>
#include <windows.h>
#include <cstdio>
using namespace std;


int main(int argc, const char *argv) {
    // 1. 加载dll
    HINSTANCE dll1 = LoadLibrary(TEXT("D:\\workspace\\library\\Dll1.dll"));
    if (dll1 == NULL) {
        printf("loadlibrary failed, errorcode: %d\n", GetLastError());
        return 0;
    }
    // 2. 定义函数指针
    typedef int(*pAdd)(int, int);
    typedef int(*pSub)(int, int);

    // 3. 获取函数地址
    pAdd add = (pAdd)GetProcAddress(dll1, "add");
    pSub sub = (pSub)GetProcAddress(dll1, "sub");

    // 4. 调用函数
    printf("a + b = %d\n", add(1, 2));
    printf("a - b = %d\n", sub(1, 2));

    // 5. 释放动态链接库
    FreeLibrary(dll1);
    return 0;
};
```

#### 隐式链接

1. 将 dll, lib 文件放到工程目录下

dll 中包含一个导出表, 记录了当前模块提供了哪些函数

```c++
#pragma comment(lib, "Dll1.lib")
extern "C" __declspec(dllimport) int add(int x, int y);
extern "C" __declspec(dllimport) int sub(int x, int y);
```

这几行的功能，编译器会把当前的dll信息写入到当前exe的导入表里, 导入表里详细的记录了当前的exe需要哪些dll, 用到了dll中的具体哪些函数。


```c++ title="隐式链接的方式"
#include <iostream>
#include <windows.h>
#include <cstdio>
using namespace std;


#pragma comment(lib, "Dll1.lib")
extern "C" __declspec(dllimport) int add(int x, int y);
extern "C" __declspec(dllimport) int sub(int x, int y);

int main(int argc, const char *argv) {
    printf("a + b = %d\n", add(1, 2));
    printf("a - b = %d\n", sub(1, 2));
    return 0;
};
```

## 创建远程线程

CreateRemoteThread

### 注入

在第三方进程不知道或者不允许的情况下将模块或者代码写入对方进程空间，并设法执行的技术。

已知的注入方式:

- 远程线程注入
- APC注入
- 消息钩子注入
- 注册表注入
- 导入表注入
- 输入法注入

等等。

### 远程注入示例

```c++ title="win32_two.exe 被注入的程序"
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv) {
    while (true) {
        printf("test app ...\n");
        Sleep(1000);
    }
    return 0;
};
```

```c++ title="要注入的dll"
#include "pch.h"
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    for (int i = 0; i < 100; ++i) {
        printf("thread i: %d \n", i);
        Sleep(500);
    }
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(
            NULL,
            0,
            ThreadProc,
            NULL,
            0,
            NULL
        );
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
```

```c++ title="执行注入操作的程序"
#include <iostream>
#include <windows.h>
#include <cstdio>
using namespace std;


BOOL LoadRemoteDll(HANDLE hProcess, const char *dllPath) {
    if (hProcess == NULL) {
        printf("hProcess Error ! \n");
        return FALSE;
    }
    // 2. 计算dll路径长度
    DWORD dllLen = strlen(dllPath) + 1;

    // 3. 在目标进程分配内存
    LPVOID lpAddr = VirtualAllocEx(hProcess, NULL, dllLen, MEM_COMMIT, PAGE_READWRITE);
    if (lpAddr == NULL) {
        printf("VirtualAllocEx Error! \n");
        printf("errcode: %d \n", GetLastError());
        CloseHandle(hProcess);
        return FALSE;
    }

    // 4. 拷贝DLL路径名字目录到进程内存
    BOOL ret = WriteProcessMemory(hProcess, lpAddr, dllPath, dllLen, NULL);
    if (!ret) {
        printf("WriteProcessMemory Error! \n");
        printf("errcode: %d \n", GetLastError());
        CloseHandle(hProcess);
        return FALSE;
    }

    // 5. 获取模块地址
    HMODULE hModule = GetModuleHandle(TEXT("Kernel32.dll"));
    if (!hModule) {
        printf("GetModuleHandle Error! \n");
        printf("errcode: %d \n", GetLastError());
        CloseHandle(hProcess);
        return FALSE;
    }

    // 6. 获取LoadLibraryA 函数地址
    /* DWORD loadAddr = (DWORD)GetProcAddress(hModule, "LoadLibraryA"); */
    // 64 位
    unsigned long long loadAddr = (unsigned long long)GetProcAddress(hModule, "LoadLibraryA");
    if (!loadAddr) {
        printf("GetModuleHandle Error! \n");
        printf("errcode: %d \n", GetLastError());
        CloseHandle(hProcess);
        CloseHandle(hModule);
        return FALSE;
    }

    // 7. 创建远程线程，加载dll
    HANDLE thread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAddr, lpAddr, 0, NULL);
    if (!thread) {
        printf("CreateRemoteThread Error! \n");
        printf("errcode: %d \n", GetLastError());
        CloseHandle(hProcess);
        CloseHandle(hModule);
        return FALSE;
    }

    // 8. 关闭句柄
    CloseHandle(hProcess);
    return TRUE;
};


int main(int argc, const char *argv) {
    // 1. 获取进程句柄
    LPCTSTR className = TEXT("ConsoleWindowClass");
    /* LPCTSTR windowName = TEXT("D:\\workspace\\vs2022\\win32_two\\Debug\\win32_two.exe"); */
    LPCTSTR windowName = TEXT("D:\\workspace\\vs2022\\win32_two\\x64\\Debug\\win32_two.exe");
    HWND gameHandle = FindWindow(className, windowName);
    printf("gameHandle: %d \n", gameHandle);

    DWORD pid;
    GetWindowThreadProcessId(gameHandle, &pid);
    printf("pid: %d \n", pid);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    printf("hProcess: %d \n", hProcess);

    LoadRemoteDll(hProcess, "D:\\workspace\\library\\Dll1.dll");
    return 0;
};
```

上述代码执行的理论依据:

把CreateRemoteThread的入口点函数设为LoadLibraryA(W),线程的那个参数设为DLL路径指针(在目标进程中,所以得把DLL路径拷到目标进程中, 用VirtualAllocEx在目标进程中分配内存空间, 然后WriteProcessMemory).

可能出现的错误:

1. CreateRemoteThread errorcode 5: 32位，64位没有对应上.
2. 64 位注入后，被注入程序崩溃了：因为32位的LoadLibraryA地址是DWORD，但64位却是ULONGLONG，所以仅仅改变编译方式还不够, 必须用一个足够容纳8个字节地址的类型来保存。


为什么在我这个进程中得到的LoadLibrary在远程进程中也可以用?

系统DLL在各个进程中的映射地址都是一样的。


64位进程,就得用64位的EXE来CreateRemoteThread, 另外DLL也应该是64位

32位进程,就得用32位的EXE来CreateRemoteThread, 另外DLL也应该是32位
