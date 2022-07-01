// show6.cpp

//--------------------------------------------------------------------

//#include "StackArray.h"
#include "StackLinked.h"

//Al-Taimee Hassan
//gf6417

// template <typename DataType>
// void StackArray<DataType>::showStructure() const

// // Array implementation. Outputs the data items in a stack. If the
// // stack is empty, outputs "Empty stack". This operation is intended
// // for testing and debugging purposes only.

// {
// 	if (isEmpty()) {
// 		cout << "Empty stack." << endl;
// 	}
// 	else {
// 		int j;
// 		cout << "Top = " << top << endl;
// 		for (j = 0; j < maxSize; j++)
// 			cout << j << "\t";
// 		cout << endl;
// 		for (j = 0; j <= top; j++)
// 		{
// 			if (j == top)
// 			{
// 				cout << '[' << dataItems[j] << ']' << "\t"; // Identify top
// 			}
// 			else
// 			{
// 				cout << dataItems[j] << "\t";
// 			}
// 		}
// 		cout << endl;
// 	}
// 	cout << endl;
// }

//--------------------------------------------------------------------

template <typename DataType>
void StackLinked<DataType>::showStructure() const

// Linked list implementation. Outputs the data elements in a stack.
// If the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.

{
	if (isEmpty())
	{
		cout << "Empty stack" << endl;
	}
	else
	{
		cout << "Top\t";
		for (StackNode* temp = top; temp != 0; temp = temp->next) {
			if (temp == top) {
				cout << "[" << temp->dataItem << "]\t";
			}
			else {
				cout << temp->dataItem << "\t";
			}
		}
		cout << "Bottom" << endl;
	}

}




//constructor
template <typename DataType>
StackLinked<DataType>::StackLinked(int maxNumber) {
	// //set maxSize
	// maxSize = maxNumber;
	// //allocate memory to dataItems
	// dataItems = new DataType[maxNumber];
	//top = -1;

	//top == NULL
	top = NULL;
}

//copy constructor
template <typename DataType>
StackLinked<DataType>::StackLinked(const StackLinked& other) {
	// //set maxSize and top as other's
	// top = other.top;
	// maxSize = other.maxSize;
	// //allocate memory to dataItems and copy data from other to it
	// for(int i = 0; i < other.maxSize; i++) {
	//     dataItems = new DataType[other];
	// }

	//use the operator= method for the copy constructor
	//to create reference of other 
	operator=();
}

template <typename DataType>
StackLinked<DataType>::~StackLinked()
{
	//delete all nodes in the stack
	clear();
}

template <typename DataType>
void StackLinked<DataType>::push(const DataType& newDataItem) throw (logic_error) {
	//require stack is not full
	if (isFull() == false) {
		// //increase top
		// top++;
		// //increase newDataItem onto the top of stack
		// dataItems[top] = newDataItem;

		//insert newDataItem onto the top of the stack
		top = new StackNode(newDataItem, top);
	}
	//else throw logic error
	else {
		throw logic_error("Error! Stack is Full!");
	}
}

template <typename DataType>
DataType StackLinked<DataType>::pop() throw (logic_error) {
	//require stack is not empty
	if (!isEmpty()) {
		// //remove the topmost dataitem from a stack and return it
		// DataType poppedDataItem = dataItems[top];
		// //decrease top
		// top--;
		// //return
		// return poppedDataItem;


		//create a pointer to removedItem
		StackNode* removedItem = top;
		top = top->next;
		//remove the topmost dataItem from a stack
		DataType poppedItem = removedItem->dataItem;
		//move the top pointer and update it
		//top = top->next;
		//remove removedItem
		delete removedItem;
		//return the removed data item
		return poppedItem;

	}
	//else throw logic error
	else {
		throw logic_error("Error! Stack is empty!");
	}
}

template <typename DataType>
bool StackLinked<DataType>::isEmpty() const {
	//check to make sure top is not pointing to the NULL, check if its empty return true
	if (top == NULL) {
		return true;
	}
	return false;
}

template <typename DataType>
bool StackLinked<DataType>::isFull() const {
	//stack cannot be full
	return false;
}

template <typename DataType>
void StackLinked<DataType>::clear()
{
	// //iterate through dataitems until reached last value and clear every value
	// int tempLastIndex = maxSize - 1;
	// for(int i = 0; i < tempLastIndex; i++) {
	// 	dataItems[i] = NULL;
	// }
	// //check if top is empty
	// top = -1;



	//clear the stack
	//while loop
	/*while (top != NULL) {
		//move the cursor until top == NULL
		next = top->next;
		//free each node
		free(top);
		//update the top
		top = next;
	}*/
	top = NULL;
}

template <typename DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=(const StackLinked& other)
{
	// //create an other max size
	// int tempOtherMaxSize = other.maxSize;
	// //copy over other's maxSize and set it to dataItems
	// for(int i = 0; i < tempOtherMaxSize; i++) { 
	// 	dataItems = new DataType[tempOtherMaxSize]; 
	// }

	//self-assignment protection
	if (this != &other) {
		return *this;
	}

	//copy first node
	top = new StackNode(other.top->dataItem, 0);
	StackNode* otherTemp = other.top->next;

	//copy rest of nodes
	//two auxiliary parameters
	StackNode* thisTemp = 0, * thisPrevious = top;
	//while loop
	while (otherTemp != NULL) {
		thisTemp = new StackNode(otherTemp->dataItem, 0);
	}
}