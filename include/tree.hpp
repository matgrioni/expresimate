#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

/*********************************************************************
*
* A BinaryTree of non-NULL nodes. Uses generic types and therefore can
* hold values of any type.
*
*********************************************************************/

template <class T>
class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(T node, BinaryTree<T> *left, BinaryTree<T> *right);
        ~BinaryTree();

        void node(T node);
        T node();

        void left(BinaryTree<T> *tree);
        BinaryTree<T>* left();

        void right(BinaryTree<T> *tree);
        BinaryTree<T>* right();

        int height();

    private:
        T node_;
        BinaryTree<T> *parent_;
        BinaryTree<T> *left_;
        BinaryTree<T> *right_;
};

template <class T>
BinaryTree<T>::BinaryTree()
{
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree(T node, BinaryTree<T>* left, BinaryTree<T>* right)
{
    node_ = node;
    left_ = left;
    right_ = right;

    parent_ = nullptr;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    if (left_)
        delete left_;

    if (right_)
        delete right_;
}

template <class T>
void BinaryTree<T>::node(T node)
{
    node_ = node;
}

template <class T>
T BinaryTree<T>::node()
{
    return node_;
}

template <class T>
void BinaryTree<T>::left(BinaryTree<T> *tree)
{
    tree->parent_ = this;
    left_ = tree;
}

template <class T>
BinaryTree<T>* BinaryTree<T>::left()
{
    return left_;
}

template <class T>
void BinaryTree<T>::right(BinaryTree<T> *tree)
{
    tree->parent_ = this;
    right_ = tree;
}

template <class T>
BinaryTree<T>* BinaryTree<T>::right()
{
    return right_;
}

template <class T>
int BinaryTree<T>::height()
{
    int h = 0;

    if (left_)
        h += 1 + left_->height();

    if (right_)
        h += 1 + right_->height();

    return h;
}

#endif
