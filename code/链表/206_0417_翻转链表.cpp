//双指针法
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* temp; // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur) {
            temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre; // 翻转操作
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

//递归
class Solution {
public:
    ListNode* reverse(ListNode* pre,ListNode* cur){
        if(cur == NULL) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
        // pre = cur;
        // cur = temp;
        return reverse(cur,temp);
    }
    ListNode* reverseList(ListNode* head) {
        // 和双指针法初始化是一样的逻辑
        // ListNode* cur = head;
        // ListNode* pre = NULL;
        return reverse(NULL, head);
    }

};

//头插法&虚拟头节点
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //创建虚拟头结点
        ListNode* dummyHead=new ListNode(0);
        dummyHead->next=NULL;
        ListNode* cur=head;
        //遍历所有结点
        while(cur!=NULL){
            ListNode* tmp=cur->next;
            //头插法
            cur->next=dummyHead->next;
            dummyHead->next=cur;
            cur=tmp;
        }
        return dummyHead->next;
        delete dummyHead;
    }
};

//使用栈
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //如果链表为空，则返回空
        if(head==NULL) return NULL;
        //如果链表中只有一个元素，则直接返回
        if(head->next==NULL) return head;
        //创建栈，使所有节点入栈
        stack<ListNode> ss;
        ListNode* cur=head;
        while(cur!=NULL){
            ss.push(cur);
            cur=cur->next;
        }

        //创建一个虚拟头节点
        ListNode* dummyHead=new ListNode(0);
        cur=dummyHead;
        while(!ss.empty()){
            ListNode* node=ss.pop();
            cur->next=node;
            cur=cur->next;
        }
        //最后一个元素的next需要赋值为NULL
        cur->next=NULL;
        return dummyHead->next;
        delete dummyHead;
    }
};