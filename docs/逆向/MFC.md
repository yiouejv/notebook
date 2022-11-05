
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


## 选项卡控件

```
1.新建一个对话框工程。命名为：TabControlTest，选择“基于对话框”，点击完成。
2. 在对话框上添加Tab控件，然后，在控件上右键添加变量，变量名为m_tab。
3. 在对话框的初始化函数OnInitDialog里面添加如下代码:
m_tab.InsertItem(0, _T("类视图"));
m_tab.InsertItem(1, _T("属性管理器"));
4. 然后，在对话框资源里面再增加两个对话框，作为选项卡的子对话框，需要对这两个对话框的属性进行设置：Border选为None，Style选为Child。并将其ID改为：IDD_FIRSTTAB和IDD_SECONDTAB。
5.添加基于CDialogEx类CFirstTab,  CSecondTab；在firsttab对话框上右键，选择添加类。命名为CFirstTab;同理创建CSecondTab；

6. 再在TabControlTest1Dlg.h中添加变量
#include "FirstTab.h"

#include "SecondTab.h"

public：
CFirstTab  m_FirstTab;

CSecondTab  m_SecondTab;

7.再在初始化函数OnInitDialog里面添加如下代码:

///start///

m_FirstTab.Create(IDD_FIRSTTAB, &m_tab);

m_SecondTab.Create(IDD_SECONDTAB, &m_tab);

//获取m_tab控件的大小。
CRect rec;

 

m_tab.GetClientRect(&rec);

 

//将m_tab控件的大小适当改小。逻辑坐标默认向下为正，向右为正

rec.top+=25;  //去掉选项卡标签页那一块空间

rec.bottom-=4;
rec.left+=4;  
rec.right-=4;
//改变选项卡窗口的位置和大小
m_FirstTab.MoveWindow(&rec);
m_SecondTab.MoveWindow(&rec);

m_FirstTab.ShowWindow(TRUE);
m_SecondTab.ShowWindow(FALSE);

m_tab.SetCurSel(0); //默认显示第一个选项卡

//end/

7. 双击主对话框上选项卡控件，在自动创建的`OnSelchangeTabtest(NMHDR* pNMHDR, LRESULT* pResult)` 函数体下添加代码如下:


int CurSel;
CurSel = m_tab.GetCurSel(); //获取点击操作的第几张表
switch(CurSel)
{
case 0: //点击第一张表
m_FirstTab.ShowWindow(TRUE);
m_SecondTab.ShowWindow(FALSE);
break;
case 1://点击第二章表
m_FirstTab.ShowWindow(FALSE);
m_SecondTab.ShowWindow(TRUE);
break;
default: ;
}

```


## MFC AfxMessageBox改变标题

fxMessageBox,AfxMessageBox却没改变标题这个属性，

老大叫我把所有的AfxMessageBox换成MessageBox，MessageBox确也可以实现，第二个参数就是设定标题属性，用MessageBox有二点不好：

第一，APP里是不能用MessageBox，所以只要在APP里用AfxMessageBox来实现的，这个办法也是行不通的
第二，因为工程大，故修改起来也是很繁杂的，让费时间不说，还有可能人为的修改错误。
在网上查了些资料，得知AfxMessageBox其实最终也是调用MessageBox.个人理由AfxMessageBox就是MessageBox简化，用起来方便。通过自定义来改变标题也是可以的。不过，我最终还是采用了最为简单的办法，节省时间，又最为简单：
其实这个标题，也就是我们的默认的工程名，我们应该怎么在不改变工程名的基础上改变标题呢？其实这个标题在资源String  Table里就能找到，查找AFX_IDS_APP_TITLE，在这里你就能轻而易举的改变标题了．


注意：有的工程的资源String Table里面没有添加AFX_IDS_APP_TITLE，需要手动添加。

https://blog.csdn.net/dongpanshan/article/details/10142853
