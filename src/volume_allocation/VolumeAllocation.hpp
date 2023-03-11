#pragma once

#include <vector>

namespace algo {
  struct TradeAllocation {
    int price_in_ticks{0};
    int quantity{0};
  };

  // looking for at most K levels from given pivot price
  std::vector<TradeAllocation> volume_allocation(int total_amount, int total_qty, int pivot_price, int max_levels);
} /* algo */
