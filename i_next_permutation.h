#ifndef I_NEXT_PERMUTATION_H
#define I_NEXT_PERMUTATION_H

#include <vector>

using std::size_t;

class INextPermutation
{
public:
    virtual long long getSumOnSegment(size_t L, size_t R) = 0;
    virtual void insert(size_t newPos, long long x) = 0;
    virtual void setElem(size_t pos, long long x) = 0;
    virtual void addOnSegment(size_t L, size_t R, long long add) = 0;
    virtual void applyNextPermutation(size_t L, size_t R) = 0;
    virtual std::vector<long long> getAsVector() = 0;
    virtual ~INextPermutation() {}
};

#endif //I_NEXT_PERMUTAION_H
