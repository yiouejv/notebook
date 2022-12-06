
## 什么是可执行文件

可执行文件(executable file) 指的是可以有操作系统进行加载执行的文件。

### 可执行文件的格式

- window 平台: PE（portable Executable) 文件结构
- linux 平台: ELF（Executable and Linking Format) 文件结构

## 那些领域会用到PE文件结构

- 病毒与反病毒
- 外挂与反外挂
- 加壳与脱壳
- 无源码修改功能，软件汉化等


## 如何识别PE文件

- PE文件的特征（PE指纹）

    分别打开\.exe, .dll, .sys等文件，观察特征前2个字节, 为MZ

- 不要仅仅通过文件的后缀名来认定PE文件

## pe结构

定义PE格式的主要是头文件`winnt.h`

<img src="../../images/pe.png">


<img src="../../images/pe结构.png">

### DOS MZ文件头

总共占64个字节

<strong>IMAGE\_DOCS\_HEADER</strong>

### DOS 块

不确定大小，DOS MZ头与PE头之间的部分即为 DOS块。可随意修改，不影响。

<span style="color:red">可以在这里插入一些危险的代码。</span>

### PE 头

```c++
typedef struct _IMAGE_NT_HEADERS {
    DWORD Signature;  // 4个字节
    // 标准PE头
    IMAGE_FILE_HEADER FileHeader;

    // 拓展PE头
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;
```

#### 标准PE头

`IMAGE_FILE_HEADER` 总共占20个字节

#### 扩展PE头

`IMAGE_OPTION_HEADER32` 32位的扩展pe头占 224 个字节, 转化为十六进制为E0h, 64位的占用为F0h, 大小可以修改

标准PE头里有个字段`WORD SizeOfOptionalHeader` 记录了扩展PE头的大小

字段`DWORD FileAlignment` 表示文件对齐的大小, `DWORD SizeOfImage` 记录了所有头+节标按照文件对齐后的大小，其实就是第一个节之前所有元素的大小，按照文件对齐之后的大小。

<span style="color:red">可以在节表之后，第一个节开始之前的空位置加别的代码。</span>


### 节表

`IMAGE_SECTION_HEADER` 节表内每个部分占40个字节

节表后面跟着一些编译器插入的数据

每个节的大小都必须是扩展PE头中，FileAlignment 文件对齐的整数倍。

## PE文件在磁盘和内存中的两种状态

<img src="../../images/pe_status.png">



-------------------------

## 每个部分具体的作用

### DOS文件头属性说明

<img src="../../images/dosHeader.png">

这个结构体是给16位系统用的，除了第一个字段，和最后一个字段，操作系统用来判断是否PE头在哪里。

所谓的PE指纹: Dos头两个字节是否为"MZ", 最后一个字段，最后四个字节的地址找到的标识是否为PE。

### 标准PE头

```c++
typedef struct _IMAGE_FILE_HEADER {
    // 可以运行在什么样的CPU上，任意: 0, intel 386及后续: 14C, x64: 8664
    WORD Machine;
    // 文件中存在的节的总数，如果要新增节或者合并节，就要修改这个值
    WORD NumberOfSections;
    // 编译器填写的时间戳，与文件属性里面的创建时间，修改时间无关
    DWORD TimeDateStamp;

    // 调试相关
    DWORD PointerToSymbolTable;
    DWORD NumberOfSymbols;

    // 可选PE头的大小（32位PE文件大小为0xE0, 64位PE文件 0xF0)
    WORD SizeOfOptionalHeader;//这个成员用来标识扩展PE头的大小，在这里改变扩展PE头的大小。

    // 文件属性
    WORD Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
```

文件属性占两个字节，16位，每一位具体的含义如下表

<img src="../../images/peFileAttr.png">

### 扩展PE头

<img src="../../images/peOption32.png">

程序的入口: ImageBase + AddressOfEntryPoint

### 节表

<img src="../../images/peTab.png">

- PointerToRawData: 当前节在文件中从哪里展开
- VirtualAddress: 当前节在内存中从哪里展开

节属性说明

<img src="../../images/peAttr.png">

## 全局变量

全局变量有初始值，会在PE中有一个位置存储

没有初始值，只有在PE文件被加载到内存中才会有位置

## RVA 到 FOA的转换

相对虚拟地址RVA

文件偏移地址FOA

1. 得到RVA的值: 内存地址 - ImageBase
2. 判断RVA是否位于PE头中，如果是 FOA == RVA
3. 判断RVA位于哪个节:

    RVA >= 节.VirtualAddress

    RVA <= 节.VirtualAddress + 当前节内存对齐后的大小

    差值 = RVA - 节.VitualAddress

    FOA = 节.PointerToRawData + 差值

## 空白区添加代码

1. 构造要写入的代码

    E8后的地址 = 要跳转的地址 - E8当前的地址 - 5

    E8当前的地址要注意加上 ImageBase

2. 在PE的空白区域构造一段代码
3. 修改入口地址位新增代码，入口地址在扩展PE头里
4. 新增代码执行后，跳回入口地址


## 新增节的步骤

1. 判断是否有足够的空间，可以添加一个节表
2. 在节表中新增一个成员
3. 修改PE头中节的数量
4. 修改sizeOfImage的大小
5. 在原有数据的最后，新增一个节的数据（内存对齐的整数倍）
6. 修正新增节表的属性

## 导出表

在扩展PE头结构体里最后一个字段，是一个结构体数组，数组长度为16，每个结构体大小为8个字节

结构体定义如下:

```c++
struct IMAGE_DATA_DIRECTORY {
    // 该成员的内存地址在哪，注意，这里的地址为RVA地址，如果文件对齐和内存对齐不一致则需要转换为FOA
    DOWRD VirtualAddress;
    // 指向内存地址的大小，这里的大小无实际意义，可以随便改
    DOWRD Size;
};
```

导出表的结构体如下，导出表占40个字节，上述的Size不一定为40个字节，原因是导出表里的结构体成员为指针。

<img src="../../images/peExport.png">

### 函数查找的过程

<img src="../../images/peFindFunc.png">

```c++
FARPROC GetProcAddress (
    HMODULE hMoudle;  // dll模块句柄, 实际上就是导出表的起始地址
    LPCSTR lpProcName;  // 函数名
);
```

GetProcAddress 拿着函数名去函数名称表遍历得到下标，用得到的下标去函数序号表里取函数的序号, 再拿序号做为下标去函数地址表里取函数的地址.

## 导入表

一个pe文件可能依赖多个dll, 可能存在多个导入表, 一个导入表占20个字节

<img src="../../images/peImportTable.png">

判断导入表结束: 连续20个字节都为00

### 确定导入的函数

<img src="../../images/peImportFunc.png">

<img src="../../images/peImportFunc2.png">


## ShellCode

不依赖环境，放到任务地方都可以执行的机器码

ShellCode 的编写原则

- 不能有全局变量
- 不能使用常量字符串
- 不能使用系统调用
- 不能嵌套调用其他函数
