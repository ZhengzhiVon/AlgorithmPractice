/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//时间复杂度：O(N)
//空间复杂度：O(1)

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;//slow速度为1，每次后移1个结点
            fast = fast->next->next;//fast速度为2，每次后移2个节点
            // 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
            if (slow == fast) {//快慢指针相遇，确定相遇节点
                ListNode* index1 = fast;//标记相遇结点
                ListNode* index2 = head;//标记初始头节点
                while (index1 != index2) {//相遇节点到入口节点的距离=头节点到入口节点的距离
                    index1 = index1->next;//速度为1
                    index2 = index2->next;//速度为1
                }
                return index2; // 返回环的入口
            }
        }
        return NULL;//当fast或者fast->next为空
    }
};