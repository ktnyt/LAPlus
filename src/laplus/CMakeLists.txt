if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

set(CPP_FILES vectorf.cpp matrixf.cpp)
add_library(laplus SHARED ${CPP_FILES})
add_library(laplus_static STATIC ${CPP_FILES})
target_link_libraries(laplus openblas)
target_link_libraries(laplus_static openblas)
