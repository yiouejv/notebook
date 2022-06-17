/*
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 

注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
 

示例：

输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
 

提示：

1 <= x <= 9
最多调用100 次 push、pop、top 和 empty
每次调用 pop 和 top 都保证栈不为空
 

进阶：你能否仅用一个队列来实现栈。

*/

/*
 * 俩个队列互相倒腾，
 * 把一个有元素的队列往没有元素的队列倒腾元素，自己只留一个元素，
 * 最后把自己剩的最后一个元素pop出去
 */

class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        if (queue1.empty()) {
            queue2.push(x);
        } else {
            queue1.push(x);
        }
    }
    
    int pop() {
        int ret;
        if (queue1.empty()) {
            while (queue2.size() != 1) {
                queue1.push(queue2.front());
                queue2.pop();
            }
            ret = queue2.front();
            queue2.pop();
        } else {
            while (queue1.size() != 1) {
                queue2.push(queue1.front());
                queue1.pop();
            }
            ret = queue1.front();
            queue1.pop();
        }
        return ret;
    }
    
    int top() {
        int ret = this->pop();
        this->push(ret);
        return ret;
    }
    
    bool empty() {
        return queue1.empty() && queue2.empty();
    }
private:
    queue<int> queue1;
    queue<int> queue2;
};

/*
 * 一个对列，弹出时只需把不是最后一个元素重新push回队列
 */
class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        queue1.push(x);
        ++size;
    }
    
    int pop() {
        int ret;
        int index = 0;

        while (index < size - 1) {
            ret = queue1.front();
            queue1.pop();
            queue1.push(ret);
            ++index;
        }
        ret = queue1.front();
        queue1.pop();

        --size;
        return ret;
    }
    
    int top() {
        int ret = this->pop();
        this->push(ret);
        return ret;
    }
    
    bool empty() {
        return queue1.empty();
    }
private:
    queue<int> queue1;
    int size = 0;
};

