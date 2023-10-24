#include <gtest/gtest.h>
#include <gtest/gtest.h>

// A simple test case
TEST(SimpleTest, Addition)
{
    int a = 2;
    int b = 3;
    int sum = a + b;

    ASSERT_EQ(sum, 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}