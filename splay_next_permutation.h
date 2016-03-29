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
    virtual long long getSumOnSegment(size_t L, size_t R) override ;
    virtual void insert(size_t newPos, long long x) override ;
    virtual void setElem(size_t pos, long long x) override ;
    virtual void addOnSegment(size_t L, size_t R, long long add) override ;
    virtual void applyNextPermutation(size_t L, size_t R) override ;
    virtual size_t size() const override;
    size_t depth() const;
protected:
    Node::NodePtr root_;
};

#endif //SPLAY_NEXT_PERMUTATION_H
