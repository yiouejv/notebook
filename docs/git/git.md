
## 在线练习
<https://learngitbranching.js.org/?locale=zh_CN>

## 阅读git官网的Book, 顺手记录一下，方便查阅   
<https://git-scm.com/book/en/v2>  

## git 基础命令
### git config  
1. /etc/gitconfig 文件: 包含系统上每一个用户及他们仓库的通用配置。 如果在执行 git config 时带上 --system 选项，那么它就会读写该文件中的配置变量。 （由于它是系统配置文件，因此你需要管理员或超级用户权限来修改它。）

- ~/.gitconfig 或 ~/.config/git/config 文件：只针对当前用户。 你可以传递 --global 选项让 Git 读写此文件，这会对你系统上 所有 的仓库生效。

- 当前使用仓库的 Git 目录中的 config 文件（即 .git/config）：针对该仓库。 你可以传递 --local 选项让 Git 强制读写此文件，虽然默认情况下用的就是它。。 （当然，你需要进入某个 Git 仓库中才能让该选项生效。）

- 配置用户：  
    - git config --global user.name "username"  
    - git config --global user.eamil "email"  
    - 当你想针对特定项目使用不同的用户名称与邮件地址时，可以在那个项目目录下运行没有 --global 选项的命令来配置。(--local 相当于上述的local)  

- 配置编辑器  
    - git config --global core.editor.vim  
    - 当 Git 需要你输入信息时会调用它。 如果未配置，Git 会使用操作系统默认的文本编辑器。  

- 查看配置信息  
    - <span style="color: red;">查看当前仓库的配置: </span>git config --list  
    - git config < key >  

### git help  
1. git help < verb >  
- git < verb > --help  
- man git-< verb >

### git init   
该命令将创建一个名为 .git 的子目录，这个子目录含有你初始化的 Git 仓库中所有的必须文件，这些文件是 Git 仓库的骨干。 但是，在这个时候，我们仅仅是做了一个初始化的操作，你的项目里的文件还没有被跟踪。

### git clone  
1. 如果你想获得一份已经存在了的 Git 仓库的拷贝，比如说，你想为某个开源项目贡献自己的一份力，这时就要用到 git clone 命令。  
- 如果你对其它的 VCS 系统（比如说 Subversion）很熟悉，请留心一下你所使用的命令是"clone"而不是"checkout"。 这是 Git 区别于其它版本控制系统的一个重要特性，Git 克隆的是该 Git 仓库服务器上的几乎所有数据，而不是仅仅复制完成你的工作所需要文件。  
- 当你执行 git clone 命令的时候，默认配置下远程 Git 仓库中的每一个文件的每一个版本都将被拉取下来。 事实上，如果你的服务器的磁盘坏掉了，你通常可以使用任何一个克隆下来的用户端来重建服务器上的仓库 （虽然可能会丢失某些服务器端的钩子（hook）设置，但是所有版本的数据仍在.  
- 克隆仓库的命令是  <span style="color: red;">git clone < url ></span>
- 克隆远程仓库的时候，自定义本地仓库的名字 <span style="color: red;">git clone < url > newname</span>
    
### git status  
1. 可以用 git status 命令查看哪些文件处于什么状态。
2. git status --short 得到一种格式更为紧凑的输出

### git add

1. 跟踪一个未跟踪的文件。
2. 将跟踪的文件放入暂存区

- git add -A  提交所有变化
- git add -u  提交被修改(modified)和被删除(deleted)文件，不包括新文件(new)
- git add .  提交新文件(new)和被修改(modified)文件，不包括被删除(deleted)文件


### .gitignore
一般我们总会有些文件无需纳入 Git 的管理，也不希望它们总出现在未跟踪文件列表。 通常都是些自动生成的文件，比如日志文件，或者编译过程中创建的临时文件等。 在这种情况下，我们可以创建一个名为 .gitignore 的文件，列出要忽略的文件的模式。 

```
*.[oa]
*~
```  
第一行告诉 Git 忽略所有以 .o 或 .a 结尾的文件。  
第二行告诉 Git 忽略所有名字以波浪符（~）结尾的文件，许多文本编辑软件（比如 Emacs）都用这样的文件名保存副本。
***文件 .gitignore 的格式规范如下：***  
- 所有空行或者以 # 开头的行都会被 Git 忽略。  
- 可以使用标准的 glob 模式匹配，它会递归地应用在整个工作区中。  
- 匹配模式可以以（/）开头防止递归。  
- 匹配模式可以以（/）结尾指定目录。  
- 要忽略指定模式以外的文件或目录，可以在模式前加上叹号（!）取反。

### git diff
1. 不加参数直接输入 git diff : 尚未暂存的文件更新了哪些部分   
2. git diff --staged : 已暂存文件与最后一次提交的文件差异  
3. git diff --cached : --staged 和 --cached 是同义词
4. git diff --check ： 它将会找到可能的空白错误并将它们为你列出来

