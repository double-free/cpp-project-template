#include "VolumeAllocation.hpp"

namespace algo {
  std::vector<TradeAllocation> volume_allocation(int total_amount, int total_qty, int pivot_price, int max_levels)
  {
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

    

    return result;
  }
} /* algo */
