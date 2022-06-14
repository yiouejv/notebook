

import os
#### os.path.abspath(path)

python.org/zh-cn/3/library/os.path.html#os.path.abspath" title="永久链接至目标"####
Return a normalized absolutized version of the pathname path. 

返回路径名对应的绝对路径



#### os.path.basename(path)  

取到文件名



#### os.path.commonpath(paths)

返回序列路径中每个路径名的最长公共子路径。如果路径同时包含绝对路径名和相对路径名，或者路径为空，则引发ValueError。与commonPrefix（）不同，它返回有效路径。



#### os.path.commonprefix(list)

返回最长路径前缀（以字符为单位），它是列表中所有路径的前缀。如果列表为空，则返回空字符串（“”）。


#### os.path.dirname(path)  

返回路径名路径的目录名。



#### os.path.exists(path)  

如果路径引用现有路径或打开的文件描述符，则返回true。



#### os.path.lexists(path)

如果路径引用现有路径，则返回true。对于断开的符号链接返回true。



#### os.path.expanduser(path)

在UNIX和Windows上，返回参数，其初始组件为~或~ user，替换为该用户的主目录。
在Unix上，如果设置了环境变量home，则用它替换初始~；否则，将通过内置模块pwd在密码目录中查找当前用户的home目录。直接在密码目录中查找初始~user。
在Windows上，如果设置了主配置文件和用户配置文件，则将使用homepath和homedrive的组合。通过从上面派生的已创建用户路径中剥离最后一个目录组件来处理初始~user。
        


#### os.path.expandvars(path)

返回扩展了环境变量的参数。$name或$name形式的子字符串将替换为环境变量name的值。格式错误的变量名和对不存在变量的引用保持不变。
在Windows上，除了$name和$name之外，还支持%name%扩展。

示例
print(os.path.expandvars('$path'))


#### os.path.getatime(path)

返回上次访问某个路径的时间。返回值是一个浮点数，给出了自epoch以来的秒数（请参见时间模块）。如果文件不存在或不可访问，则引发OSError。


#### os.path.getmtime(path)

Return the time of last modification of path. The return value is a floating point number giving the number of seconds since the epoch (see the time module). Raise OSError if the file does not exist or is inaccessible.

返回上次修改路径的时间。返回值是一个浮点数，给出了自epoch以来的秒数（请参见时间模块）。如果文件不存在或不可访问，则引发OSError。




#### os.path.getctime(path)

Return the system's ctime which, on some systems (like Unix) is the time of the last metadata change, and, on others (like Windows), is the creation time for path. The return value is a number giving the number of seconds since the epoch (see the time module). Raise OSError if the file does not exist or is inaccessible.

返回系统的ctime，在某些系统（如unix）上，它是最后一次元数据更改的时间，而在其他系统（如windows）上，它是路径的创建时间。返回值是一个数字，给出了从epoch开始的秒数（请参见时间模块）。如果文件不存在或不可访问，则引发OSError。


#### os.path.getsize(path)

Return the size, in bytes, of path. Raise OSError if the file does not exist or is inaccessible.

返回路径的大小（以字节为单位）。如果文件不存在或不可访问，则引发OSError。



#### os.path.isabs(path)

Return True if path is an absolute pathname. On Unix, that means it begins with a slash, on Windows that it begins with a (back)slash after chopping off a potential drive letter.

如果路径是绝对路径名，则返回true。在UNIX上，这意味着它以斜线开头，在Windows上，它在切掉一个可能的驱动器号后以（反）斜线开头。


#### os.path.isfile(path)

Return True if path is an existing regular file. This follows symbolic links, so both islink() and isfile()can be true for the same path.

如果路径是现有的常规文件，则返回true。这遵循符号链接，因此islink（）和isfile（）对于同一路径都可以为真。


#### os.path.isdir(path)

Return True if path is an existing directory. This follows symbolic links, so both islink() and isdir() can be true for the same path.  
如果路径是现有目录，则返回true。这遵循符号链接，因此islink（）和isdir（）对于同一路径都可以为真。


