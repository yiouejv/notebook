
<h2>打印</h2>

```c++
#defind log(fmt, ...) \
CString str; \
str.Format(CString(fmt), __va_args__); \
AfxMessageBox(str);
```

<h2>打开链接</h2>

```c++
ShellExecute(NULL, CString("open"), CString("https://github.com/yiouejv/notebook"), NULL, NULL, SW_SHOWNORMAL);
```

<h2>check box</h2>

1. 是否选中

```c++
bool checked = IsDlgButtonChecked(id);
```
