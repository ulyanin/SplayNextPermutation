//
// Created by ulyanin on 23.02.16.
//

#ifndef VECTOR_NEXT_PERMUTATAION_H
#define VECTOR_NEXT_PERMUTATAION_H

#include <vector>
#include "i_next_permutation.h"

class VectorNextPermutation
        : public INextPermutation
{
public:
    VectorNextPermutation();
    virtual long long getSumOnSegment(size_t L, size_t R);
    virtual void insert(size_t newPos, long long x);
    virtual void setElem(size_t pos, long long x);
    virtual void addOnSegment(size_t L, size_t R, long long add);
    virtual void applyNextPermutation(size_t L, size_t R);
    virtual size_t size() const;
protected:
    std::vector<long long> data_;
};

#endif //VECTOR_NEXT_PERMUTATAION_H
