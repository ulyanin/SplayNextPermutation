//
// Created by ulyanin on 23.02.16.
//

#ifndef SPLAY_NEXT_PERMUTATION_H
#define SPLAY_NEXT_PERMUTATION_H

#include "i_next_permutation.h"
#include "splay_node.h"

class SplayNextPermutation
    : public INextPermutation
{
public:
    SplayNextPermutation();
    virtual long long getSumOnSegment(size_t L, size_t R);
    virtual void insert(size_t newPos, long long x);
    virtual void setElem(size_t pos, long long x);
    virtual void addOnSegment(size_t L, size_t R, long long add);
    virtual void applyNextPermutation(size_t L, size_t R);
    virtual std::vector<long long> getAsVector(size_t L, size_t R);
protected:
    Node::NodePtr root_;
};

#endif //SPLAY_NEXT_PERMUTATION_H
