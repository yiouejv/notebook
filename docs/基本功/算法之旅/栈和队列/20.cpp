/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
 

示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "()[]{}"
输出：true
示例 3：

输入：s = "(]"
输出：false
示例 4：

输入：s = "([)]"
输出：false
示例 5：

输入：s = "{[]}"
输出：true
 

提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成

*/


/* 利用栈来做，如果是左括号压入栈
 * 如果遇到了右括号，判断栈是否为空，如果为空说明在这个右括号前面都没一个左括号，肯定不合法
 * 如果栈顶元素不是与之匹配的左括号，说明在匹配的括号之间夹杂着其他的左括号，不合法
 * 如果是与之匹配的左括号，则将这左括号弹出栈顶，
 * 如果最后栈为空说明括号全都匹配
 */
class Solution {
public:
    bool isValid(string s) {
        stack<char> sta;

        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                sta.push(c);
            } else {

                if (sta.empty()) {
                    return false;

                } else if (c == ')' && sta.top() != '(') {
                    return false;

                } else if (c == ']' && sta.top() != '[') {
                    return false;

                } else if (c == '}' && sta.top() != '{') {
                    return false;
                }
                sta.pop();
            }
        }
        return sta.empty();
    }
};

