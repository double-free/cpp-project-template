enable_testing()
include("ut_helper.cmake")

yy_test(
NAME
  va
SRCS
  VolumeAllocationTests.cpp
DEPS
  gtest
  gtest_main
  volume_allocation
)
