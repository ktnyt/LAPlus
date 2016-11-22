if(LAPLUS_EXAMPLE)
  file(COPY mnist DESTINATION ${PROJECT_BINARY_DIR})
  add_subdirectory(dfa)
endif()