#### os.path.islink(path)

Return True if path refers to an existing directory entry that is a symbolic link. Always False if symbolic links are not supported by the Python runtime.

如果路径引用的是符号链接的现有目录项，则返回true。如果Python运行时不支持符号链接，则始终为false。


#### os.path.ismount(path)

Return True if pathname path is a mount point: a point in a file system where a different file system has been mounted. On POSIX, the function checks whether path's parent, path/.., is on a different device than path, or whether path/.. and path point to the same i-node on the same device --- this should detect mount points for all Unix and POSIX variants. It is not able to reliably detect bind mounts on the same filesystem. On Windows, a drive letter root and a share UNC are always mount points, and for any other path GetVolumePathName is called to see if it is different from the input path.

如果路径名路径是装入点，则返回true：文件系统中已装入其他文件系统的点。在posix上，函数检查path的父级path/，与path是否在不同的设备上，或者path/。路径指向同一设备上的同一个i节点——这应该可以检测到所有unix和posix变体的挂载点。它不能可靠地检测同一文件系统上的绑定装载。在Windows上，驱动器号根目录和共享UNC始终是装入点，对于任何其他路径，调用getvolumepathname查看它是否与输入路径不同。


#### os.path.join(path, *paths)

Join one or more path components intelligently. The return value is the concatenation of path and any members of *paths with exactly one directory separator (os.sep) following each non-empty part except the last, meaning that the result will only end in a separator if the last part is empty. If a component is an absolute path, all previous components are thrown away and joining continues from the absolute path component.

On Windows, the drive letter is not reset when an absolute path component (e.g., r'\foo') is encountered. If a component contains a drive letter, all previous components are thrown away and the drive letter is reset. Note that since there is a current directory for each drive, os.path.join("c:", "foo") represents a path relative to the current directory on drive C: (c:foo), not c:\foo.

智能地连接一个或多个路径组件。返回值是路径和*路径的任何成员的串联，每个非空部分后面只有一个目录分隔符（os.sep），最后一个除外，这意味着如果最后一个部分为空，结果将仅以分隔符结尾。如果某个组件是绝对路径，则会丢弃所有以前的组件，并从绝对路径组件继续连接。
在Windows上，遇到绝对路径组件（例如R'\foo'）时，不会重置驱动器号。如果某个组件包含驱动器号，则会丢弃所有以前的组件并重置驱动器号。注意，由于每个驱动器都有一个当前目录，os.path.join（“c：”，“foo”）表示相对于驱动器c:（c:foo）上当前目录的路径，而不是c:\foo。



#### os.path.normcase(path)

Normalize the case of a pathname. On Windows, convert all characters in the pathname to lowercase, and also convert forward slashes to backward slashes. On other operating systems, return the path unchanged. Raise a TypeError if the type of path is not str or bytes (directly or indirectly through the os.PathLikeinterface).

规范化路径名的大小写。在Windows上，将路径名中的所有字符转换为小写，并将正斜杠转换为反斜杠。在其他操作系统上，返回路径不变。如果路径类型不是str或bytes（直接或间接通过os.pathlikeinterface），则引发类型错误。


#### os.path.normpath(path)

Normalize a pathname by collapsing redundant separators and up-level references so that A//B, A/B/, A/./Band A/foo/../B all become A/B. This string manipulation may change the meaning of a path that contains symbolic links. On Windows, it converts forward slashes to backward slashes. To normalize case, use normcase().

通过折叠冗余分隔符和上一级引用来规范化路径名，使a//b、a/b/、a//b and a/foo/。/b都成为a/b。此字符串操作可能会更改包含符号链接的路径的含义。在Windows上，它将前斜杠转换为后斜杠。要规范化大小写，请使用normcase（）。


#### os.path.realpath(path)

Return the canonical path of the specified filename, eliminating any symbolic links encountered in the path (if they are supported by the operating system).

返回指定文件名的规范路径，消除路径中遇到的任何符号链接（如果操作系统支持）。


