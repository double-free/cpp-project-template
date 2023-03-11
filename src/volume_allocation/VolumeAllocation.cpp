#include "VolumeAllocation.hpp"

#include <limits>
#include <iostream>

namespace algo {
  std::vector<Price> get_price_candidates(Price best_bid_price, Price best_ask_price, size_t max_levels)
  {
    std::vector<Price> prices{best_bid_price, best_ask_price};

    bool crossed = false;
    for (auto i=1; i<max_levels; i++)
    {
      Price worse_ask_px = best_ask_price + i;
      Price worse_bid_px = best_bid_price - i;
      // worse prices never cross
      prices.push_back(worse_ask_px);
      prices.push_back(worse_bid_px);

      if (crossed) {
        continue;
      }

      Price better_ask_px = best_ask_price - i;
      Price better_bid_px = best_bid_price + i;
      if (better_ask_px > better_bid_px) {
        prices.push_back(worse_ask_px);
        prices.push_back(worse_bid_px);
      } else if (better_ask_px == better_bid_px) {
        prices.push_back(better_ask_px);
        crossed = true;
      } else {
        // never reach here
      }
    }

    std::cout << "prices: [";
    for (const auto& price : prices ) {
      std::cout << price << ", ";
    }
    std::cout << "]\n";
    return prices;
  }

  std::vector<TradeAllocation> allocate_volume(
    Price total_amount, Quantity total_qty,
    Price best_bid_price, Price best_ask_price, size_t max_levels)
  {
    // safety checks
    if (best_bid_price >= best_ask_price) {
      throw std::invalid_argument("ask and bid prices cross!");
    }

    // no trade
    if (total_qty == 0 || total_amount == 0) {
      return {};
    }

    // one trade
    if (total_qty == 1) {
      TradeAllocation allocation;
      allocation.quantity = total_qty;
      allocation.price_in_ticks = total_amount;
      return {allocation};
    }

    // multiple trades, we need serious allocation now
    std::vector<TradeAllocation> result;

    // TODO: avoid dynamic memory allocation for price candidates
    // it is essentially an unbounded knapsack problem.
    // but we need to sort the price levels as we desire the trade to happen
    auto prices = get_price_candidates(best_bid_price, best_ask_price, max_levels);

    // we have to use 2D dp so that we can print the items
    std::vector<std::vector<Price>> dp(prices.size() + 1);
    for (auto&row : dp) {
      // initialized with -inf, invalid value
      row.resize(total_qty + 1, std::numeric_limits<Price>::min());
      // the first value is valid, because a knapsack with 0 capacity is full
      row[0] = 0;
    }
    for (int i = 1; i<dp.size(); ++i) {
      const auto& price = prices.at(i-1);
      for (Quantity j=1; j<dp[i].size(); ++j) {
        dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-1] + price);
        if (dp[i][j] == total_amount) {
          std::cout << "Find solution with total amount " << total_amount
          << ", total quantity "<< j << ", TODO: output solution.\n";
          return result;
        }
      }
    }

    // solution not found!!!
    // probably you shall choose a greater "max_levels"
    return result;
  }
} /* algo */
