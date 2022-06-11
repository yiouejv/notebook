
## 打印

```c++
#defind log(fmt, ...) \
CString str; \
str.Format(CString(fmt), __va_args__); \
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