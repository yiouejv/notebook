
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

<img src="../../images/pe结构.png">
