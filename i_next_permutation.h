#ifndef I_NEXT_PERMUTATION_H
#define I_NEXT_PERMUTATION_H

#include <vector>

#define DEBUG

using std::size_t;

class INextPermutation
{
public:
    virtual long long getSumOnSegment(size_t L, size_t R) = 0;
    virtual void insert(size_t newPos, long long x) = 0;
    virtual void setElem(size_t pos, long long x) = 0;
    virtual void addOnSegment(size_t L, size_t R, long long add) = 0;
    virtual void applyNextPermutation(size_t L, size_t R) = 0;
    virtual size_t size() const = 0;
    virtual std::vector<long long> getAsVector(int L, int R)
    {
        std::vector<long long> res((R - L + 1), 0);
        for (int i = L; i <= R; ++i) {
            res[i - L] = getSumOnSegment(i, i);
        }
        return std::move(res);
    }
    virtual ~INextPermutation() {}
};



#endif //I_NEXT_PERMUTAION_H
