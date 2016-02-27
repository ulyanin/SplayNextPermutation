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
    virtual long long getSumOnSegment(int L, int R);
    virtual void insert(int newPos, long long x);
    virtual void setElem(int pos, long long x);
    virtual void addOnSegment(int L, int R, long long add);
    virtual void applyNextPermutation(int L, int R);
    virtual std::vector<long long> getAsVector(int L, int R);
protected:
    std::vector<long long> data_;
};

#endif //VECTOR_NEXT_PERMUTATAION_H
