#include "plane.hpp"

void Plane::insert(int x, int y) { x_to_y_[x].insert(y); }
void Plane::erase(int x, int y) { x_to_y_[x].erase(y); }

template <typename Container>
auto get_start_end(const Container &c, const Range &range) {
  // find the first element that is GREATER OR EQUAL to the x.low
  const auto start = c.lower_bound(range.low);
  // find the first element that is GREATER than high
  const auto end = c.upper_bound(range.high);
  return std::make_pair(start, end);
}

bool Plane::contains(const Range &x_range, const Range &y_range) {
  auto [x_start, x_end] = get_start_end(x_to_y_, x_range);
  if (x_start == x_end) {
    return false;
  }
  for (auto iter = x_start; iter != x_end; ++iter) {
    const auto &ys = iter->second;
    auto [y_start, y_end] = get_start_end(ys, y_range);
    if (y_start != y_end) {
      return true;
    }
  }
  return false;
}
