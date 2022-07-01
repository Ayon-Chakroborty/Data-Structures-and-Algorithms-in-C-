
#include "BSTree.h"
//Ayon Chakroborty
//gv5072


template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{
	root = NULL;
	copyTree(other);
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= (const BSTree<DataType, KeyType>& other)
{
	copyTree(other);
	if (this != &other ) {
		clear();
		copyTree(other);
		return *this;
	}
	else {
		return *this;
	}
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyTree(const BSTree<DataType, KeyType>& otherTree) {
	copyTreeHelper(root, otherTree.root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode*& p, const BSTreeNode* otherPtr) {
	if (p != 0) {
		p = new BSTreeNode(otherPtr->dataItem, 0, 0);
		copyTreeHelper(p->left, otherPtr->left);
		copyTreeHelper(p->right, otherPtr->right);
	}
}
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree()
{
	clearHelper(root);
	root = NULL;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
	insertHelper(root, newDataItem);
}

template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode*& p, const DataType& newDataItem) {
	if (p == 0) {
		p = new BSTreeNode(newDataItem, 0, 0);
	}
	else if (newDataItem.getKey() < p->dataItem.getKey()) {
		insertHelper(p->left, newDataItem);
	}
	else if (newDataItem.getKey() > p->dataItem.getKey()) {
		insertHelper(p->right, newDataItem);
	}
	else {
		p->dataItem = newDataItem;
	}
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{

	return retrieveHelper(root, searchKey, searchDataItem);
}

template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* p, const KeyType& searchKey, DataType& searchDataItem)const {
	bool result; //result returned

	if (p == 0) { //Fell off the tree while searching. Item is not in tree
		return false;

	}
	else if (searchKey < p->dataItem.getKey()) { //Key is smaller than current node. search to left.
		retrieveHelper(p->left, searchKey, searchDataItem);

	}
	else if (searchKey > p->dataItem.getKey()) {//Key is larger than current node. Search to right
		retrieveHelper(p->right, searchKey, searchDataItem);

	}
	else {//Found the desired Item
		result = true;
	}

	return result;


}
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	return removeHelper(root, deleteKey);
}

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& p, const KeyType& deleteKey) {
	BSTreeNode* delPtr; //Pointer to node to delete
	bool result; // result returned
	
	if (p == 0) { //search failed
		result = false;
	}
	else if (deleteKey < p->dataItem.getKey()) {
		removeHelper(p->left, deleteKey); //search left
	}
	else if (deleteKey > p->dataItem.getKey()) {
		removeHelper(p->right, deleteKey); //search right
	}
	else {
		//Found
		delPtr = p;

		if (p->left == 0) {
			//No left Child, link right child, deletePtr
			p = p->right;
			delete delPtr;

		}
		else if (p->right == 0) {
			//No right child, link left child, delete delPtr
			p = p->left;
			delete delPtr;
		}
		else {
			//Node has both children: removing is more complex
			//Find NOde with largest Key smaller than p's key
			//That is, the rightmost descendant of the node's left child

			BSTreeNode* temp = p->left;

			while (temp->right)
			{
				temp = temp->right;
			}

			//Copy node data to p;
			p->dataItem = temp->dataItem;

			//And remove the node whose data wsa copied to p
			removeHelper(p->left, temp->dataItem.getKey());

		}
		result = true;
	}
	return result;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys() const
{
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* p) const {
	if (p != NULL) {

		writeKeysHelper(p->left);
		std::cout << p->dataItem.getKey() << " ";
		writeKeysHelper(p->right);
	}
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear()
{
	clearHelper(root);
	root = NULL;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode* p) {
	if (p != 0) {
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;

	}
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
{
	if (root == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight() const
{
	getHeightHelper(root);
	return -1;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* p) const {
	int x, y;
	if (p == NULL) {
		return 0;
	}
	x = getCountHelper(p->right);
	y = getCountHelper(p->left);
	if (x > y) {
		return x + 1;
	}
	if (y > x) {
		return y + 1;
	}
		
	
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount() const
{
	getCountHelper(root);
	return -1;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* p) const {
	int x, y;
	if (p != NULL) {
		x = getCountHelper(p->right);
		y = getCountHelper(p->left);
		return x + y + 1;
	}
	return 0;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan(const KeyType& searchKey) const {
	writeLTHelper(root, searchKey);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLTHelper(BSTreeNode* p, const KeyType& searchKey)const {
	if (p != NULL) {
		if (p->left < searchKey)
			writeLTHelper(p->left, searchKey);
		std::cout << p->dataItem.getKey() << " ";
		if (p->right < searchKey)
			writeLTHelper(p->right, searchKey);
	}
}
//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showStructure() const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode* p,
	int level) const

	// Recursive helper for showStructure. 
	// Outputs the subtree whose root node is pointed to by p. 
	// Parameter level is the level of this node within the tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}