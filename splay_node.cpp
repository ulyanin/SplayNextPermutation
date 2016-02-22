#include "splay.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <climits>

Node::Node(long long int value)
    : left_(nullptr)
    , right_(nullptr)
    , parent_(nullptr)
    , subTreeSize_(1)
    , sortedSuffix_(1)
    , sortedPrefix_(1)
    , value_(value)
    , sum_(0)
    , add_(0)
    , first_(value)
    , last_(value)
    , needReverse_(false)
{ }

Node::~Node()
{
    delete left_;
    delete right_;
    if (exist(parent_)) {
        if (parent_->left_ == this) {
            parent_->left_ = nullptr;
        }
        if (parent_->right_ == this) {
            parent_->right_ = nullptr;
        }
    }
}

Node::Node(Node &&other)
    : left_(other.left_)
    , right_(other.right_)
    , parent_(other.parent_)
    , subTreeSize_(other.subTreeSize_)
    , sortedSuffix_(other.sortedSuffix_)
    , sortedPrefix_(other.sortedPrefix_)
    , value_(other.value_)
    , sum_(other.sum_)
    , add_(other.add_)
    , first_(other.first_)
    , last_(other.last_)
    , needReverse_(other.needReverse_)
{
    other.left_ = other.right_ = nullptr;
}

Node::NodePtr Node::makeOneNodeCopy(const NodePtr &other)
{
    return (exist(other) ? new Node(*other) : nullptr);
}

Node::NodePtr Node::makeFullCopy(const NodePtr &other)
{
    if (!exist(other))
        return nullptr;
    Node * res = makeOneNodeCopy(other);
    res->left_ = makeFullCopy(other->left_);
    res->right_ = makeFullCopy(other->right_);
    return res;
}

bool Node::exist(NodePtr x)
{
    return x != nullptr;
}

Node::NodePtr Node::rotate(NodePtr &x, NodePtr p)
{
    if (!exist(p))
        return x;
    if (isLeftSon(x, p)) {
        return rotateRight(x, p);
    } else {
        return rotateLeft(x, p);
    }
}

bool Node::isLeftSon(const NodePtr x, const NodePtr p)
{
    return exist(p) && (p->left_ == x);
}

bool Node::isRightSon(const NodePtr x, const NodePtr p)
{
    return exist(p) && (p->right_ == x);
}

void Node::makeNewChild(NodePtr x, NodePtr p, NodePtr gp)
{
    if (exist(x)) {
        x->parent_ = gp;
    }
    if (exist(gp)) {
        if (gp->right_ == p) {
            gp->right_ = x;
        } else {
            gp->left_ = x;
        }
    }
}

void Node::makeRightChild(NodePtr x, NodePtr child)
{
    if (exist(x)) {
        x->right_ = child;
    }
    if (exist(child)) {
        child->parent_ = x;
    }
}

void Node::makeLeftChild(NodePtr x, NodePtr child)
{
    if (exist(x)) {
        x->left_ = child;
    }
    if (exist(child)) {
        child->parent_ = x;
    }
}

Node::NodePtr Node::rotateRight(NodePtr &x, NodePtr p)
{
    if (!exist(p))
        return x;
    makeNewChild(x, p, p->parent_);
    //p->left_= x->right_;
    makeLeftChild(p, x->right_);
    //x->right_ = p;
    //p->parent_ = x;
    makeRightChild(x, p);
    reCalc(p);
    reCalc(x);
    reCalc(x->parent_);
    return x;
}

Node::NodePtr Node::rotateLeft(NodePtr &x, NodePtr p)
{
    if (!exist(p))
        return x;
    makeNewChild(x, p, p->parent_);
    //p->right_ = x->left_;
    makeRightChild(p, x->left_);
    //p->parent_ = x;
    //x->left_ = p;
    makeLeftChild(x, p);
    reCalc(p);
    reCalc(x);
    reCalc(x->parent_);
    return x;
}

Node::NodePtr Node::zigZig(NodePtr &x, NodePtr p, NodePtr gp)
{
    if (!exist(gp) || !exist(p))
        return x;
    rotate(p, gp);
    rotate(x, p);
    return x;
}

