class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        bool co = 0;    // 表示进位
        ListNode head;  // 头结点
        ListNode *p = &head;
        
        while( l1 || l2 || co ) {
            int sum = co;
            if(l1) sum += l1->val, l1 = l1->next;
            if(l2) sum += l2->val, l2 = l2->next;
            co = sum/10;
            ListNode* node = new ListNode(sum%10);
            p->next = node; p = p->next;   
        }
        return head.next;
    }
};
