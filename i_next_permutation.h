#ifndef I_NEXT_PERMUTATION_H
#define I_NEXT_PERMUTATION_H

#include <vector>

class INextPermutation
{
public:
    virtual long long subSegmentSum(int L, int R) = delete;
    virtual void Insert(int i, long long x) = delete;
    virtual void SetElem(int i, long long x) = delete;
    virtual void addSubSegment(int L, int R, long long add) = delete;
    virtual void applyNextPermutation(int L, int R) = delete;
    virtual std::vector<long long> getAsVector() = delete;
    virtual ~INextPermutation() {}
};

#endif //I_NEXT_PERMUTAION_H
