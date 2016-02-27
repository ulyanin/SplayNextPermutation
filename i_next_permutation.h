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
    virtual std::vector<long long> getAsVector(size_t L, size_t R);
    virtual ~INextPermutation() {}
};


std::vector<long long> INextPermutation::getAsVector(size_t L, size_t R)
{
    std::vector<long long> res((R - L + 1), 0);
    for (size_t i = L; i <= R; ++i) {
        res[i - L] = getSumOnSegment(L, L);
    }
    return std::move(res);
}

#endif //I_NEXT_PERMUTAION_H
