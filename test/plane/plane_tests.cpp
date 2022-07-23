#include "../../src/plane.hpp"

#include <gtest/gtest.h>

TEST(PlaneTests, basic_apis) {
  XXX x;
  EXPECT_EQ(false, x.contains(1, {0, 4}, {2, 5}));
  x.insert(1, 2, 3);
  EXPECT_EQ(true, x.contains(1, {0, 4}, {2, 5}));
  x.erase(1, 2, 3);
  EXPECT_EQ(false, x.contains(1, {0, 4}, {2, 5}));
}

TEST(PlaneTests, find_lower_x) {
  XXX x;
  x.insert(1, 2, 3);

  // given range.max is lower
  EXPECT_EQ(false, x.contains(1, {0, 1}, {2, 5}));

  // on boundary
  EXPECT_EQ(true, x.contains(1, {0, 2}, {2, 5}));
}

TEST(PlaneTests, find_higher_x) {
  XXX x;
  x.insert(1, 2, 3);

  // given range.max is higher
  EXPECT_EQ(false, x.contains(1, {3, 4}, {2, 5}));

  // on boundary
  EXPECT_EQ(true, x.contains(1, {2, 4}, {2, 5}));
}

TEST(PlaneTests, find_lower_y) {
  XXX x;
  x.insert(1, 2, 3);

  // given range.max is lower
  EXPECT_EQ(false, x.contains(1, {0, 2}, {0, 2}));

  // on boundary
  EXPECT_EQ(true, x.contains(1, {0, 2}, {0, 3}));
}

TEST(PlaneTests, find_higher_y) {
  XXX x;
  x.insert(1, 2, 3);

  // given range.max is higher
  EXPECT_EQ(false, x.contains(1, {2, 4}, {4, 5}));

  // on boundary
  EXPECT_EQ(true, x.contains(1, {2, 4}, {3, 5}));
}

TEST(PlaneTests, search_cross) {
  XXX x;

  x.insert(1, 2, 13);
  x.insert(1, 12, 3);

  EXPECT_EQ(false, x.contains(1, {10, 15}, {10, 15}));
  x.insert(1, 12, 13);
  EXPECT_EQ(true, x.contains(1, {10, 15}, {10, 15}));
}
