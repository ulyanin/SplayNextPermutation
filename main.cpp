#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "splay_next_permutation.h"
#include "vector_next_permutataion.h"
#include <chrono>
#include <random>
#include <vector>

const size_t SMALL_TEST = 100;
const size_t MEDIUM_TEST = 5e3;
const size_t LARGE_TEST = 1e5;
const size_t EXTRA_LARGE_TEST = 5e6;
const size_t MAX_TEST = 1e8;

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
    bool testRightStruct_;
    INextPermutation * right_, * toTest_;

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
            return TestData::tSetElem;
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
                    std::cout << R - L << std::endl;
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
                    ++num;
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
                    std::cout << R - L << std::endl;
                    tests_.push_back(TestData(
                            TestData::tAdd,
                            L, R,
                            genRandomValue(minValue, maxValue)
                    ));
                    break;
                case TestData::tNextPermutation:
                    L = genRandomPos(0, num - 1);
                    R = genRandomPos(L, num - 1);
                std::cout << R - L << std::endl;
                    tests_.push_back(TestData(
                            TestData::tNextPermutation,
                            L, R
                    ));
            }
        }

    }

    void applyGetSum(const TestData &test)
    {
        long long s1, s2;
        s2 = toTest_->getSumOnSegment(test.L, test.R);
        if (testRightStruct_) {
            s1 = right_->getSumOnSegment(test.L, test.R);
            EXPECT_EQ(s1, s2) << " while getting sum" << std::endl;
        }
    }

    void applyInsertElem(const TestData &test)
    {
        if (testRightStruct_) {
            right_->insert(test.L, test.value);
        }
        toTest_->insert(test.L, test.value);
    }

    void applySetElem(const TestData &test)
    {
        if (testRightStruct_) {
            right_->setElem(test.L, test.value);
        }
        toTest_->setElem(test.L, test.value);
    }

    void applyAdd(const TestData &test)
    {
        if (testRightStruct_) {
            right_->addOnSegment(test.L, test.R, test.value);
        }
        toTest_->addOnSegment(test.L, test.R, test.value);
    }

    void applyNextPermutation(const TestData &test)
    {
        if (testRightStruct_) {
            right_->applyNextPermutation(test.L, test.R);
        }
        toTest_->applyNextPermutation(test.L, test.R);
    }

    double applyTests(INextPermutation * rightStruct, INextPermutation * testStruct,
                      bool fullCheck=false, bool testRightStruct=true)
    {
        auto start(std::chrono::steady_clock::now());
        testRightStruct_ = testRightStruct;
        if (testRightStruct_) {
            right_ = rightStruct;
        }
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
            if (fullCheck && testRightStruct_) {
                auto v1 = right_->getAsVector(0, (int)right_->size() - 1);
                auto v2 = toTest_->getAsVector(0, (int)toTest_->size() - 1);
                EXPECT_EQ(v1, v2) << " after operation on test #" << testNum << std::endl;
            }
            testNum++;
        }
        auto end(std::chrono::steady_clock::now());
        return std::chrono::duration_cast<std::chrono::duration<double> > (end - start).count();
    }
};


TEST_F(NextPermutationTest, SimpleTest)
{
    size_t size = 12;
    INextPermutation *splay = new SplayNextPermutation(),
            *simply = new VectorNextPermutation();
    genTest(size, 0, size);
    applyTests(simply, splay, true);
    delete splay;
    delete simply;
}

TEST_F(NextPermutationTest, TestsWithFullCheckRare)
{
    size_t size = 1;
    while ((size *= 10) <= MEDIUM_TEST) {
        size_t cnt = 10;
        if (size == MEDIUM_TEST)
            cnt = 1;
        for (size_t i = 0; i < cnt; ++i) {
            INextPermutation *splay = new SplayNextPermutation(),
                             *simply = new VectorNextPermutation();
            genTest(size, 0, 1e9);
            applyTests(simply, splay, true);
            delete splay;
            delete simply;
        }
    }
}


