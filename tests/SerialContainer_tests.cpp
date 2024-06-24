#include <cstddef>
#include <vector>

#include "SerialContainer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


struct SerialContainerFixture : public testing::Test {
    SerialContainer<int> c;

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
    MockElement& operator=(const MockElement& other) { return *this; }

    MOCK_METHOD(void, die, ());
    ~MockElement() { die(); }
};


TEST(SerialContainer, CtorOk) {
    SerialContainer<int> c1;
    SerialContainer<float> c2;

    ASSERT_EQ(c1.size(), 0);
    ASSERT_EQ(c2.size(), 0);
}

TEST_F(SerialContainerFixture, PushBackOk) {
    c.push_back(6);
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_F(SerialContainerFixture, InsertIntoBeginningOk) {
    c.insert(0, 0);
    AssertEqualsToVector(std::vector<int>{0, 1, 2, 3, 4, 5});
}

TEST_F(SerialContainerFixture, InsertIntoCenterOk) {
    c.insert(c.size()/2, 0);
    AssertEqualsToVector(std::vector<int>{1, 2, 0, 3, 4, 5});
}

TEST_F(SerialContainerFixture, InsertIntoEndOk) {
    c.insert(c.size(), 0);
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4, 5, 0});
}

TEST_F(SerialContainerFixture, EraseAtBegginningOk) {
    c.erase(0);
    AssertEqualsToVector(std::vector<int>{2, 3, 4, 5});
}

TEST_F(SerialContainerFixture, EraseAtCenterOk) {
    c.erase(c.size()/2);
    AssertEqualsToVector(std::vector<int>{1, 2, 4, 5});
}

TEST_F(SerialContainerFixture, EraseAtEndOk) {
    c.erase(c.size());
    AssertEqualsToVector(std::vector<int>{1, 2, 3, 4});
}

TEST_F(SerialContainerFixture, SizeOk) {
    ASSERT_EQ(c.size(), 5);
}

TEST_F(SerialContainerFixture, ElementAssignmentOk) {
    c[1] = 100;
    AssertEqualsToVector(std::vector<int>{1, 100, 3, 4 ,5});
}

TEST_F(SerialContainerFixture, MoveCtorOk) {
    SerialContainer<int> c2{std::move(c)};
    ASSERT_EQ(c.size(), 0);

    ASSERT_EQ(c2.size(), 5);
    for (size_t i = 0; i < c.size(); ++i) {
        ASSERT_EQ(c2[i], i+1);
    }
}

TEST_F(SerialContainerFixture, MoveAssignmentOk) {
    SerialContainer<int> c2;
    c2 = std::move(c);
    ASSERT_EQ(c.size(), 0);

    ASSERT_EQ(c2.size(), 5);
    for (size_t i = 0; i < c.size(); ++i) {
        ASSERT_EQ(c2[i], i+1);
    }
}

TEST(MockElement, DtorOk) {
    SerialContainer<MockElement> c;

    MockElement e1;
    EXPECT_CALL(e1, die()).Times(1);

    MockElement e2;
    EXPECT_CALL(e2, die()).Times(1);

    c.push_back(e1);
    c.push_back(e2);
}
