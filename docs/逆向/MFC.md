
Microsoft Foundation Classes

由微软提供的放置WIN API 的面向对象的包装的C++类库

1. 基于MFC的窗口程序必须只能有一个由CWinApp派生的对象
2. 我们必须覆盖CWinApp的虚函数 InitInstance 在里面创建窗口并把窗口对象保存在它的成员变量`m_pMainWnd`
3. 创建窗口是通过派生 CFrameWnd 对象，在它的构造函数里面调用成员函数create.



## 打印

```c++
#define log(fmt, ...) \
CString str;  \
str.Format(CString(fmt), __VA_ARGS__);  \
AfxMessageBox(str);
```

## 打开链接

```c++
ShellExecute(NULL, CString("open"), CString("https://github.com/yiouejv/notebook"), NULL, NULL, SW_SHOWNORMAL);
```

## check box

1. 是否选中

```c++
bool checked = IsDlgButtonChecked(id);
```


## WriteMemory

```c++
void WriteMemory(void *value, DWORD valueSize, ...)
{
	if (value == NULL || valueSize == 0 || g_processHandle == NULL) return;

	DWORD tempValue = 0;

	va_list addresses;
	va_start(addresses, valueSize);
	DWORD offset = 0;
	DWORD lastAddress = 0;
	while ((offset = va_arg(addresses, DWORD)) != -1)
	{
		lastAddress = tempValue + offset;
		::ReadProcessMemory(g_processHandle, (LPCVOID)lastAddress, &tempValue, sizeof(DWORD), NULL);
	}
	va_end(addresses);

	::WriteProcessMemory(g_processHandle, (LPVOID)lastAddress, value, valueSize, NULL);
}

void WriteMemory(void *value, DWORD valueSize, DWORD address) {
	WriteMemory(value, valueSize, address, -1);
}
```

## 常量中有换行符

```
属性->配置属性->C++ ->命令行

加入一下属性

/source-charset:utf-8 

```


