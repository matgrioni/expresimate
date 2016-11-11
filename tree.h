#ifndef TREE_H
#define TREE_H

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

        void node(T node);
        T node();

        void left(BinaryTree<T> *tree);
        BinaryTree<T> left();

        void right(BinaryTree<T> *tree);
        BinaryTree<T> right();

        int size();

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
BinaryTree<T> BinaryTree<T>::left()
{
    return *left_;
}

template <class T>
void BinaryTree<T>::right(BinaryTree<T> *tree)
{
    tree->parent_ = this;
    right_ = tree;
}

template <class T>
BinaryTree<T> BinaryTree<T>::right()
{
    return *right_;
}

template <class T>
int BinaryTree<T>::size()
{
    int s = 0;

    if (node != nullptr)
        s += 1;

    if (left != nullptr)
        left_->size();

    if (right != nullptr)
        right_->size();

    return s;
}

#endif
