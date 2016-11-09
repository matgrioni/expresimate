#include <iostream>
#include "tree.h"

int main()
{
    BinaryTree<int> right_tree;
    right_tree.node(2);
    BinaryTree<int> left_tree;
    left_tree.node(3);
    BinaryTree<int> tree(1, &left_tree, &right_tree);
    tree.node(1);

    std::cout << tree.node() << tree.right().node() << tree.left().node() ;

    return 0;
}
