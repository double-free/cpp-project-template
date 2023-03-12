#include "VolumeAllocation.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <numeric>

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


  // solve the unbounded knapsack problem
  // extra contraint is that the knapsack must be full
  [[nodiscard]] std::vector<TradeAllocation> solve_unbounded_knapsack(
    Price total_amount, Quantity total_qty,
    const std::vector<Price> prices)
  {
    using Solution = std::vector<Quantity>;
    using Solutions = std::vector<std::vector<Quantity>>;
    // we have to use 2D dp so that we can print the items
    // dp[i][j] is the solution of selected items, -1 means no solution.
    // For the first i items, to achieve total value j.
    std::vector<std::vector<Solutions>> dp(prices.size() + 1);

    for (auto&row : dp) {
      // initialized with -1, invalid value
      row.resize(total_amount + 1);
      // the first value is valid, because a knapsack with 0 capacity is full
      row[0] = {Solution(prices.size(), 0)};
    }

    std::vector<TradeAllocation> result;
    for (int i = 1; i<dp.size(); ++i) {
      const auto& px = prices.at(i-1);
      for (Price j=px; j<dp[i].size(); ++j) {
        // at least, with the extra ith item, it can have the same solution as
        // the first i-1 items.
        dp[i][j] = dp[i-1][j];
        // the ith item can add another solution
        for (const auto& prev_solution: dp[i][j-px]) {
          // deep copy
          auto solution = prev_solution;
          // add one ith item
          solution[i-1] += 1;
          dp[i][j].push_back(solution);
        }
      }

      for (const auto& solution: dp[i][total_amount])
      {
        if (std::accumulate(solution.begin(), solution.end(), 0) != total_qty) {
          continue;
        }

        for (size_t i=0; i<solution.size(); ++i) {
          const auto& qty = solution[i];
          if (qty > 0) {
            TradeAllocation allocation;
            allocation.quantity = qty;
            allocation.price = prices.at(i);
            result.push_back(allocation);
          }
        }
        // return on finding first solution
        if (result.size() > 0) {
          std::cout << "Find solution with total amount " << total_amount
          << ", total quantity "<< total_qty << " with first " << i
          << " items,TODO: output solution.\n";
          return result;
        }
      }
    }

    // solution not found, probably choose a greater price range?
    return result;
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
      allocation.price = total_amount;
      return {allocation};
    }

    // multiple trades, we need serious allocation now

    // TODO: avoid dynamic memory allocation for price candidates
    // it is essentially an unbounded knapsack problem.
    // but we need to sort the price levels as we desire the trade to happen
    auto prices = get_price_candidates(best_bid_price, best_ask_price, max_levels);

    // we need to use the price offset instead of real price to save space
    const auto& pivot_price = *std::min_element(prices.begin(), prices.end());
    auto offset_prices = prices;
    for (auto& px : offset_prices) {
      px -= pivot_price;
    }
    auto offset_total_amount = total_amount - pivot_price * total_qty;
    assert(offset_total_amount > 0);

    std::vector<TradeAllocation> result = solve_unbounded_knapsack(
      offset_total_amount, total_qty, offset_prices);

    for (auto& allocation : result) {
      // restore offset price to original price
      allocation.price += pivot_price;
    }
    // solution not found!!!
    // probably you shall choose a greater "max_levels"
    return result;
  }
} /* algo */