### git commit
1. git commit -m "message": 提交代码
2. 请记住，提交时记录的是放在暂存区域的快照。 任何还未暂存文件的仍然保持已修改状态，可以在下次提交时纳入版本管理。 每一次运行提交操作，都是对你项目作一次快照，以后可以回到这个状态，或者进行比较。  
3. git commit -m -a "message": 尽管使用暂存区域的方式可以精心准备要提交的细节，但有时候这么做略显繁琐。 Git 提供了一个跳过使用暂存区域的方式， 只要在提交的时候，给 git commit 加上 -a 选项，Git 就会自动把所有已经跟踪过的文件暂存起来一并提交。  
4. git commit -amend: 修改提交

### git rm
1. git rm file: 从已跟踪文件清单中移除（确切地说，是从暂存区域移除）, 并连带从工作目录中删除指定的文件
2. git rm -f file: 如果要删除之前修改过或已经放到暂存区的文件，则必须使用强制删除选项 -f（译注：即 force 的首字母）  
3. git rm --cached file: 让文件保留在磁盘，但是并不想让 Git 继续跟踪。  

### git mv
1. git mv README.md README 相当于  
```
mv README.md README
git rm README.md
git add README
```
不像其它的 VCS 系统，Git 并不显式跟踪文件移动操作。 如果在 Git 中重命名了某个文件，仓库中存储的元数据并不会体现出这是一次改名操作。 不过 Git 非常聪明，它会推断出究竟发生了什么。

### git log
1. 在提交了若干更新，又或者克隆了某个项目之后，你也许想回顾下提交历史。 完成这个任务最简单而又有效的工具是 git log 命令   
- git log --patch, 它会显示每次提交所引入的差异（按 补丁 的格式输出）, 你也可以限制显示的日志条目数量，例如使用 -2 选项来只显示最近的两次提交： git log -p -2  
- git log --stat, 每次提交的简略统计信息, 可以使用 --stat 选项  
- git log --relative-date, 使用较短的相对时间而不是完整格式显示日期（比如“2 weeks ago”）  
- git log --name-status, 显示新增、修改、删除的文件清单  
- git log -oneline, --pretty=oneline --abbrev-commit 合用的简写。  
- git log --author author_name, 显示指定作者的提交
- git log --grep, 搜索提交说明中的关键字
- git log -S function_name, 只会显示那些添加或删除了该字符串的提交, 假设你想找出添加或删除了对某一个特定函数的引用的提交，可以调用
- 以上的够用了，更多的<https://git-scm.com/book/zh/v2/Git-基础-查看提交历史>  

### git reset
1. git reset HEAD [< file >], 取消暂存的文件

### git stash
希望回到以前的版本，但又不想把现有的代码提交。
1. git stash 创建临时工作去
2. git stash list 查看保存的工作区
3. git stash apply stash@{1}  应用哪个工作区
4. git stash pop 应用上一个工作区并且删除
5. git stash drop stash@{0} 删除指定的工作区
6. git stash clear 删除所有的工作区

### git checkout
1. git checkout -- < file >, <span style="color: red;">请务必记得 git checkout -- < file > 是一个危险的命令</span>。 你对那个文件在本地的任何修改都会消失——Git 会用最近提交的版本覆盖掉它。 除非你确实清楚不想要对那个文件的本地修改了，否则请不要使用这个命令。

### git stash
1. git stash: 创建保存临时工作区
- git stash list: 查看保存的工作区
- git stash apply stash@{1}: 应用哪个工作区
- git stash pop: 应用上一个工作区并且删除
- git stash drop stash@{0}: 删除指定的工作区
- git stash clear: 删除所有的工作区


### git remote
1. 运行 git remote 命令, 它会列出你指定的每一个远程服务器的简写。
2. git remote -v, 会显示需要读写远程仓库使用的 Git 保存的简写与其对应的 URL
3. git remote add < shortname > < url >, 添加一个新的远程 Git 仓库，同时指定一个方便使用的简写
4. git remote show < remote >, 查看某一个远程仓库的更多信息
5. git remote rename, 修改一个远程仓库的简写名  
    - git remote rename pb paul，将 pb 重命名为 paul
6. git remote remove, 移除一个远程仓库
    - 你已经从服务器上搬走了或不再想使用某一个特定的镜像了
    - 又或者某一个贡献者不再贡献了——可以使用 git remote remove 或 git remote rm

### git fetch
1. git fetch < remote >, 这个命令会访问远程仓库，从中拉取所有你还没有的数据, 执行完成后，你将会拥有那个远程仓库中所有分支的引用，可以随时合并或查看。   
    - 如果你使用 clone 命令克隆了一个仓库，命令会自动将其添加为远程仓库并默认以 “origin” 为简写。 所以，git fetch origin 会抓取克隆（或上一次抓取）后新推送的所有工作。   
    - 必须注意 git fetch 命令只会将数据下载到你的本地仓库——它并不会自动合并或修改你当前的工作。 当准备好时你必须手动将其合并入你的工作。

