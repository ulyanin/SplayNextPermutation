#include "splay_next_permutation.h"

SplayNextPermutation::SplayNextPermutation()
{
    root_ = nullptr;
}

long long SplayNextPermutation::getSumOnSegment(size_t L, size_t R)
{
    return Node::getSumOnSegment(root_, L, R);
}

void SplayNextPermutation::insert(size_t newPos, long long value)
{
    Node::insertValue(root_, newPos, value);
}

void SplayNextPermutation::setElem(size_t pos, long long value)
{
    Node::setValue(root_, pos, value);
}

void SplayNextPermutation::addOnSegment(size_t L, size_t R, long long add)
{
    Node::addOnSegment(root_, L, R, add);
}

void SplayNextPermutation::applyNextPermutation(size_t L, size_t R)
{
    Node::nextPermutationOnSegment(root_, L, R);
}

size_t SplayNextPermutation::size() const
{
    return Node::getSubTreeSize(root_);
}
