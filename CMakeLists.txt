
cmake_minimum_required(VERSION 3.1...3.16)
project(Pathfinders LANGUAGES CXX)


add_subdirectory(pybind11)


pybind11_add_module(_dijkstra src/path.cpp)
pybind11_add_module(_dfs src/dfsi.cpp)
pybind11_add_module(_bfs src/bfsi.cpp)
set_target_properties(_dijkstra _bfs _dfs PROPERTIES CXX_VISIBILITY_PRESET hidden)

