#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <new>

#ifdef __cpp_lib_hardware_interference_size
    using std::hardware_constructive_interference_size;
    using std::hardware_destructive_interference_size;
#else
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif

// a toy function to measure cache performance
void func(std::vector<int> *counter, size_t index) {
  for (int i = 0; i < 1000000; ++i) {
    (*counter)[index] += 1;
  }
}

auto run_in_parallel(size_t thread_num, size_t offset) {
  auto start = std::chrono::steady_clock::now();
  std::vector<int> counter(1024, 0);

  std::vector<std::thread> threads;
  for (size_t i = 0; i < thread_num; ++i) {
    threads.emplace_back(func, &counter, i * offset);
  }
  for (auto &t : threads) {
    t.join();
  }

  auto end = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

int main(int argc, char const *argv[]) {
  std::cout
    << "hardware_destructive_interference_size == "
    << hardware_destructive_interference_size << '\n'
    << "hardware_constructive_interference_size == "
    << hardware_constructive_interference_size << "\n";

  size_t thread_num = 8;

  auto offset1 = hardware_constructive_interference_size / sizeof(int);
  for (size_t offset = 1; offset < offset1; offset *= 2) {
    auto elapsed_us = run_in_parallel(thread_num, offset).count();
    std::cout << "Time elapsed: " << elapsed_us << "us for offset "<< offset <<"\n";
  }

  auto offset2 = hardware_destructive_interference_size / sizeof(int);
  for (size_t offset = offset1; offset <= offset2 + offset1; offset += offset1) {
    auto elapsed_us = run_in_parallel(thread_num, offset).count();
    std::cout << "Time elapsed: " << elapsed_us << "us for offset "<< offset <<"\n";
  }
  return 0;
}
