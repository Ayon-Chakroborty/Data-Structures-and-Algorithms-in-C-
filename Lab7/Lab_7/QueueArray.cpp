
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
    maxSize = maxNumber;
    front = -1;
    back = -1;
    dataItems = new DataType[maxSize];
}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other)
{
    operator=();
}

template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other)
{
    if (this != &other) {
        return *this;
    }
    front = other.front;
    back = other.back;
    maxSize = other.maxSize;
    dataItems = new DataType[other.maxSize];
    for (int i = 0; i < other.maxSize; i++) {
        dataItems[i] = other.dataItems[i];
    }
}

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
    delete[] dataItems;
}


#include "QueueArray.h"
template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
    if (isFull()) {
        throw logic_error("Queue overflow");
    }
    else if (isEmpty()) {
        front = 0;
        back = 0;
        dataItems[back] = newDataItem;
        back++;
    }
    else {
        back = (back + 1) % maxSize;
        dataItems[back] = newDataItem;
    }
}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
    if (isEmpty()) {
        throw logic_error("Queue Underflow");
    }

    else {
        DataType temp = dataItems[front];
        dataItems[front] = NULL;
        front = (front + 1) % maxSize;
        return temp;
    }
}

template <typename DataType>
void QueueArray<DataType>::clear()
{
    front = -1;
    back = -1;
    delete[] dataItems;

}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
    if (front == -1 && back == -1) {
        return true;
    }
    return false;
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
    if (((back + 1) % maxSize) == front) {
        return true;
    }
    return false;
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
    if (isEmpty()) {
        throw logic_error("Queue Underflow");
    }
    else if (isFull()) {
        throw logic_error("Queue Overflow");
    }
    else if (front == 0) {
        int cursor = maxSize;
        while (dataItems[cursor] != NULL) {
            cursor--;
        }
        dataItems[cursor] = newDataItem;
        front = cursor;
    }
    else {
        dataItems[front - 1] = newDataItem;
        front--;
    }


}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
    if (isEmpty()) {
        throw logic_error("Queue Underflow");
    }
    DataType temp = dataItems[back];
    back--;
    return temp;


}

template <typename DataType>
int QueueArray<DataType>::getLength() const
{
    if (isEmpty()) {
        return NULL;
    }
    if (front > back) {
        return ((maxSize - (front + back)));
    }
    if (front < back) {
        return back - front;
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if (front == -1)
        cout << "Empty queue" << endl;
    else
    {
        cout << "Front = " << front << "  Back = " << back << endl;
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        if (back >= front)
            for (j = 0; j < maxSize; j++)
                if ((j >= front) && (j <= back))
                    cout << dataItems[j] << "\t";
                else
                    cout << " \t";
        else
            for (j = 0; j < maxSize; j++)
                if ((j >= front) || (j <= back))
                    cout << dataItems[j] << "\t";
                else
                    cout << " \t";
        cout << endl;
    }
}