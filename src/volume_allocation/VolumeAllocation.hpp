#pragma once

#include <vector>
#include <cstddef>

namespace algo {
  using Price = int;
  using Quantity = int;

  struct TradeAllocation {
    Price price{0};
    Quantity quantity{0};
  };

  std::vector<Price> get_price_candidates(Price best_bid_price, Price best_ask_price, size_t max_levels);

  std::vector<TradeAllocation> allocate_volume(
    Price total_amount, Quantity total_qty,
    Price best_bid_price, Price best_ask_price, size_t max_levels);
} /* algo */