Node::NodePtr Node::zigZag(NodePtr &x, NodePtr p, NodePtr gp)
{
    if (!exist(gp) || !exist(p))
        return x;
    rotate(x, p);
    rotate(x, gp);
    return x;
}


void Node::push(NodePtr x)
{
    if (!exist(x))
        return;
    if (x->right_) {
        if (x->needReverse_) {
            x->right_->needReverse_ ^= 1;
        }
        x->right_->add_ += x->add_;
    }
    if (x->left_) {
        if (x->needReverse_) {
            x->left_->needReverse_ ^= 1;
        }
        x->left_->add_ += x->add_;
    }
    if (x->needReverse_) {
        std::swap(x->sortedSuffix_, x->sortedPrefix_);
        std::swap(x->first_, x->last_);
        std::swap(x->left_, x->right_);
    }
    x->first_ += x->add_;
    x->last_ += x->add_;
    x->value_ += x->add_;
    x->sum_ += x->add_;
    x->add_ = 0;
    x->needReverse_ = false;
}

long long Node::getSum(NodePtr v)
{
    return exist(v) ? (v->sum_ + v->add_) : 0;
}

int Node::getSortedPrefix(NodePtr x)
{
    return exist(x) ? x->sortedPrefix_ : 0;
}

int Node::getSortedSuffix(NodePtr x)
{
    return exist(x) ? x->sortedSuffix_ : 0;
}

void Node::reCalcSortedPrefix(NodePtr x)
{
    x->sortedPrefix_ = 0; // if left does not exist
    if (x->left_) {
        x->sortedPrefix_ = x->left_->sortedPrefix_;
    }
    if (!exist(x->left_) ||
                (getSortedPrefix(x->left_) == getSubTreeSize(x->left_) &&
                x->left_->last_ <= x->value_)) {
        // left tree does not exist or sorted and (L) <= x;
        x->sortedPrefix_++;
        if (x->right_ && x->value_ <= x->right_->first_) {
            // prefix right tree is sorted and (L) <= x <= prefix(R)
            x->sortedPrefix_ += x->right_->sortedPrefix_;
        }
    }
}

void Node::reCalcSortedSuffix(NodePtr x)
{
    x->sortedSuffix_ = 0;
    if (x->right_) {
        // so right tree is exist
        x->sortedSuffix_ = x->right_->sortedSuffix_;
    }
    if (!exist(x->right_) ||
                (getSortedSuffix(x->right_) == getSubTreeSize(x->right_) &&
                x->value_ >= x->right_->first_)) {
        // right tree does not exist or sorted in descending order and x >= (R);
        x->sortedSuffix_++;
        if (x->left_ && x->left_->last_ >= x->value_) {
            // suffix left tree is sorted and suffix(L) >= x >= (R)
            x->sortedSuffix_ += x->left_->sortedSuffix_;
        }
    }
}

int Node::getSubTreeSize(NodePtr x)
{
    return exist(x) ? x->subTreeSize_ : 0;
}

void Node::reCalc(NodePtr x)
{
    if (!exist(x))
        return;
    x->subTreeSize_ = getSubTreeSize(x->left_) + getSubTreeSize(x->right_) + 1;
    x->sum_ = getSum(x->left_) + getSum(x->right_) + x->value_;
    x->first_ = x->value_;
    x->last_ = x->value_;
    reCalcSortedPrefix(x);
    reCalcSortedSuffix(x);
    if (x->left_) {
        x->first_ = x->left_->first_;
    }
    if (x->right_) {
        x->last_ = x->right_->last_;
    }
}

Node::NodePtr Node::getKth(NodePtr x, int pos)
{
    push(x);
    if (pos < 0 || pos >= getSubTreeSize(x))
        return nullptr;
    int cnt = getSubTreeSize(x->left_);
    if (pos == cnt) {
        return x;
    } else if (pos < cnt) {
        return getKth(x->left_, pos);
    } else {
        return getKth(x->right_, pos - cnt - 1);
    }
}

