#include <navigation.hpp>
#include <gtest/gtest.h>

TEST(NavigationTest, TurnPos) {
    EXPECT_EQ(getTurnSquare(0, WHITE), 0);
    EXPECT_EQ(getTurnSquare(1, WHITE), 1);
    EXPECT_EQ(getTurnSquare(0, BLACK), 63);
    EXPECT_EQ(getTurnSquare(1, BLACK), 62);
}
