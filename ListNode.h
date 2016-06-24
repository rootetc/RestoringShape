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
	//friend Node; friend는 외부에서 private에 접근을 가능하게 해준다.
private:
	int listnode_count;

public:
	Node* nptr; // list에서 움직이는 부분이다.
	Node* head; // 시작 point, 항상 머리 부분을 가리킨다.

	ListNode();
	~ListNode();
	void List_delete();
	void List_insert(float x, float y, float z);
	int List_count();
};

//int ListNode::count2 = 0; // class에서 static은 외부에서 초기화 해주어야 한다. 무조건 !!!!!!!!!!!!!!!!! struct도 똑같다.
//밖에서 선언 왜?? 객체를 생성 할때 마다 초기화 된다면 의미가 없기 때문이다.
