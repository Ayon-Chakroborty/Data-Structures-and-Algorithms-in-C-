
#include "ListLinked.h"

// ListNode member functions

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}

// List member functions

template <typename DataType>
List<DataType>::List(int ignored)
{
	head = 0;
	cursor = 0;
}

template <typename DataType>
List<DataType>::List(const List& other)
{
	head = 0;
	cursor = 0;
	operator=(other);
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	if (this != &other) {
		clear();

		//head
		ListNode* otherPointer = other.head;
		//cursor
		ListNode* holder = 0;
		//deep copy for every listnode object
		while (otherPointer != 0) {
			insert(otherPointer->dataItem);
			if (otherPointer == other.cursor) {
				holder = other.cursor;
			}
		}
		cursor = holder;
	}
	return *this;

}

template <typename DataType>
List<DataType>::~List()
{
	delete[] head;
	delete[] cursor;
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty())
	{
		head = new ListNode(newDataItem, 0);
		cursor = head;
	}
	else
	{
		cursor->next = new ListNode(newDataItem, cursor->next);
		cursor = cursor->next;
	}
}

template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	ListNode* preFunc = new ListNode(NULL, 0);
	ListNode* ItemDel = new ListNode(NULL, 0);
	
	if (cursor == head) {
		preFunc = head;
		head = ItemDel->next;
		cursor = head;
		delete ItemDel;
		return;
	}

	ListNode* NodeCheck;
	NodeCheck = 0;
	preFunc = head;
	ItemDel = head->next;


	while (ItemDel != NULL) {
		if (ItemDel == cursor) {
			preFunc->next = ItemDel->next;
			cursor = preFunc->next;
			delete ItemDel; 
		}
		preFunc = ItemDel;
		preFunc = ItemDel->next;
	}

	if (NodeCheck != 0) {
		ListNode* prefunction = new ListNode(NULL, 0);
		ListNode* postfunction = new ListNode(NULL, 0);

		if (cursor == head) {
			prefunction = head;
			head = postfunction->next;
			cursor = head;
			delete postfunction;
			return;
		}

		prefunction = head;
		postfunction = head->next;
	}
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty())
		throw logic_error("This is empty");
	cursor->dataitem = newDataItem;
	//moving across list to find cursor
	ListNode* temp = head;
	if (temp != NULL) {
		while (temp->next != cursor->next) {
			temp = temp->next;
			break;
		}
	}

}

template <typename DataType>
void List<DataType>::clear()
{
	cursor = head;
	while (cursor != NULL) {
		cursor->dataItem = NULL;
		cursor->next;

	}
	head = 0;
	cursor = head;

}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("List is empty");
	}
	else
		cursor = head;
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if (isEmpty() == false) {
		throw logic_error("List is empty");
		return false;
	}
	else {
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		return true;
	}

}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	if (isEmpty() == false) {
		throw logic_error("List is empty");
		return false;
	}
	else {
		if (cursor->next != NULL) {
			cursor = cursor->next;
		}
		return true;
	}
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if (isEmpty() == false) {
		throw logic_error("List is empty");
		return false;
	}
	if (cursor == head) {
		return false;
	}
		ListNode* BeforeCursor;
		BeforeCursor = head;
		//Beforecursor traversing the list until it reaches cursor
		while (BeforeCursor->next != cursor) {
			BeforeCursor = BeforeCursor->next;
		}
		cursor = BeforeCursor;
		return true;
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	if (isEmpty() == false) {
		throw logic_error("List is empty");
	}
	DataType t = NULL;
	t = cursor->dataItem;
	return t;
}

template <typename DataType>
void List<DataType>::moveToBeginning() throw (logic_error)
{
	if (isEmpty() == false) {
		throw logic_error("List is empty");
	}
	ListNode* NEWHEAD;
	for(NEWHEAD=head; NEWHEAD->next !=cursor; NEWHEAD=NEWHEAD->next)
	NEWHEAD->next = cursor->next;
	cursor->next = head;
	head = cursor;
}

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		head = new ListNode(newDataItem, NULL);
		cursor = head;
	}
	ListNode* tmp = new ListNode(cursor->dataItem, cursor->next);
	cursor->next = tmp;
	cursor->dataItem = newDataItem;
}

#include "show5.cpp"

