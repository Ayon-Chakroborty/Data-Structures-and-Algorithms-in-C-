#include "ExpressionTree.h"

//Al-Taimee Hassan
//gf6417

//--------------------------------------------------------------------

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char nodeDataItem,
    ExprTreeNode* leftPtr,
    ExprTreeNode* rightPtr)

{
    //initialize data members
    dataItem = nodeDataItem;
    left = leftPtr;
    right = rightPtr;
}


template <typename DataType>
ExprTree<DataType>::ExprTree()

{
    //set root to 0
    root = 0;
}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)

{
    //given copy constructor
    root = source.root;
    copyHelper(root);
}


template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)

{
    //given operator=, perform check if they are not the same, call copyHelper
    if (&source != this) {
        copyHelper(source.root);
    }
    return *this;

}

template <typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode*& p)

{
    //given
    if (p != 0) {
        p = new ExprTreeNode(p->dataItem, p->left, p->right);
        copyHelper(p->left);
        copyHelper(p->right);
    }

}

template <typename DataType>
ExprTree<DataType>:: ~ExprTree()

{
    //destructor and clear works similarly
    clear();
}


template <typename DataType>
void ExprTree<DataType>::build()

{
    //given
    clear();
    buildHelper(root);
}

template <>
void ExprTree<float>::buildHelper(ExprTreeNode*& p)

{
    //given
    char ch;
    std::cin >> ch;
    p = new ExprTreeNode(ch, 0, 0);
    if (!isdigit(ch)) {
        //call recursively to build subtrees
        buildHelper(p->left);
        buildHelper(p->right);
    }
}

template <>
void ExprTree<bool>::buildHelper(ExprTreeNode*& p)

{
    //given
    char ch;
    std::cin >> ch;
    p = new ExprTreeNode(ch, 0, 0);
    if (!isdigit(ch)) {
        //call recursively to build subtrees
        buildHelper(p->left);
        buildHelper(p->right);
    }
}


template <typename DataType>
void ExprTree<DataType>::expression() const

{
    //given
    exprHelper(root);

}

template <typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode* p) const

{
    if (p != 0) {
        if (!isdigit(p->dataItem)) {
            std::cout << "( " << exprHelper(p->left);
            cout << p->dataItem;
            cout << exprHelper(p->right);
        }
        if (!isdigit(p->dataItem)) {
            std::cout << ")";
        }
    }
}


template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)

{
    //given
    return evalHelper(root);

}


template <>
float ExprTree<float>::evalHelper(ExprTreeNode* p) const

{
    //define variables for intermediate and finals results
    float finalResult, leftEval, rightEval;
    if (isdigit(p->dataItem)) {
        finalResult = p->dataItem - '0';
    }
    else {
        //evaluate left and right subtrees and combine results
        leftEval = evalHelper(p->left);
        rightEval = evalHelper(p->right);
        //check input and combine result based on input operator
        if (p->dataItem == '+') {
            finalResult = leftEval + rightEval;
        }
        if (p->dataItem == '*') {
            finalResult = leftEval * rightEval;
        }
        if (p->dataItem == '/') {
            finalResult = leftEval / rightEval;
        }
        if (p->dataItem == '-') {
            finalResult = leftEval - rightEval;
        }

        return finalResult;
    }
    return finalResult;
}


template <>
bool ExprTree<bool>::evalHelper(ExprTreeNode* p) const

{
    //define variables for intermediate and finals results
    bool finalResult, leftEval, rightEval;
    if (isdigit(p->dataItem)) {
        finalResult = p->dataItem - '0';
    }
    else {
        //evaluate left and right subtrees and combine results
        leftEval = evalHelper(p->left);
        rightEval = evalHelper(p->right);
        //check input and combine result based on input operator
        if (p->dataItem == '+') {
            finalResult = leftEval + rightEval;
        }
        if (p->dataItem == '*') {
            finalResult = leftEval * rightEval;
        }
        if (p->dataItem == '/') {
            finalResult = leftEval / rightEval;
        }
        if (p->dataItem == '-') {
            finalResult = leftEval - rightEval;
        }

        return finalResult;
    }
    return finalResult;
}

template <typename DataType>
void ExprTree<DataType>::clear()

{
    //given
    clearHelper(root);
    root = 0;

}


template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode* p)


{
    //if p is not empty
    if (p != 0) {
        //clear left and right subtrees
        clearHelper(p->left);
        clearHelper(p->right);
        //free memory
        delete p;
    }

}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const {
    ExprTreeNode* p = root;
    if (p == NULL) {
        return true;
    }
    else {
        return false;
    }
}

template <typename DataType>
void ExprTree<DataType>::showStructure() const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showHelper(root, 1);
        cout << endl;
    }
}


template <typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode* p, int level) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
    int j;   // Loop counter

    if (p != 0)
    {
        showHelper(p->right, level + 1);        // Output right subtree
        for (j = 0; j < level; j++)   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ((p->left != 0) &&          // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "/";
        cout << endl;
        showHelper(p->left, level + 1);         // Output left subtree
    }
}


template <typename DataType>
void ExprTree<DataType>::commute()

{
    //given
    commuteHelper(root);

}


template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p)

{
    //define temp store pointer during swap
    if (p != 0) {
        //commute left and right subtree
        commuteHelper(p->left);
        commuteHelper(p->right);
        //switch left leaf and right leaf
        ExprTreeNode* switchLeft;
        switchLeft = p->left;
        ExprTreeNode* switchRight;
        switchRight = p->right;
        p->left = switchRight;
        switchRight = switchLeft;
    }

}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree<DataType>& source) const

{
    return isEquivalentHelper(root, source.root);

}


template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x,
    const ExprTreeNode* y) const

{
    //create a placeHolder bool value
    bool checkIfEquivalent = false;
    do {
        if (x->dataItem != y->dataItem) {
            //if both are empty, return true
            if ((x->left == NULL && y->left == NULL) && (x->right == NULL && y->right == NULL)) {
                checkIfEquivalent = true;
            }
            //if only one is empty, return false
            if ((x->left == NULL && y->left == NULL) || (x->right == NULL && y->right == NULL)) {
                checkIfEquivalent = false;
            }
            //compare left subtree and right subtree
            if (isEquivalentHelper(x->left, y->left) && isEquivalentHelper(x->right, y->right)) {
                checkIfEquivalent = true;
            }

        }
    } while (!checkIfEquivalent);
    return checkIfEquivalent;
}