include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)

enable_testing()

if (test)
  add_executable(unit_tests laplus.cpp)
  target_link_libraries(unit_tests gtest gtest_main openblas)
  add_test(NAME laplus-test COMMAND unit_tests)
endif()
