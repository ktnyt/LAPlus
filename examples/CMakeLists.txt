if(LAPLUS_EXAMPLE)
  file(COPY mnist DESTINATION ${CMAKE_BINARY_DIR})
  add_subdirectory(dfa)
endif()
