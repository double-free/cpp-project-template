enable_testing()
include("ut_helper.cmake")

yy_test(
  NAME
    plane
  SRCS
    "plane/plane_tests.cpp"
    "../src/plane.cpp"
  DEPS
    gtest
    gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
)
