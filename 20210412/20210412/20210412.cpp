#include<iostream>
using namespace std;



struct Node
{
	int data;
	Node *next;
};
class LinkedList
{
public:
	LinkedList(const int &n);
	LinkedList(const LinkedList &aplist);
	~LinkedList();
	void display();
	void insert_before(const int &key, const int &toinsert);
	void del(const int &todelete);
	Node* find_key(const int &key);
	void distroy();
	int getLength();
private:
	Node *head;
	Node *cur;
};


LinkedList::LinkedList(const int &n)
{
	head = new Node;
	head->data = -1;
	head->next = NULL;
	Node *p = head;
	int i;
	cout << "请输入链表序列：" << endl;
	for (i = 0; i<n; i++)
	{
		cur = new Node;
		cin >> cur->data;
		cur->next = NULL;
		p->next = cur;
		p = cur;
	}
}
LinkedList::~LinkedList()
{
	cout << "***";
	distroy();
}
void LinkedList::display()
{
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表为空！" << endl;
		return;
	}
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;// 多一个空格的
}


void LinkedList::del(const int &todelete)
{
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return;
	}
	Node *p = head;
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表为空，删除失败！" << endl;
		return;
	}
	while (cur != NULL && cur->data != todelete)
	{
		p = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		cout << "此元素不存在，删除失败！" << endl;// 当然也可能此链表为空
	else
	{
		cout << "成功删除元素：" << cur->data << endl;
		p->next = cur->next;
		delete cur;
	}
}
void LinkedList::insert_before(const int &key, const int &toinsert)
{
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return;
	}
	Node *p, *tmp;
	p = head;
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表为空，插入失败！" << endl;// 当然也可能此链表为空
		return;
	}
	while (cur != NULL && cur->data != key)
	{
		p = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		cout << key << "：此元素不存在，插入失败！" << endl;
	else
	{
		tmp = new Node;
		tmp->data = toinsert;
		tmp->next = NULL;
		p->next = tmp;
		tmp->next = cur;
		cout << "成功插入元素：" << toinsert << endl;
	}
}
Node* LinkedList::find_key(const int &key)
{
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return NULL;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表为空，查找失败！" << endl;
		return head;
	}
	while (cur != NULL && cur->data != key)
		cur = cur->next;
	if (cur == NULL)
	{
		cout << key << "此元素不在链表中，查找失败！" << endl;
		return head;
	}
	else
	{
		cout << "成功查找到元素：" << cur->data << endl;
		return cur;
	}
}


void LinkedList::distroy()
{
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表已经为空，无法再次删除！" << endl;
		delete head;//销毁head节点
		head = NULL;// 用于后面的判断
		return;
	}
	while (cur != NULL)
	{
		head->next = cur->next;
		delete cur;
		cur = head->next;
	}
	if (head != NULL)
	{
		delete head;
		head = NULL;
	}
}
int LinkedList::getLength()
{
	int cp = 0;
	if (head == NULL)
	{
		cout << "此链表不存在！" << endl;
		return cp;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "此链表为空！" << endl;
		return cp;
	}
	while (cur != NULL)
	{
		cp++;
		cur = cur->next;
	}
	return cp;
}
