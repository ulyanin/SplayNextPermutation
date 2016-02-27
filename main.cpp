#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "splay_next_permutation.h"
#include "vector_next_permutataion.h"
#include <chrono>
#include <random>
#include <vector>

const int SMALL_TEST = 10;
const int MEDIUM_TEST = 1e4;
const int LARGE_TEST = 1e5;
const int EXTRA_LARGE_TEST = 5e6;
const int MAX_TEST = 1e8;

class TestData
{
public:
    enum TestType {
        tGetSum, tInsertElem, tSetElem, tAdd, tNextPermutation,
    } type;
    size_t L, R;
    long long value;
    TestData() = default;
    explicit TestData(TestType t, size_t L_, size_t R_)
            : type(t), L(L_), R(R_), value(0)
    { }
    explicit TestData(TestType t, size_t L_, size_t R_, long long val)
            : type(t), L(L_), R(R_), value(val)
    { }
    explicit TestData(TestType t, size_t pos, long long val)
            : type(t), L(pos), R(pos), value(val)
    { }

};


class NextPermutationTest : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        engine.seed(42 + 666 + 13 * 179);
        tests_.clear();
        randomRange = std::uniform_int_distribution<size_t>();
        randomProbability = std::uniform_real_distribution<double>(0, 1);
    }

    virtual void TearDown()
    { }
protected:
    std::default_random_engine engine;
    std::uniform_int_distribution<long long> random;
    std::uniform_int_distribution<size_t> randomRange;
    std::uniform_real_distribution<double> randomProbability;
    std::vector<TestData> tests_;

    long long genRandomValue(long long L, long long R)
    {
        return random(engine) % (R - L + 1) + L;
    }

    size_t genRandomPos(size_t L, size_t R)
    {
        return randomRange(engine) % (R - L + 1) + L;
    }

    TestData::TestType genTestType(std::vector<double> prob)
    {
        for (int i = 1; i < 5; ++i) {
            prob[i] += prob[i - 1];
        }
        double rnd = randomProbability(engine);
        if (rnd <= prob[0])
            return TestData::tGetSum;
        if (rnd <= prob[1])
            return TestData::tInsertElem;
        if (rnd <= prob[2])
            return TestData::tInsertElem;
        if (rnd <= prob[3])
            return TestData::tAdd;
        return TestData::tNextPermutation;
    }

    void genTest(size_t testSize, long long minValue, long long maxValue,
                 std::vector<double> prob={0.2, 0.2, 0.2, 0.2, 0.2})
    {
        tests_.push_back(TestData(
                TestData::tInsertElem, 0, genRandomValue(minValue, maxValue)
        ));
        assert(prob.size() == 5 &&
               abs(std::accumulate(prob.begin(), prob.begin() + 5, (double)0) - 1.0) < 1e-5);
        for (size_t num = 1; tests_.size() < testSize; ) {
            size_t L, R;
            switch (genTestType(prob)) {
                case TestData::tGetSum:
                    L = genRandomPos(0, num - 1);
                    R = genRandomPos(L, num - 1);
                    tests_.push_back(TestData(
                            TestData::tGetSum,
                            L, R
                    ));
                    break;
                case TestData::tInsertElem:
                    tests_.push_back(TestData(
                            TestData::tInsertElem,
                            genRandomPos(0, num),
                            genRandomValue(minValue, maxValue)
                    ));
                    break;
                case TestData::tSetElem:
                    tests_.push_back(TestData(
                            TestData::tSetElem,
                            genRandomPos(0, num - 1),
                            genRandomValue(minValue, maxValue)
                    ));
                    break;
                case TestData::tAdd:
                    L = genRandomPos(0, num - 1);
                    R = genRandomPos(L, num - 1);
                    tests_.push_back(TestData(
                            TestData::tAdd,
                            L, R,
                            genRandomValue(minValue, maxValue)
                    ));
                    break;
                case TestData::tNextPermutation:
                    L = genRandomPos(0, num - 1);
                    R = genRandomPos(L, num - 1);
                    tests_.push_back(TestData(
                            TestData::tNextPermutation,
                            L, R
                    ));
            }
        }

    }

    void applyGetSum(const TestData &test)
    {
        long long s1 = right_->getSumOnSegment(test.L, test.R),
                  s2 = toTest_->getSumOnSegment(test.L, test.R);
        EXPECT_EQ(s1, s2) << " while getting sum" << std::endl;
    }

    void applyInsertElem(const TestData &test)
    {
        right_->insert(test.L, test.value);
        toTest_->insert(test.L, test.value);
    }

    void applySetElem(const TestData &test)
    {
        right_->setElem(test.L, test.value);
        toTest_->setElem(test.L, test.value);
    }

    void applyAdd(const TestData &test)
    {
        right_->addOnSegment(test.L, test.R, test.value);
        toTest_->addOnSegment(test.L, test.R, test.value);
    }

    void applyNextPermutation(const TestData &test)
    {
        right_->applyNextPermutation(test.L, test.R);
        toTest_->applyNextPermutation(test.L, test.R);
    }

    void applyTest(INextPermutation * rightStruct, INextPermutation * testStruct, bool fullCheck=false)
    {
        right_ = rightStruct;
        toTest_ = testStruct;
        int testNum = 0;
        for (auto test: tests_) {
            switch (test.type) {
                case TestData::tInsertElem:
                    applyInsertElem(test);
                    break;
                case TestData::tGetSum:
                    applyGetSum(test);
                    break;
                case TestData::tSetElem:
                    applySetElem(test);
                    break;
                case TestData::tAdd:
                    applyAdd(test);
                    break;
                case TestData::tNextPermutation:
                    applyNextPermutation(test);
            }
            if (fullCheck) {
                EXPECT_EQ(right_->getAsVector(), toTest_->getAsVector())
                                    << " after operation on test #" << testNum << std::endl;
            }
            testNum++;
        }
    }

    INextPermutation * right_, * toTest_;
};


int main(int argc, char **argv)
{
    std::cerr.setf(std::cerr.fixed);
    std::cerr.precision(9);

    testing::InitGoogleTest(&argc, argv);
    std::vector<int> v1({1, 2, 3}), v2({2, 4});
    EXPECT_EQ(v1, v2);

    return RUN_ALL_TESTS();
}