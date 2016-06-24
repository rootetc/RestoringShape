#pragma once
#ifndef _LISTNODE_H_
#define _LISTNODE_H_
#endif

class Node{
public:
	float x, y, z;
	Node* next;

	Node(){
		x = y = z = 0;
		next = NULL;
	}
	Node(float _x, float _y, float _z){
		x = _x, y = _y, z = _z;
		next = NULL;
	}
};


class ListNode
{
	//friend Node; friend�� �ܺο��� private�� ������ �����ϰ� ���ش�.
private:
	int listnode_count;

public:
	Node* nptr; // list���� �����̴� �κ��̴�.
	Node* head; // ���� point, �׻� �Ӹ� �κ��� ����Ų��.

	ListNode();
	~ListNode();
	void List_delete();
	void List_insert(float x, float y, float z);
	int List_count();
};

//int ListNode::count2 = 0; // class���� static�� �ܺο��� �ʱ�ȭ ���־�� �Ѵ�. ������ !!!!!!!!!!!!!!!!! struct�� �Ȱ���.
//�ۿ��� ���� ��?? ��ü�� ���� �Ҷ� ���� �ʱ�ȭ �ȴٸ� �ǹ̰� ���� �����̴�.
