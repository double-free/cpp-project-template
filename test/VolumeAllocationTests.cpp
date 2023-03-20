#include "../src/volume_allocation/VolumeAllocation.hpp"

#include <gtest/gtest.h>

TEST(VolumeAllocationTests, crossed_book) {
  int total_qty = 0;
  int total_amount = 0;
  int best_bid_price = 98;
  int best_ask_price = 98;
  int max_levels = 10;
  EXPECT_THROW(algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                     best_ask_price, max_levels),
               std::invalid_argument);
}

TEST(VolumeAllocationTests, no_trade) {
  int total_qty = 0;
  int total_amount = 0;
  int best_bid_price = 98;
  int best_ask_price = 100;
  int max_levels = 10;
  auto result = algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                      best_ask_price, max_levels);
  EXPECT_EQ(0, result.size());
}

TEST(VolumeAllocationTests, one_trade) {
  int total_qty = 1;
  int total_amount = 1 * 101;
  int best_bid_price = 98;
  int best_ask_price = 100;
  int max_levels = 10;
  auto result = algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                      best_ask_price, max_levels);
  ASSERT_EQ(1, result.size());
  EXPECT_EQ(101, result[0].price);
  EXPECT_EQ(1, result[0].quantity);
}

TEST(VolumeAllocationTests, one_level_trade) {
  int total_qty = 3;
  int total_amount = 3 * 101;
  int best_bid_price = 98;
  int best_ask_price = 100;
  int max_levels = 10;
  auto result = algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                      best_ask_price, max_levels);
  ASSERT_EQ(1, result.size());
  EXPECT_EQ(101, result[0].price);
  EXPECT_EQ(3, result[0].quantity);
}

TEST(VolumeAllocationTests, multiple_levels_trade) {
  int total_qty = 6;
  // traded in 3 levels, 100, 98, 101
  int total_amount = 2 * 100 + 3 * 98 + 101;
  int best_bid_price = 98;
  int best_ask_price = 100;
  int max_levels = 10;
  auto result = algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                      best_ask_price, max_levels);
  ASSERT_EQ(3, result.size());
  EXPECT_EQ(98, result[0].price);
  EXPECT_EQ(3, result[0].quantity);

  EXPECT_EQ(100, result[1].price);
  EXPECT_EQ(2, result[1].quantity);

  EXPECT_EQ(101, result[2].price);
  EXPECT_EQ(1, result[2].quantity);
}

TEST(VolumeAllocationTests, buy_3_levels) {
  int total_qty = 6;
  // traded in 3 levels, 100, 98, 101
  int total_amount = 3 * 98 + 2 * 97 + 96;
  int best_bid_price = 98;
  int best_ask_price = 100;
  int max_levels = 10;
  auto result = algo::allocate_volume(total_amount, total_qty, best_bid_price,
                                      best_ask_price, max_levels);

  std::cout << algo::serialize(result) << "\n";
  ASSERT_EQ(3, result.size());
  EXPECT_EQ(98, result[0].price);
  EXPECT_EQ(3, result[0].quantity);

  EXPECT_EQ(97, result[1].price);
  EXPECT_EQ(2, result[1].quantity);

  EXPECT_EQ(96, result[2].price);
  EXPECT_EQ(1, result[2].quantity);
}
