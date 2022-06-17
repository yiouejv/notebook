/*
设计链表的实现。您可以选择使用单链表或双链表。
单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。
如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。

在链表类中实现这些功能：

get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
 

示例：

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
linkedList.get(1);            //返回2
linkedList.deleteAtIndex(1);  //现在链表是1-> 3
linkedList.get(1);            //返回3
 

提示：

所有val值都在 [1, 1000] 之内。
操作次数将在  [1, 1000] 之内。
请不要使用内置的 LinkedList 库。

*/
struct LinkNode {
    int val;
    LinkNode *next;
    LinkNode(int val, LinkNode *next=nullptr) : val(val), next(next) {}
};

class MyLinkedList {
private:
    LinkNode *dummy;
    LinkNode *head;
    LinkNode *tail;
    int size;

public:
    MyLinkedList() {
        dummy = new LinkNode(-1);
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    LinkNode *GetNode(int index) const {
        if (index > size - 1) {
            return nullptr;

        } else if (index < 0) {
            return dummy;

        } else if (index == 0) {
            return head;

        } else if (index == size - 1) {
            return tail;
        }
        LinkNode *cur = head;
        int i = 0;
        while (i++ < index) {
            cur = cur->next;
        }
        return cur;
    }
    
    int get(int index) const {
        if (index < 0 || index > size - 1) {
            return -1;
        }
        LinkNode *cur = GetNode(index);
        return cur->val;
    }
    
    void addAtHead(int val) {
        LinkNode *node = new LinkNode(val);
        node->next = head;
        head = node;
        dummy->next = node;
        ++size;
        if (size == 1) {
            tail = head;
        }
    }
    
    void addAtTail(int val) {
        LinkNode *node = new LinkNode(val);
        if (tail) {
            tail->next = node;
        } else {
            head = node;
            dummy->next = head;
        }
        tail = node;
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size) {
            return;
        } else if (index == 0) {
            addAtHead(val);
            return;
        } else if (index == size) {
            addAtTail(val);
            return;
        }
        LinkNode *cur = GetNode(index - 1);
        LinkNode *node = new LinkNode(val);
        node->next = cur->next;
        cur->next = node;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        // 删除的是头节点
        if (index == 0) {
            dummy->next = head->next;
            delete head;
            head = dummy->next;
            --size;
            return;
        }
        // 如果删除的是尾节点则需要特殊处理
        if (index == size - 1) {
            LinkNode *cur = head;
            while (cur->next != tail) {
                cur = cur->next;
            }
            delete tail;
            tail = cur;
            cur->next = nullptr;
            --size;
            return;
        }

        LinkNode *cur = GetNode(index);
        if (!cur) {
            return;
        }
        LinkNode *curNext = cur->next;
        cur->val = curNext->val;
        cur->next = curNext->next;
        if (curNext == tail) {
            tail = cur;
        }
        delete curNext;
        --size;
    }
};

//----------------------------------------
struct LinkNode {
    int val;
    LinkNode *next;
    LinkNode(int val, LinkNode *next=nullptr) : val(val), next(next) {}
};

class MyLinkedList {
private:
    LinkNode *dummy;
    int size;

public:
    MyLinkedList() {
        dummy = new LinkNode(-1);
        size = 0;
    }
    
    int get(int index) const {
        if (index < 0 || index > size - 1) {
            return -1;
        }
        LinkNode *cur = dummy->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        LinkNode *node = new LinkNode(val);
        node->next = dummy->next;
        dummy->next = node;
        ++size;
    }
    
    void addAtTail(int val) {
        LinkNode *cur = dummy;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        LinkNode *node = new LinkNode(val);
        cur->next = node;
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size) {
            return;
        } else if (index <= 0) {
            return addAtHead(val);
        } else if (index == size) {
            return addAtTail(val);
        }
        LinkNode *pre = dummy;
        for (int i = 0; i < index; ++i) {
            pre = pre->next;
        }
        LinkNode *node = new LinkNode(val);
        node->next = pre->next;
        pre->next = node;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        if (index > size - 1 || index < 0) {
            return;
        }

        LinkNode *pre = dummy;
        for (int i = 0; i < index; ++i) {
            pre = pre->next;
        }
        LinkNode *cur = pre->next;
        pre->next = cur->next;
        delete cur;
        --size;
    }
};


/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
