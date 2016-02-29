#ifndef SPLAY_NODE_H
#define SPLAY_NODE_H
#include <memory>

class Node
{
public:
//    typedef std::shared_ptr<Node> NodePtr;
//    typedef std::weak_ptr<Node> NodeWeakPtr;
    typedef Node * NodePtr;
    typedef Node * NodeWeakPtr;
    Node(long long value);
    Node(Node &&);
    ~Node();
    static NodePtr makeOneNodeCopy(const NodePtr &);
    static NodePtr makeFullCopy(const NodePtr &);
    static void getSegment(NodePtr, int, int, NodePtr &, NodePtr &, NodePtr &);
    static void addOnSegment(NodePtr &x, int lPos, int rPos, long long add);
    static long long getSumOnSegment(NodePtr &x, int lPos, int rPos);
    static void nextPermutationOnSegment(NodePtr &x, int lPos, int rPos);
    static void nextPermutation(NodePtr &x);
    static void setValue(NodePtr &, int pos, long long val);
    static void insertValue(NodePtr &, int newPos, long long val);
    static void printLeaves(NodePtr root, bool reverse=0);
    static void printAsTree(NodePtr root, int depth=0, bool reverse=0);
    static void printAsTreeExtended(NodePtr root, int depth=0, bool reverse=0);
    static bool exist(const NodePtr);
    static void fullPush(NodePtr x);
//    static bool exist(const NodeWeakPtr);
    static void checkIntegrity(NodePtr root, NodePtr parent=nullptr);
    static NodePtr splay(NodePtr);
    static NodePtr getKth(NodePtr, int);
    static std::pair<NodePtr, NodePtr> split(NodePtr root, int pos);
    static NodePtr merge(NodePtr, NodePtr);
    static int getSubTreeSize(NodePtr);
protected:
    // must be sorted in descending order!!!
    static NodePtr findFirstGreater(NodePtr, long long);
    static void reverse(NodePtr &);
    static void swapJustRoots(NodePtr &x, NodePtr &y);
    static NodePtr rotate(NodePtr &x, NodePtr p);
    static bool isLeftSon(const NodePtr x, const NodePtr p);
    static bool isRightSon(const NodePtr x, const NodePtr p);
    static void makeNewChild(NodePtr x, NodePtr p, NodePtr gp);
    static void makeRightChild(NodePtr x, NodePtr child);
    static void makeLeftChild(NodePtr x, NodePtr child);
    static NodePtr rotateRight(NodePtr &x, NodePtr p);
    static NodePtr rotateLeft(NodePtr &x, NodePtr p);
    static NodePtr zigZag(NodePtr &x, NodePtr p, NodePtr gp);
    static NodePtr zigZig(NodePtr &x, NodePtr p, NodePtr gp);
    static void push(NodePtr);
    static void reCalc(NodePtr);
    static void reCalcSortedPrefix(NodePtr);
    static void reCalcSortedSuffix(NodePtr);
    static long long getSum(NodePtr);
    static int getSortedSuffix(NodePtr);
    static int getSortedPrefix(NodePtr);
    NodePtr left_,
            right_;
    NodePtr parent_;
    int subTreeSize_, sortedSuffix_, sortedPrefix_;
    long long value_, sum_, add_, first_, last_;
    bool needReverse_;
private:
    Node(const Node &) = default;
};

#endif