Node::NodePtr Node::splay(NodePtr x)
{
    NodePtr p = x->parent_;
    if (!exist(p))
        return x;
    NodePtr gp = p->parent_;
    if (!exist(gp)) {
        return rotate(x, p);
    }
    if (isLeftSon(x, p) ^ isLeftSon(p, gp)) {
        zigZag(x, p, gp);
    } else {
        zigZig(x, p, gp);
    }
    return splay(x);
}

std::pair<Node::NodePtr, Node::NodePtr> Node::split(NodePtr root, int pos)
{
    if (!exist(root)) {
        return std::make_pair(nullptr, nullptr);
    }
    if (pos < 0) {
        return std::make_pair(nullptr, root);
    }
    if (pos >= root->subTreeSize_) {
        return std::make_pair(root, nullptr);
    }
    root = splay(getKth(root, pos));
    std::pair<NodePtr, NodePtr> p(root->left_, root);
    root->left_ = nullptr;
    if (p.first) {
        p.first->parent_ = nullptr;
    }
    reCalc(p.second);
    return p;
}


Node::NodePtr Node::merge(NodePtr L, NodePtr R)
{
    if (L == nullptr)
        return R;
    NodePtr newRoot = splay(getKth(L, getSubTreeSize(L) - 1));
    if (exist(newRoot->right_))
        throw std::runtime_error("wrong splay newRoot element");
    push(R);
    newRoot->right_ = R;
    if (exist(R)) {
        R->parent_ = newRoot;
    }
    reCalc(newRoot);
    return newRoot;
}

void Node::getSegment(NodePtr x, int lPos, int rPos, NodePtr &L, NodePtr &C, NodePtr &R)
{
    auto pairTR = split(x, rPos + 1);
    auto pairLC = split(pairTR.first, lPos);
    L = pairLC.first;
    C = pairLC.second;
    R = pairTR.second;
}

void Node::addOnSegment(NodePtr &x, int lPos, int rPos, long long add)
{
    NodePtr L, C, R;
    getSegment(x, lPos, rPos, L, C, R);
    if (exist(C)) {
        C->add_ += add;
        //push(C);
    }
    x = merge(L, merge(C, R));
}

void Node::reverse(NodePtr &x)
{
    x->needReverse_ ^= 1;
}

void Node::swapJustRoots(NodePtr &x, NodePtr &y)
{
    if (!exist(x) && !exist(y))
        throw std::runtime_error("one of roots to swap does not exist");
    push(x);
    push(y);
    std::swap(x->value_, y->value_);
    reCalc(x);
    reCalc(y);
}

void Node::nextPermutation(NodePtr &x)
{
    if (x == nullptr)
        return;
    push(x);
    if (x->sortedSuffix_ == x->subTreeSize_) {
        reverse(x);
        return;
    }
    auto p = split(x, getSubTreeSize(x) - x->sortedSuffix_);
    NodePtr last = getKth(p.first, getSubTreeSize(p.first) - 1);
    p.first = splay(last);
    p.second = splay(findFirstGreater(p.second, p.first->value_));
    swapJustRoots(p.first, p.second);
    reverse(p.second);
    x = merge(p.first, p.second);
}

void Node::nextPermutationOnSegment(NodePtr &x, int lPos, int rPos)
{
    NodePtr L, C, R;
    getSegment(x, lPos, rPos, L, C, R);
    nextPermutation(C);
    x = merge(merge(L, C), R);
}

Node::NodePtr Node::findFirstGreater(NodePtr x, long long key)
{
    if (x->sortedSuffix_ != x->subTreeSize_)
        throw std::runtime_error("trying to search in unsorted tree");
    /*if (!exist(x))
        throw nullptr;
    if (x->value_ <= key) {
        if (exist(x->left_))
            return findFirstGreater(x->left_, key);
        return x;
    } else {
        if (exist(x->right_))
            return findFirstGreater(x->right_, key);
        return x;
    }*/
    NodePtr res(nullptr);
    while (exist(x)) {
        push(x);
        if (x->value_ > key) {
            res = x;
            x = x->right_;
        } else {
            x = x->left_;
        }
    }
    return res;
}