#### os.path.relpath(path, start=os.curdir)

Return a relative filepath to path either from the current directory or from an optional start directory. This is a path computation: the filesystem is not accessed to confirm the existence or nature of path or start.

从当前目录或可选的开始目录返回路径的相对文件路径。这是一个路径计算：不能访问文件系统来确认路径或开始的存在或性质。


#### os.path.samefile(path1, path2)

Return True if both pathname arguments refer to the same file or directory. This is determined by the device number and i-node number and raises an exception if an os.stat() call on either pathname fails.

如果两个路径指向相同的文件或目录，则返回True



#### os.path.sameopenfile(fp1, fp2)

Return True if the file descriptors fp1 and fp2 refer to the same file.

如果文件描述符fp1和fp2引用同一文件，则返回true。


#### os.path.samestat(stat1, stat2)

Return True if the stat tuples stat1 and stat2 refer to the same file. These structures may have been returned by os.fstat(), os.lstat(), or os.stat(). This function implements the underlying comparison used by samefile() and sameopenfile().



#### os.path.split(path)

Split the pathname path into a pair, (head, tail) where tail is the last pathname component and head is everything leading up to that. The tail part will never contain a slash; if path ends in a slash, tail will be empty. If there is no slash in path, head will be empty. If path is empty, both head and tail are empty. Trailing slashes are stripped from head unless it is the root (one or more slashes only). In all cases, join(head, tail)returns a path to the same location as path (but the strings may differ). Also see the functions dirname() andbasename().

将路径名路径拆分为一对（head，tail），其中tail是最后一个路径名组件，head是指向该组件的所有内容。尾部部分永远不会包含斜线；如果路径以斜线结尾，则尾部将为空。如果路径中没有斜线，则头部将为空。如果路径是空的，那么头部和尾部都是空的。尾随斜线从头部剥离，除非它是根（仅一个或多个斜线）。在所有情况下，join（head，tail）都将路径返回到与path相同的位置（但字符串可能不同）。另请参见函数dirname（）和basename（）。



#### os.path.splitdrive(path)

Split the pathname path into a pair (drive, tail) where drive is either a mount point or the empty string. On systems which do not use drive specifications, drive will always be the empty string. In all cases, drive +tail will be the same as path.

On Windows, splits a pathname into drive/UNC sharepoint and relative path.

If the path contains a drive letter, drive will contain everything up to and including the colon. e.g. splitdrive("c:/dir") returns ("c:", "/dir")

If the path contains a UNC path, drive will contain the host name and share, up to but not including the fourth separator. e.g. splitdrive("//host/computer/dir") returns ("//host/computer", "/dir")

将路径名路径拆分为一对（drive，tail），其中drive是装入点或空字符串。在不使用驱动器规格的系统上，驱动器始终是空字符串。在所有情况下，驱动+尾部将与路径相同。
在Windows上，将路径名拆分为驱动器/UNC SharePoint和相对路径。
如果路径包含驱动器号，则驱动器将包含冒号之前（包括冒号）的所有内容。例如splitdrive（“c:/dir”）返回（“c：”，/dir”）
如果路径包含UNC路径，驱动器将包含主机名和共享，最多不包括第四个分隔符。例如splitdrive（“//host/computer/dir”）返回（“//host/computer”，“/dir”）。



#### os.path.splitext(path)

Split the pathname path into a pair (root, ext) such that root + ext == path, and ext is empty or begins with a period and contains at most one period. Leading periods on the basename are ignored; splitext('.cshrc') returns ('.cshrc', '').

将路径名路径拆分为一对（root，ext），这样root+ext==path，ext为空或以句点开头，最多包含一个句点。忽略basename上的前导句点；splitext（“.cshrc”）返回（“.cshrc”，“”。


#### os.path.supports_unicode_filenames

True if arbitrary Unicode strings can be used as file names (within limitations imposed by the file system).

True如果任意Unicode字符串can be used as names（文件在文件系统的局限性imposed by the）。