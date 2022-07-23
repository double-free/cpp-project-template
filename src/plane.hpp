#pragma once

#include <map>
#include <set>
#include <unordered_map>

struct Range {
  int low{0};
  int high{0};
};

struct Point {
  int x{0};
  int y{0};
};

class Plane {
public:
  void insert(int x, int y);
  void erase(int x, int y);
  bool contains(const Range &x_range, const Range &y_range);

private:
  // security id to container
  std::map<int, std::set<int>> x_to_y_;
};

class XXX {
public:
  void insert(int secid, int price, int quantity) {
    return planes_[secid].insert(price, quantity);
  }
  void erase(int secid, int price, int quantity) {
    return planes_[secid].erase(price, quantity);
  }
  bool contains(int secid, const Range &price_range, const Range &qty_range) {
    return planes_[secid].contains(price_range, qty_range);
  }

private:
  // security id to plane
  std::unordered_map<int, Plane> planes_;
};
