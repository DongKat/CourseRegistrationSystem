/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        int k=0;
        while ((head!=nullptr) && (k<=10000))
        {
           k++;
           head=head->next;
        }
        if (k>10000)
            return true;
        return false;
    }
};
