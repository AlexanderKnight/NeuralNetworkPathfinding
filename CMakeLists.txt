
cmake_minimum_required (VERSION 2.6)

project (NeuralNetworkPathfinding)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(nnpflib nnpf.h main.cpp)
add_library(domlib dom.h domain.cpp)

#add_library(celllib cells.h average_cell_centers.c)
#target_compile_features(celllib PUBLIC c_std_99)

#link_libraries(nnpflib nnpf.h)
#add_executable(average average.c)
#add_executable(integration integration.c)

#add_executable(domaintest domain.cpp)
#target_link_libraries(domaintest nnpflib)

add_executable(create_domain create_domain.cpp)
target_link_libraries(create_domain domlib)

add_executable(pathfinder main.cpp)
target_link_libraries(pathfinder domlib nnpflib)
