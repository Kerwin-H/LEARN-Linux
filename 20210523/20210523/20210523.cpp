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
	ListNode* getKthFromEnd(ListNode* head, int k) {
		int n = 0;
		for (auto q = head; q; q = q->next)
			n++;
		if (k>n)
			return NULL;

		ListNode *p = head;
		for (int i = 0; i<n - k; ++i){
			p = p->next;
		}
		return p;
	}
};


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
	ListNode* reverseList(ListNode* head) {

		if (!head || !head->next)
			return head;
		ListNode *prev = nullptr;
		ListNode *cur = head;
		while (curr)
		{
			ListNode *temp = cur->next;
			cur->next = prev;
			prev = cur;
			cur = temp;
		}
		return prev;
	}
};


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
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1) return l2;
		if (!l2) return l1;
		ListNode *dummy = new ListNode(INT_MAX);
		ListNode *res = dummy;
		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				res->next = l1;
				l1 = l1->next;
			}
			else
			{
				res->next = l2;
				l2 = l2->next;
			}
			res = res->next;
		}
		res->next = l1 ? l1 : l2;
		return dummy->next;
	}
};