void Node::setValue(NodePtr &x, int pos, long long val)
{
    if (pos < 0 || pos >= getSubTreeSize(x))
        throw std::runtime_error("bad index in set value");
    NodePtr L, C, R;
    getSegment(x, pos, pos, L, C, R);
    if (!exist(C))
        throw std::runtime_error("wrong index while setting the value");
    push(C);
    C->value_ = val;
    reCalc(C);
    x = merge(L, merge(C, R));
}

void Node::insertValue(NodePtr &x, int newPos, long long val)
{
    if (newPos < 0 || newPos > getSubTreeSize(x))
        throw std::runtime_error("bad index in insert value");
    auto p = split(x, newPos);
    NodePtr newNode = new Node(val);
    merge(p.first, merge(newNode, p.second));
    x = splay(newNode);
}


void Node::printAsTree(NodePtr root, int depth, bool reverse)
{
    if (!exist(root))
        return;
    if (depth == 0)
        std::cout << "_____________" << std::endl;
    reverse ^= root->needReverse_;
    if (reverse) {
        std::swap(root->left_, root->right_);
    }
    printAsTree(root->right_, depth + 1, reverse);
    for (int i = 0; i < depth; ++i)
        std::cout << "\t";
    std::cout << root->value_ << std::endl;
    printAsTree(root->left_, depth + 1, reverse);
    if (reverse) {
        std::swap(root->left_, root->right_);
    }
    if (depth == 0)
        std::cout << "_____________" << std::endl;
}

void Node::printAsTreeExtended(NodePtr root, int depth, bool reverse)
{
    if (!exist(root))
        return;
    if (depth == 0)
        std::cout << "_____________" << std::endl;
    reverse ^= root->needReverse_;
    if (reverse) {
        //std::swap(root->left_, root->right_);
    }
    printAsTreeExtended(root->right_, depth + 1);
    for (int i = 0; i < depth; ++i)
        std::cout << "\t\t";
    std::cout << "val=" << root->value_ << " pref=" << root->sortedPrefix_ << std::endl;
    for (int i = 0; i < depth; ++i)
        std::cout << "\t\t";
    std::cout << "suf=" <<  root->sortedSuffix_ << " rev=" << root->needReverse_ << std::endl;
    for (int i = 0; i < depth; ++i)
        std::cout << "\t\t";
    std::cout << "cnt=" <<  root->subTreeSize_ << std::endl;
    printAsTreeExtended(root->left_, depth + 1);
    if (reverse) {
        //std::swap(root->left_, root->right_);
    }
    if (depth == 0)
        std::cout << "_____________" << std::endl;
}

void Node::printLeaves(NodePtr root, bool reverse)
{
    if (!exist(root))
        return;
    reverse ^= root->needReverse_;
    if (reverse) {
        std::swap(root->left_, root->right_);
    }
    printLeaves(root->left_, reverse);
    std::cout << root->value_ << " ";
    printLeaves(root->right_, reverse);
    if (reverse) {
        std::swap(root->left_, root->right_);
    }
}

void Node::checkIntegrity(NodePtr root, NodePtr parent)
{
    if (!exist(root))
        return;
    if (root->parent_ != parent) {
        std::cerr << "error while checking integrity" << std::endl;
        //throw "error while checking integrity";
    }
    checkIntegrity(root->left_, root);
    checkIntegrity(root->right_, root);
}

// without pair
//void Node::split(NodePtr root, int pos, NodePtr &L, NodePtr &R)
//{
//    if (!exist(root)) {
//        L = nullptr;
//        R = nullptr;
//        return;
//    }
//    if (pos < 0) {
//        L = nullptr;
//        R = root;
//        return;
//    }
//    if (pos > root->subTreeSize_) {
//        L = nullptr;
//        R = root;
//        return;
//    }
//    NodePtr v = getKth(root, pos);
//    splay(v);
//    L = root->left_;
//    R = root;
//    root->left_ = nullptr;
//    if (root->left_) {
//        root->left_->parent_ = nullptr;
//    }
//    return p;
//}
