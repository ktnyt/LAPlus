if(LAPLUS_TEST)
  include_directories(${gtest_SOURCE_DIR}/include)
  enable_testing()
  add_executable(unit_tests
    laplus/internal/array.cpp
    laplus/internal/shared_array.cpp

    laplus/vectorf.cpp
    laplus/matrixf.cpp
  )
  target_link_libraries(unit_tests laplus openblas gtest gtest_main)
  add_test(NAME laplus-test COMMAND unit_tests)
endif()

if(LAPLUS_BENCH)
  include_directories(${benchmark_SOURCE_DIR}/include)
  enable_testing()
  add_executable(benchmarks benchmarks.cpp)
  target_link_libraries(benchmarks openblas benchmark)
endif()
