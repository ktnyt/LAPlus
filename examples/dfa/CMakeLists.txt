include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mnist/include include)
add_executable(run_dfa src/main.cpp src/layer.cpp src/dfa_layer.cpp)
target_link_libraries(run_dfa laplus)
