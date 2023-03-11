#pragma once

#include <vector>
#include <cstddef>

namespace algo {
  struct TradeAllocation {
    int price_in_ticks{0};
    int quantity{0};
  };

  using Price = int;
  using Quantity = int;

  std::vector<Price> get_price_candidates(Price best_bid_price, Price best_ask_price, size_t max_levels);

  std::vector<TradeAllocation> allocate_volume(
    Price total_amount, Quantity total_qty,
    Price best_bid_price, Price best_ask_price, size_t max_levels);
} /* algo */
