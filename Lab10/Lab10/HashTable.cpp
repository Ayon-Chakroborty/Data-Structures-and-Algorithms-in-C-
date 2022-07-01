#include <iostream>
#include "HashTable.h"
//Ayon Chakroborty
//gv5072

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	copyTable(other);
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if (tableSize < other.tableSize)
	{
		delete[] dataTable;
		copyTable[other];
		return;
	}
	else
	{
		for (int i = 0; i < tableSize - 1; i++)
		{
			dataTable[i] = other.dataTable[i];
		}
	}
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{
	dataTable = new BSTree<DataType, KeyType>[source.tableSize];

	for (int i = 0; i < source.tableSize - 1; i++) {
		dataTable[i] = source.dataTable[i];
	}
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	delete[] dataTable;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	unsigned int loc = DataType::hash(newDataItem.getKey()) % tableSize;
	dataTable[loc].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	unsigned int loc = DataType::hash(deleteKey) % tableSize;
	return(dataTable[loc].remove(deleteKey));
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	unsigned int loc = DataType::hash(searchKey) % tableSize;
	return(dataTable[loc].retrieve(searchKey, returnItem));
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for (int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for (int i = 0; i < tableSize - 1; i++) {
		if (dataTable[i].isEmpty() == false) {
			return false;
		}
	}
	return true;
}



template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
}


template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
	for (int i = 0; i < tableSize; ++i) {
		std::cout << i << ": ";
		dataTable[i].writeKeys();
	}
}
