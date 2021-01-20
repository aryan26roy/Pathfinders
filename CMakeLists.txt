# BSD 3-Clause License; see https://github.com/scikit-hep/awkward-1.0/blob/main/LICENSE

cmake_minimum_required(VERSION 3.1...3.16)
project(Pathfinders LANGUAGES CXX)


add_subdirectory(pybind11)


pybind11_add_module(dijkstra src/path.cpp)
pybind11_add_module(DFS src/dfsi.cpp)
pybind11_add_module(BFS src/bfsi.cpp)
set_target_properties(dijkstra DFS BFS PROPERTIES CXX_VISIBILITY_PRESET hidden)

