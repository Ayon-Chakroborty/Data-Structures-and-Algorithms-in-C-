
#include "ListArray.h"
template < typename DataType >
List<DataType>::List(int maxNumber) :maxSize(maxNumber), size(0), cursor(-1)
{
	dataItems = new DataType[maxSize];
}

template < typename DataType >
List<DataType>::List(const List& source)
{
	maxSize = source.maxSize;
	size = source.size;
	cursor = source.cursor;
	dataItems = new DataType[maxSize];
	for (int i = 0; i < size; i++) {
		dataItems[i] = source.dataItems[i];
	}
}

template < typename DataType >
List<DataType>& List<DataType>::operator= (const List& source)
{
	if (this != &source) {
		if (source.maxSize > maxSize) {
			delete[] dataItems;
			maxSize = source.maxSize;
			dataItems = new DataType[maxSize];

		}
		size = source.size;
		cursor = source.cursor;

		for (int i = 0; i < size; i++) {
			dataItems[i] = source.dataItems[i];
		}
	}


	return *this;
}

template < typename DataType >
List<DataType>::~List()
{
	delete[] dataItems;
}

template < typename DataType >
void List<DataType>::insert(const DataType& newDataItem)
throw (logic_error)
{
	//check list array is full or not
	if (size == maxSize) {
		throw logic_error("List is full");
	}
	//cursor == 3, cursor++, cursor == 4

	for (int i = size; i > cursor + 1; i--) {
		dataItems[i] = dataItems[i - 1];
	}
	size++;
	cursor++;
	//insert new element
	if (isEmpty())
	{
		dataItems[0] = newDataItem;
	}
	else
		dataItems[cursor] = newDataItem;

}

template < typename DataType >
void List<DataType>::remove() throw (logic_error)
{
	//check the list is empty or not
	if (isEmpty()) {
		throw logic_error("List is empty");
	}
	//
	for (int i = cursor; i < size - 1; i++) {
		//first shifting is from cursor + 1 to cursor
		dataItems[i] = dataItems[i + 1];
		//last shifting is from size - 1 to size - 2

	}
	//update size and cursor
	size--;
	cursor--;
}

template < typename DataType >
void List<DataType>::replace(const DataType& newDataItem)
throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("List is empty");
	}
	dataItems[cursor] = newDataItem;
}

template < typename DataType >
void List<DataType>::clear()
{
	size = 0;
	cursor = -1;

}

template < typename DataType >
bool List<DataType>::isEmpty() const
{
	if (size == 0) {
		return true;
	}
	return false;
}

template < typename DataType >
bool List<DataType>::isFull() const
{
	if (size == maxSize) {
		return true;
	}
	return false;
}

template < typename DataType >
void List<DataType>::gotoBeginning()
throw (logic_error)
{
	if (size == 0) {
		throw logic_error("List is empty");
	}
	cursor = 0;
}

template < typename DataType >
void List<DataType>::gotoEnd()
throw (logic_error)
{
	if (size == 0) {
		throw logic_error("List is empty");
	}
	cursor = size - 1;
}

template < typename DataType >
bool List<DataType>::gotoNext()
throw (logic_error)
{
	if (size == 0) {
		throw logic_error("List is empty");
	}
	if (cursor < size) {
		cursor = cursor + 1;
		return true;
	}
	return false;
}

template < typename DataType >
bool List<DataType>::gotoPrior()
throw (logic_error)
{
	if (size == 0) {
		throw logic_error("List is empty");
	}
	if (cursor > 0) {
		cursor = cursor - 1;
		return true;
	}
	return false;
}

template < typename DataType >
DataType List<DataType>::getCursor() const
throw (logic_error)
{
	if (size == 0) {
		throw logic_error("List is empty");
	}
	DataType t;
	t = dataItems[cursor];
	return t;
}

#include "show3.cpp"

template < typename DataType >
void List<DataType>::moveToNth(int n)
throw (logic_error)
{
	if (size < n + 1) {
		throw logic_error("List is empty");
	}
	DataType obj = getCursor();
	remove();
	cursor = n - 1;
	insert(obj);

}

template < typename DataType >
bool List<DataType>::find(const DataType& searchDataItem)
throw (logic_error)
{
	cursor = 0;
	if (this->isEmpty()) {
		throw logic_error("List is empty");
	}
	for (int i = cursor; i < size; i++) {
		if (this->dataItems[i] == searchDataItem) {
			cursor = i;
			return true;
		}
	}
	return false;
}