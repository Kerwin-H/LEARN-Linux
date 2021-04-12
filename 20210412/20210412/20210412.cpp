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
	cout << "�������������У�" << endl;
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
		cout << "���������ڣ�" << endl;
		return;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "������Ϊ�գ�" << endl;
		return;
	}
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;// ��һ���ո��
}


void LinkedList::del(const int &todelete)
{
	if (head == NULL)
	{
		cout << "���������ڣ�" << endl;
		return;
	}
	Node *p = head;
	cur = head->next;
	if (cur == NULL)
	{
		cout << "������Ϊ�գ�ɾ��ʧ�ܣ�" << endl;
		return;
	}
	while (cur != NULL && cur->data != todelete)
	{
		p = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		cout << "��Ԫ�ز����ڣ�ɾ��ʧ�ܣ�" << endl;// ��ȻҲ���ܴ�����Ϊ��
	else
	{
		cout << "�ɹ�ɾ��Ԫ�أ�" << cur->data << endl;
		p->next = cur->next;
		delete cur;
	}
}
void LinkedList::insert_before(const int &key, const int &toinsert)
{
	if (head == NULL)
	{
		cout << "���������ڣ�" << endl;
		return;
	}
	Node *p, *tmp;
	p = head;
	cur = head->next;
	if (cur == NULL)
	{
		cout << "������Ϊ�գ�����ʧ�ܣ�" << endl;// ��ȻҲ���ܴ�����Ϊ��
		return;
	}
	while (cur != NULL && cur->data != key)
	{
		p = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		cout << key << "����Ԫ�ز����ڣ�����ʧ�ܣ�" << endl;
	else
	{
		tmp = new Node;
		tmp->data = toinsert;
		tmp->next = NULL;
		p->next = tmp;
		tmp->next = cur;
		cout << "�ɹ�����Ԫ�أ�" << toinsert << endl;
	}
}
Node* LinkedList::find_key(const int &key)
{
	if (head == NULL)
	{
		cout << "���������ڣ�" << endl;
		return NULL;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "������Ϊ�գ�����ʧ�ܣ�" << endl;
		return head;
	}
	while (cur != NULL && cur->data != key)
		cur = cur->next;
	if (cur == NULL)
	{
		cout << key << "��Ԫ�ز��������У�����ʧ�ܣ�" << endl;
		return head;
	}
	else
	{
		cout << "�ɹ����ҵ�Ԫ�أ�" << cur->data << endl;
		return cur;
	}
}


void LinkedList::distroy()
{
	if (head == NULL)
	{
		cout << "���������ڣ�" << endl;
		return;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "�������Ѿ�Ϊ�գ��޷��ٴ�ɾ����" << endl;
		delete head;//����head�ڵ�
		head = NULL;// ���ں�����ж�
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
		cout << "���������ڣ�" << endl;
		return cp;
	}
	cur = head->next;
	if (cur == NULL)
	{
		cout << "������Ϊ�գ�" << endl;
		return cp;
	}
	while (cur != NULL)
	{
		cp++;
		cur = cur->next;
	}
	return cp;
}
