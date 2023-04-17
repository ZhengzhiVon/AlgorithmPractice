class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);//定义虚拟头节点
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        //每次循环中，将fast指向下一个节点，同时将n减1，直到n减为0或fast指向NULL为止。
        while(n-- && fast != NULL) {//让fast先走n步
            fast = fast->next;
        }
        if(fast==NULL){//如果n大于链表长度则fast走到NULL，此时直接返回原链表。
            return head;
        }
        fast = fast->next; // fast再提前走一步，因为需要让slow指向删除节点的上一个节点
        while (fast != NULL) {//同时移动slow和fast，直到fast走到链表尾部。
            fast = fast->next;
            slow = slow->next;
        }
         //此时slow指向删除节点的上一个节点，将slow->next指向slow->next->next即可完成删除操作。
        slow->next = slow->next->next; 
        
        // ListNode *tmp = slow->next;  C++释放内存的逻辑
        // slow->next = tmp->next;
        // delete nth;
        
        return dummyHead->next;
        delete dummyHead;
    }
};