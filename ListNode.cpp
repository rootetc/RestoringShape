#include "stdafx.h"
#include "ListNode.h"
ListNode::ListNode()
{
	this->head = NULL;
	nptr = head;
	listnode_count = 0;
}
ListNode::~ListNode(){
	if (nptr != NULL){
		delete nptr;
	}
}
void ListNode::List_delete(){
	Node* tmp_ptr;
	while (head != NULL){
		tmp_ptr = head;
		head = head->next;
		delete tmp_ptr;
	}
}
void ListNode::List_insert(float x, float y, float z){
	if (head != NULL){
		nptr->next = new Node(x, y, z);
		nptr = nptr->next;
	}else{
		//head = new Node(x, y, z);
		nptr = head;
	}
	++listnode_count;
}

int ListNode::List_count(){
	return listnode_count;
}
