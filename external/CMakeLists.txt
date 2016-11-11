include(ExternalProject)

set(EXERNAL_BUILD_THREADS 1 CACHE STRING "Number of threads to build external projects")

ExternalProject_Add(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/googletest
  CMAKE_ARGS
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make -j ${EXTERNAL_BUILD_THREADS}
  INSTALL_COMMAND make install
)

ExternalProject_Add(
  OpenBLAS
  GIT_REPOSITORY https://github.com/xianyi/OpenBLAS
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/OpenBLAS
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/OpenBLAS/src/OpenBLAS
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make USE_THREADS=0 -j ${EXTERNAL_BUILD_THREADS}
  INSTALL_COMMAND make install PREFIX=${CMAKE_INSTALL_PREFIX}
)

include_directories(${CMAKE_INSTALL_PREFIX}/include)
link_directories(${CMAKE_INSTALL_PREFIX}/lib)