TEST_F(NextPermutationTest, TestsWithFullCheckDensely)
{
    size_t size = 1;
    while ((size *= 10) <= MEDIUM_TEST) {
        size_t cnt = 10;
        if (size == MEDIUM_TEST)
            cnt = 1;
        for (size_t i = 0; i < cnt; ++i) {
            INextPermutation *splay = new SplayNextPermutation(),
                             *simply = new VectorNextPermutation();
            genTest(size, 0, (long long)size / 2LL * (i + 1LL));
            applyTests(simply, splay, true);
            delete splay;
            delete simply;
        }
    }
}

TEST_F(NextPermutationTest, SimpleTests)
{
    for (int i = 0; i < 100; ++i) {
        size_t size = SMALL_TEST;
        INextPermutation *splay = new SplayNextPermutation(),
                *simply = new VectorNextPermutation();
        genTest(size, 0, 1e9);
        applyTests(simply, splay, true);
        delete splay;
        delete simply;
    }
}

TEST_F(NextPermutationTest, TestInsert)
{
    size_t size = 1;
    while ((size *= 10) <= MEDIUM_TEST) {
        size_t cnt = 1000;
        for (size_t i = 0; i < cnt; ++i) {
            INextPermutation *splay = new SplayNextPermutation(),
                             *simply = new VectorNextPermutation();
            genTest(size, 0, (long long)size / 2LL * (i + 1LL), {0, 1, 0, 0, 0});
            applyTests(simply, splay, false);
            delete splay;
            delete simply;
        }
    }
}

TEST_F(NextPermutationTest, TestSetElem)
{
    size_t size = 1;
    while ((size *= 10) <= MEDIUM_TEST) {
        size_t cnt = 1000;
        for (size_t i = 0; i < cnt; ++i) {
            INextPermutation *splay = new SplayNextPermutation(),
                             *simply = new VectorNextPermutation();
            genTest(size, 0, (long long)size / 2LL * (i + 1LL), {0, 0.2, 0.8, 0, 0});
            applyTests(simply, splay, false);
            delete splay;
            delete simply;
        }
    }
}

TEST_F(NextPermutationTest, TestAdd)
{
    size_t size = 1;
    while ((size *= 10) <= MEDIUM_TEST) {
        size_t cnt = 1000;
        for (size_t i = 0; i < cnt; ++i) {
            INextPermutation *splay = new SplayNextPermutation(),
                             *simply = new VectorNextPermutation();
            genTest(size, 0, (long long)size / 2LL * (i + 1LL), {0, 0.2, 0, 0.8, 0});
            applyTests(simply, splay, false);
            delete splay;
            delete simply;
        }
    }
}


TEST_F(NextPermutationTest, CompareWorkingTime)
{

    size_t size = 1e6;
    INextPermutation *splay = new SplayNextPermutation(),
                     *simply = new VectorNextPermutation();
    genTest(size, 0, (long long)size, {0.3, 0.3, 0.1, 0.3, 0});
    long double s1, s2;
    std::cout << "starting simple realisation on test" << std::endl;
    s1 = applyTests(nullptr, simply, false, false);
    std::cout << "starting splay tree on test" << std::endl;
    s2 = applyTests(nullptr, splay, false, false);
    std::cout << "simple realisation as vector has worked for a " << s1 << " seconds" << std::endl;
    std::cout << "splay has worked for a " << s2 << " seconds" << std::endl;
    delete splay;
    delete simply;
}


int main(int argc, char **argv)
{
    std::cerr.setf(std::cerr.fixed);
    std::cerr.precision(9);
    testing::InitGoogleTest(&argc, argv);
//    std::vector<int> v1({1, 2, 3}), v2({2, 4});
//    EXPECT_EQ(v1, v2);

    return RUN_ALL_TESTS();
}