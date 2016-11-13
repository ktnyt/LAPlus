if(LAPLUS_TEST AND NOT TARGET gtest)
  add_subdirectory(googletest)
endif()

if(LAPLUS_BENCH AND NOT TARGET benchmark)
  add_subdirectory(benchmark)
endif()
