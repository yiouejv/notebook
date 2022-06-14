

在网上查了下敏感词过滤方案，找到了一种名为DFA的算法，即Deterministic Finite 

Automaton算法，翻译成中文就是确定有穷自动机算法。它的基本思想是基于状态转移来检索敏感词，只需要扫描一次待检测文本，就能对所有敏感词进行检测，所以效率比方案一高不少。

假设我们有以下5个敏感词需要检测：傻逼、傻子、傻大个、坏蛋、坏人。那么我们可以先把敏感词中有相同前缀的词组合成一个树形结构，不同前缀的词分属不同树形分支，以上述5个敏感词为例，可以初始化成如下2棵树：


把敏感词组成成树形结构有什么好处呢？最大的好处就是可以减少检索次数，我们只需要遍历一次待检测文本，然后在敏感词库中检索出有没有该字符对应的子树就行了，如果没有相应的子树，说明当前检测的字符不在敏感词库中，则直接跳过继续检测下一个字符；如果有相应的子树，则接着检查下一个字符是不是前一个字符对应的子树的子节点，这样迭代下去，就能找出待检测文本中是否包含敏感词了。


我们以文本“你是不是傻逼”为例，我们依次检测每个字符，因为前4个字符都不在敏感词库里，找不到相应的子树，所以直接跳过。当检测到“傻”字时，发现敏感词库中有相应的子树，我们把他记为tree-1，接着再搜索下一个字符“逼”是不是子树tree-1的子节点，发现恰好是，接下来再判断“逼”这个字符是不是叶子节点，如果是，则说明匹配到了一个敏感词了，在这里“逼”这个字符刚好是tree-1的叶子节点，所以成功检索到了敏感词：“傻逼”。大家发现了没有，在我们的搜索过程中，我们只需要扫描一次被检测文本就行了，而且对于被检测文本中不存在的敏感词，如这个例子中的“坏蛋”和“坏人”，我们完全不会扫描到，因此相比方案一效率大大提升了。

在python中，我们可以用dict来存储上述的树形结构，还是以上述敏感词为例，我们把每个敏感词字符串拆散成字符，再存储到dict中，可以这样存：

```python
# -*- coding:utf-8 -*-

import time

time1 = time.time()


# DFA算法
class DFAFilter(object):
    def __init__(self):
        self.keyword_chains = {}  # 关键词链表
        self.delimit = '\x00'  # 限定

    def add(self, keyword):
        keyword = keyword.lower()  # 关键词英文变为小写
        chars = keyword.strip()  # 关键字去除首尾空格和换行
        if not chars:  # 如果关键词为空直接返回
            return
        level = self.keyword_chains
        # 遍历关键字的每个字
        for i in range(len(chars)):
            # 如果这个字已经存在字符链的key中就进入其子字典
            if chars[i] in level:
                level = level[chars[i]]
            else:
                if not isinstance(level, dict):
                    break
                for j in range(i, len(chars)):
                    level[chars[j]] = {}
                    last_level, last_char = level, chars[j]
                    level = level[chars[j]]
                last_level[last_char] = {self.delimit: 0}
                break
        if i == len(chars) - 1:
            level[self.delimit] = 0

    def parse(self, path):
        with open(path, encoding='utf-8') as f:
            for keyword in f:
                self.add(str(keyword).strip())
        print(self.keyword_chains)

    def filter(self, message, repl="*"):
        message = message.lower()
        ret = []
        start = 0
        while start < len(message):
            level = self.keyword_chains
            step_ins = 0
            for char in message[start:]:
                if char in level:
                    step_ins += 1
                    if self.delimit not in level[char]:
                        level = level[char]
                    else:
                        ret.append(repl * step_ins)
                        start += step_ins - 1
                        break
                else:
                    ret.append(message[start])
                    break
            else:
                ret.append(message[start])
            start += 1

        return ''.join(ret)


if __name__ == "__main__":
    gfw = DFAFilter()
    path = "./1.txt"
    gfw.parse(path)
    text = "你真是个大傻逼，大傻子，傻大个，大坏蛋，坏人。"
    result = gfw.filter(text)

    print(text)
    print(result)
    time2 = time.time()
    print('总共耗时：' + str(time2 - time1) + 's')


{'傻': {'大': {'个': {'\x00': 0}}, '逼': {'\x00': 0}}, '坏': {'人': {'\x00': 0}}}
你真是个大傻逼，大傻子，傻大个，大坏蛋，坏人。
你真是个大**，大傻子，***，大坏蛋，**。
总共耗时：0.0s
```