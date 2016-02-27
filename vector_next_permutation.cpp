#include "vector_next_permutataion.h"
#include <algorithm>

VectorNextPermutation::VectorNextPermutation()
{}

void VectorNextPermutation::addOnSegment(int L, int R, long long add)
{
    std::transform(data_.begin() + L, data_.begin() + R + 1,
                   [add] (long long elem) {
                       return elem + add;
                   });
}

long long VectorNextPermutation::getSumOnSegment(int L, int R)
{
    return std::accumulate(data_.begin() + L, data_.begin() + R + 1, 0);
}

void VectorNextPermutation::applyNextPermutation(int L, int R)
{
    std::next_permutation(data_.begin() + L, data_.begin() + R + 1);
}

void VectorNextPermutation::insert(int newPos, long long x)
{
    data_.insert(data_.begin() + newPos, x);
}

void VectorNextPermutation::setElem(int pos, long long x)
{
    data_.at(pos) = x;
}