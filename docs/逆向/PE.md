
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
    分别打开\.exe, .dll, .sys等文件，观察特征前2个字节

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

可以在这里插入一些危险的代码。

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
