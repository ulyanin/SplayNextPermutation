#include "vector_next_permutataion.h"
#include <algorithm>
#include <numeric>

VectorNextPermutation::VectorNextPermutation()
{}

void VectorNextPermutation::addOnSegment(size_t L, size_t R, long long add)
{
    std::transform(data_.begin() + L, data_.begin() + R + 1,
                   data_.begin() + L,
                   [add] (long long elem) {
                       return elem + add;
                   });
}

long long VectorNextPermutation::getSumOnSegment(size_t L, size_t R)
{
    return std::accumulate(data_.begin() + L, data_.begin() + R + 1, (long long)0);
}

void VectorNextPermutation::applyNextPermutation(size_t L, size_t R)
{
    std::next_permutation(data_.begin() + L, data_.begin() + R + 1);
}

void VectorNextPermutation::insert(size_t newPos, long long x)
{
    data_.insert(data_.begin() + newPos, x);
}

void VectorNextPermutation::setElem(size_t pos, long long x)
{
    data_.at(pos) = x;
}

size_t VectorNextPermutation::size() const
{
    return data_.size();
}
