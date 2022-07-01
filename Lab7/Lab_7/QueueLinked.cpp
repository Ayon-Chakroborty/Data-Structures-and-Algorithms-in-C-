
#include "QueueLinked.h"
//Ayon Chakroborty

template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
	front = NULL;
	back = NULL;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
	operator=(other);
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
	if (this != &other) {
		return *this;
	}
	front = new QueueNode(other.front->dataItem, 0);
	QueueNode* otherTemp = other.front->next;
	QueueNode* thisTemp = 0;
	while (otherTemp != NULL) {
		thisTemp = new QueueNode(otherTemp->dataItem, 0);
		thisTemp = thisTemp->next;
	}
}

template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	clear();
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if (isFull()) {
		throw logic_error("Queue is full");
	}
	else {
		QueueNode* insertedItem = new QueueNode(newDataItem, NULL);
		if (isEmpty()) {
			front = insertedItem;
			back = insertedItem;
		}
		else {
			back->next = insertedItem;
			back = insertedItem;
		}
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Queue is Empty");
	}
	else {
		DataType temp = front->dataItem;
		QueueNode* removedItem = front;
		front = front->next;
		free(removedItem);
		return temp;
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
	QueueNode* remove, * nextItem;
	remove = front;
	while (remove != NULL) {
		nextItem = remove->next;
		free(remove);
		remove = nextItem;
	}
	front = NULL;
	back = NULL;

}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	if (front == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	QueueNode* insertedItem = new QueueNode(newDataItem, front);
	front = insertedItem;
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Queue is Empty");
	}
	else {
		DataType temp = back->dataItem;
		QueueNode* cursor = front;
		while (cursor->next != back) {
			cursor = cursor->next;
		}
		back = cursor;
		cursor = cursor->next;
		back->next = NULL;
		free(cursor);
		return temp;
	}
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	int count = 0;
	QueueNode* cursor = front;
	while (cursor != NULL) {
		count++;
		cursor = cursor->next;
	}
	return count;

}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
	QueueNode* p;   // Iterates through the queue

	if (isEmpty())
		cout << "Empty queue" << endl;
	else
	{
		cout << "Front\t";
		for (p = front; p != 0; p = p->next)
		{
			if (p == front)
			{
				cout << '[' << p->dataItem << "] ";
			}
			else
			{
				cout << p->dataItem << " ";
			}
		}
		cout << "\trear" << endl;
	}
}