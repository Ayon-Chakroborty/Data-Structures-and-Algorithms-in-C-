//--------------------------------------------------------------------
//
//  Laboratory 12                                            Heap.cpp
//
//  SOLUTION: Array implementation of the Heap ADT
//
//--------------------------------------------------------------------

#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"

//#include <new>

using namespace std;

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)

// Creates an empty heap. Allocates enough memory for maxNumber
// data items.
{
    //initialize constructor with the given input values
    maxSize = maxNumber;
    size = 0;
    //initialize and set new dataItems array with maxSize
    dataItems = new DataType[maxSize];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)

// Copy constructor
{
    //call operator= because they work similarly
    operator=(other);
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator= (const Heap& other)

{
    //perform check if this != other
    if (&other != this) {
        //if maxSize is less than other.maxSize
        if (maxSize < other.maxSize) {
            //clear 
            delete[] dataItems;
            //set dataItems to be initialized with other.maxSize
            dataItems = new DataType[other.maxSize];
        }
        //set other.size to be size
        size = other.size;
        //set other.maxSize to be maxSize
        maxSize = other.maxSize;
        //deep copy and loop through every index of dataItems of other and store it into current dataItems
        for (int i = 0; i < maxSize; i++) {
            dataItems[i] = other.dataItems[i];
        }
    }
    return *this;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::~Heap()

// Frees the memory used by a heap.

{
    //clear dataItems array by calling delete
    delete[] dataItems;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem) throw (logic_error)

// Inserts newDataItem into a heap. This data item is initially
// inserted as the bottom rightmost data item in the heap. It is then
// moved upward until a valid heap is produced.

{
    //create placeholder values
    int temp_size = size;
    int temp2;
    //check if empty, then store newDataItem into the dataItems size
    if (isEmpty()) {
        dataItems[temp_size] = newDataItem;
    }
    //check if full, then throw error message
    if (isFull()) {
        throw logic_error("Error! Cannot enter values : Heap full");
    }
    else {
        //get the median value one less than the array
        temp2 = (temp_size - 1) / 2;
        //loop through the array and check if size is not zero, and call comparator
        while ((temp_size != 0) && comparator(newDataItem.getPriority()),
            dataItems[temp2].getPriority()) {
            //if condition met, store value into dataItems of size
            dataItems[temp_size] = dataItems[temp2];
            //store temp value into size placeHolder value
            temp_size = temp2;
            //store the half value before size into placeHolder
            temp2 = (temp_size - 1) / 2;
        }
        //store newDataItem into dataItems array of size
        dataItems[temp_size] = newDataItem;
    }
    //update size
    size++;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)

// Removes the data item with the highest priority (the root) from a
// heap and returns it. This data item is replaced with the bottom
// rightmost data item, which is moved downward until a valid heap is
// produced.

{
    //if heap is empty, throw error message as we can't remove a value from an empty heap
    if (isEmpty()) {
        throw logic_error("Error! Heap is empty");
    }
    //store the first index of dataItems array into a temp datatype variable
    DataType temp = dataItems[0];
    //remove values
    dataItems[0] = dataItems[--size];
    return temp;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()

// Removes all the data items from a heap.

{
    //to clear set size to be empty
    size = NULL;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty() const

// Returns true if a heap is empty. Otherwise, returns false.

{
    //if size is empty, return true
    if (size == NULL) {
        return true;
    }
    //else return false
    else {
        return false;
    }
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull() const

// Returns true if a heap is full. Otherwise, returns false.

{
    //if size >= maxSize, return true
    if (size >= maxSize) {
        return true;
    }
    //else return false
    else {
        return false;
    }
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showStructure() const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if (size == 0)
        cout << "Empty heap" << endl;
    else
    {
        cout << "size = " << size << endl;       // Output array form
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        for (j = 0; j < size; j++)
            cout << dataItems[j].getPriority() << "\t";
        cout << endl << endl;
        showSubtree(0, 0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showSubtree(int index, int level) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
    int j;   // Loop counter

    if (index < size)
    {
        showSubtree(2 * index + 2, level + 1);        // Output right subtree
        for (j = 0; j < level; j++) {        // Tab over to level
            cout << "\t";
        }
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if (2 * index + 2 < size) {                // Output "connector"
            cout << "<";
        }
        else if (2 * index + 1 < size) {
            cout << "\\";
        }
        cout << endl;
        showSubtree(2 * index + 1, level + 1);        // Output left subtree
    }
}

//--------------------------------------------------------------------
//
//                       Take-home operations
//
//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels() const

// Outputs the data items in a heap in level order, one level per line.
// Only outputs the priority for each data item.

{
    //create temp placeHolder values for level printing output
    int tempLevel = 1;
    int tempPrint = 0;
    //loop through size
    for (int i = 0; i < size; i++) {
        //loop through size and update printer temp value
        for (int j = 0; j < size; tempPrint++) {
            //if placeHolder temp print value equals temp level placeHolder value
            if (tempPrint == tempLevel) {
                std::cout << "\n";
                //update placeHolder values and increase level order by one level per line
                tempPrint = 0;
                tempLevel += 1;
            }
        }
        //print priority values of heap at every index
        std::cout << dataItems[i].getPriority() << " ";
    }
    std::cout << endl;
}


#endif	// #ifndef HEAP_CPP