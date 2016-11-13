if(test AND NOT TARGET gtest)
  add_subdirectory(googletest)
endif()

if(benchmark AND NOT TARGET benchmark)
  add_subdirectory(benchmark)
endif()