### git push
1. git push origin master, 只有当你有所克隆服务器的写入权限，并且之前没有人推送过时，这条命令才能生效。 当你和其他人在同一时间克隆，他们先推送到上游然后你再推送到上游，你的推送就会毫无疑问地被拒绝。 你必须先抓取他们的工作并将其合并进你的工作后才能推送。

### git tag
1. git tag --lits, 列出已有的标签  
    - git tag -l "v1.8.5*", 你也可以按照特定的模式查找标签。 例如，Git 自身的源代码仓库包含标签的数量超过 500 个。 如果只对 1.8.5 系列感兴趣，可以运行 git tag -l "v1.8.5*"   
- git tag -a v1.4 -m "my version 1.4", 创建附注标签(annotated)  
    - git show v1.4, 标签信息和与之对应的提交信息  
- git tag v1.4-lw, 创建轻量标签(lightweight)  
    - 轻量标签本质上是将提交校验和存储到一个文件中——没有保存任何其他信息   
    - 创建轻量标签，不需要使用 -a、-s 或 -m 选项，只需要提供标签名字  
- 后期打标签  
    - git tag -a v1.2 9fceb02, 要在那个提交上打标签，你需要在命令的末尾指定提交的校验和（或部分校验和）
- 共享标签
    - git push origin < tagname >, 默认情况下，git push 命令并不会传送标签到远程仓库服务器上。 在创建完标签后你必须显式地推送标签到共享服务器上  
    - git push origin --tags, 如果想要一次性推送很多标签，也可以使用带有 --tags 选项的 git push 命令。 这将会把所有不在远程仓库服务器上的标签全部传送到那里  
    - <span style="color: red;">使用 git push < remote > --tags 推送标签并不会区分轻量标签和附注标签， 没有简单的选项能够让你只选择推送一种标签。</span>
- git tag -d < tagname >, 删除掉你本地仓库上的标签  
    - 注意上述命令并不会从任何远程仓库中移除这个标签，你必须用 git push < remote > :refs/tags/< tagname > 来更新你的远程仓库, 上面这种操作的含义是，将冒号前面的空值推送到远程标签名，从而高效地删除它。  
    - 第二种更直观的删除远程标签的方式是： git push origin --delete < tagname >


## git 分支  
git 分支工作原理： <https://git-scm.com/book/zh/v2/Git-分支-分支简介>

### git branch
1. git branch, 得到当前所有分支
    - git branch -v, 查看每一个分支的最后一次提交   
    - git branch --merged, 查看哪些分支已经合并到当前分支  
    - git branch --no-merged, 查看哪些分支尚未合并到当前分支  
    - git branch --no-merged master，查看哪些分支尚未合并到master分支  
- git branch < name >, 创建分支，为你创建了一个可以移动的新的指针  
- git branch -d < branchname >, 删除分支  
- git branch -u origin/serverfix, 设置已有的本地分支跟踪一个刚刚拉取下来的远程分支，或者想要修改正在跟踪的上游分支， 你可以在任意时间使用 -u 或 --set-upstream-to 选项运行 git branch 来显式地设置
- git branch -vv, 如果想要查看设置的所有跟踪分支, 这会将所有的本地分支列出来并且包含更多的信息，如每一个分支正在跟踪哪个远程分支与本地分支是否是领先、落后或是都有。
    - 需要重点注意的一点是这些数字的值来自于你从每个服务器上最后一次抓取的数据。 这个命令并没有连接服务器，它只会告诉你关于本地缓存的服务器数据。 如果想要统计最新的领先与落后数字，需要在运行此命令前抓取所有的远程仓库。 可以像这样做：git fetch --all; git branch -vv  
- git branch -f master HEAD~3  
### git checkout
1. git checkout master, 这条命令做了两件事。  
    - 一是使 HEAD 指回 master 分支  
    - 二是将工作目录恢复成 master 分支所指向的快照内容   
2. git checkout -b < newbranchname >, 创建一个新分支后立即切换过去  
3. git checkout -b < branch > < remote >/< branch >, 创建一个新分支后立即切换过去, 并且跟踪远程仓库的分支

### git merge
1. git merge < branchname >, 在当前分支合并另一个分支的修改  
    - 当你试图合并两个分支时， 如果顺着一个分支走下去能够到达另一个分支，那么 Git 在合并两者的时候， 只会简单的将指针向前推进（指针右移），因为这种情况下的合并操作没有需要解决的分歧——这就叫做 “快进（fast-forward）”

### git add 
1. 合并时把有冲突的文件标记为已解决状态

### git push 
1. git push origin --delete < branchname >, 删除远程分支

### git rebase 变基
详情： <https://git-scm.com/book/zh/v2/Git-分支-变基>

### 如何避免每次输入密码
1. git config --global credential.helper cache, 如果你正在使用 HTTPS URL 来推送，Git 服务器会询问用户名与密码。 默认情况下它会在终端中提示服务器是否允许你进行推送。
如果不想在每一次推送时都输入用户名与密码，你可以设置一个 “credential cache”。 最简单的方式就是将其保存在内存中几分钟，可以简单地运行 git config --global credential.helper cache 来设置它。