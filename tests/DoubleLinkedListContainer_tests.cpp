#include <cstddef>
#include <vector>

#include "DoubleLinkedListContainer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


struct DoubleLinkedListContainerFixture : public testing::Test {
    DoubleLinkedListContainer<int> c;

    void SetUp() override {
        for (int i = 0; i < 5; ++i) {
            c.push_back(i+1);
        }
    }

    void AssertEqualsToVector(std::vector<int> v) {
        ASSERT_EQ(c.size(), v.size());
        for (size_t i = 0; i < c.size(); ++i) {
            ASSERT_EQ(c[i], v[i]);
        }
    }
};

struct MockElement {
    MockElement() {}
    MockElement(const MockElement& e) {}
    MockElement& operator=(const MockElement& other) { return *this; }

    MOCK_METHOD(void, die, ());
    ~MockElement() { die(); }
};


TEST(DoubleLinkedListContainer, CtorOk) {
    DoubleLinkedListContainer<int> c1;
    DoubleLinkedListContainer<float> c2;

    ASSERT_EQ(c1.size(), 0);
    ASSERT_EQ(c2.size(), 0);
}

TEST_F(DoubleLinkedListContainerFixture, PushBackOk) {
    c.push_back(6);
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_F(DoubleLinkedListContainerFixture, InsertIntoBeginningOk) {
    c.insert(0, 0);
    AssertEqualsToVector(std::vector<int>{0, 1, 2, 3, 4, 5});
}

TEST_F(DoubleLinkedListContainerFixture, InsertIntoCenterOk) {
    c.insert(c.size()/2, 0);
    AssertEqualsToVector(std::vector<int>{1, 2, 0, 3, 4, 5});
}

TEST_F(DoubleLinkedListContainerFixture, InsertIntoEndOk) {
    c.insert(c.size(), 0);
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4, 5, 0});
}

TEST_F(DoubleLinkedListContainerFixture, EraseAtBegginningOk) {
    c.erase(0);
    AssertEqualsToVector(std::vector<int>{2, 3, 4, 5});
}

TEST_F(DoubleLinkedListContainerFixture, EraseAtCenterOk) {
    c.erase(c.size()/2);
    AssertEqualsToVector(std::vector<int>{1, 2, 4, 5});
}

TEST_F(DoubleLinkedListContainerFixture, EraseAtEndOk) {
    c.erase(c.size()-1);
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4});
}

TEST_F(DoubleLinkedListContainerFixture, SizeOk) {
    ASSERT_EQ(c.size(), 5);
}

TEST_F(DoubleLinkedListContainerFixture, ElementAssignmentOk) {
    c[1] = 100;
    AssertEqualsToVector(std::vector<int>{1, 100, 3, 4 ,5});
}

TEST(MockElementDDL, DtorOk) {
    DoubleLinkedListContainer<MockElement> c;

    MockElement e1;
    EXPECT_CALL(e1, die()).Times(1);

    MockElement e2;
    EXPECT_CALL(e2, die()).Times(1);

    c.push_back(e1);
    c.push_back(e2);
}
