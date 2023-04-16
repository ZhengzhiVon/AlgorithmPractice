#include <cstddef>
#include<iostream>
using namespace std;

class{
private:
    //定义链表结点结构体
    struct LinkedNode{
        int val;
        LinkedNode* next;
        LinkedNode(int val):val(val),next(nullptr){}
    };
    int _size;
    LinkedNode* _dummyHead;
    
public:
    //初始化链表
    MyLinkedList(){
        _dummyHead=new LinkedNode(0);//定义虚拟头节点
        _size=0;
    }

    //获取到第index个结点的数值
    int get(int index){
        if(index>(_size-1)||index<0){
            return -1;
        }
        LinkedNode* cur=_dummyHead->next;
        while (index--) {//--index会陷入死循环
            cur=cur->next;
        }//通过一个指针cur指向当前节点，每次循环将cur指向下一个节点，直到遍历到第index个节点。
        return cur->val;
    }

    //在链表最前面插入一个结点，插入完成后新插入的节点为新头节点
    void addAtHead(int val){
        LinkedNode* newNode=new LinkedNode(val);
        newNode->next=_dummyHead->next;//将新节点的next指针指向虚拟头节点的下一个节点，即原来的第一个节点。
        _dummyHead->next=newNode;//将虚拟头节点的next指针指向新节点，即将新节点插入到链表头部。
        _size++;//链表大小+1
    }

    //在链表最后面添加一个节点
    void addAtTail(int val){
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while(cur->next!=nullptr){
            cur=cur->next;
        }
        cur->next=newNode;
        _size++;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    // 如果index小于0，则在头部插入节点
    void addAtIndex(int index, int val) {
        if(index > _size) return;
        if(index < 0) index = 0;        
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while(index--) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    // 删除第index个节点，如果index 大于等于链表的长度，直接return，注意index是从0开始的
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        }
        LinkedNode* cur = _dummyHead;
        while(index--) {
            cur = cur ->next;
        }
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        _size--;
    }

    // 打印链表
    void printLinkedList() {
        LinkedNode* cur = _dummyHead;
        while (cur->next != nullptr) {
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }

}