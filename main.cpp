#include <iostream>
#include <algorithm>
#include "splay_next_permutation.h"


void nanoTest()
{
    Node::NodePtr Tree(nullptr);
    for (int i = 0; i < 10; ++i) {
        Node::insertValue(Tree, i, i);
        Node::printAsTree(Tree);
    }
    Node::printLeaves(Tree);
    std::cout << std::endl;
    Node::NodePtr L, C, R;
    Node::getSegment(Tree, 1, 4, L, C, R);
    Node::printLeaves(L);
    std::cout << std::endl;
    Node::printLeaves(C);
    std::cout << std::endl;
    for (int i = 0; i < 24; ++i) {
        Node::nextPermutation(C);
        Node::printLeaves(C);
        Node::checkIntegrity(C);
        std::cout << std::endl;
    }
    Node::printLeaves(R);
    std::cout << std::endl;
    Tree = Node::merge(Node::merge(L, C), R);
    Node::printLeaves(Tree);
    std::cout << std::endl;
    delete L;
    delete C;
    delete R;
    delete Tree;
}

void test(int n)
{
    Node::NodePtr Tree(nullptr);
    for (int i = 0; i < n; ++i) {
        Node::insertValue(Tree, i, i + 1);
        Node::printAsTree(Tree);
    }
    Node::printLeaves(Tree);
    std::cout << std::endl;
    for (int i = 0; i < 24; ++i) {
        Node::nextPermutation(Tree);
        Node::printLeaves(Tree);
        Node::checkIntegrity(Tree);
        std::cout << std::endl;
    }
}

void testP(const std::vector <long long> arr, int k=10)
{
    Node::NodePtr Tree(nullptr);
    for (int i = 0; i < (int)arr.size(); ++i) {
        Node::insertValue(Tree, i, arr[i]);
        Node::printAsTree(Tree);
    }
    Node::printLeaves(Tree);
    std::cout << std::endl;
    //Node::printAsTree(Tree);
    //Node::printAsTreeExtended(Tree);
    for (int i = 0; i < k; ++i) {
        Node::nextPermutation(Tree);
        Node::printLeaves(Tree);
        Node::checkIntegrity(Tree);
        std::cout << std::endl;
        //Node::printAsTree(Tree);
        //Node::printAsTreeExtended(Tree);
    }
    delete Tree;
}

int main()
{
    //testP({3, 2, 1, 4}, 24);
    testP({0, 1, 23, 423, 1, 20, 1, 2}, 250);
    return 0;
}
