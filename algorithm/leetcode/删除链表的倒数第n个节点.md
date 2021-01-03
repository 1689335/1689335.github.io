---
sort: 19
---

```
/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第N个节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
       ListNode *pre = head;
       ListNode *next = head;

       if (head == NULL) {
           return NULL;
       }

       while (n-- > 0) {
           next = next->next;
       }

       if (next == NULL) {
           return head->next;
       }

       while (next->next != NULL) {
           pre = pre->next;
           next = next->next;
       }

       pre->next = pre->next->next;

       return head;
    }
};
// @lc code=end


```
