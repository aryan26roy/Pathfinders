# PATHFINDERS
A library containing pathfinding algorithms implemented and compiled in C++ and binded and exposed to Python. It enabled fast execution of these pathfinding algorithms in Python.
 
 ## How To Install
 To install the library, simply clone this repository and go to the folder where it has been cloned and type the following commands.
 ```bash
 cmake -S . -B build
 cmake --build build
 ```
 ## How To USe
 To use the library simply import the wrapper class from the folder where it was built:
 ```python
 import pathfinders
 ```
 Then the class can be instantiated like this:
 ```python
 finder = pathfinders.pathfinder()
 ```
 ### Inputing A Map
 In the pathfinders library there are two ways to input a map.
 * Rasterized Form
 * Obstacles form

To input the map in the rasterized form, assuming the map is in 2-Dimensional form in the variable map:
```python
finder.mapras(map)
```
To input the map in the obstacles form, a 2D list of the coordinates of the obstacles on the map need to be provided along with the shape and the start and stop points:
```python
finder.map(obs,dims,start,stop)
```
### Map Manipulation
The library provides two simple functions to modify the map, they are:
* Mark
* Delete
  
The Mark function can be used to mark a new set of start and stop points:
```python
finder.mark(start,stop)
```
The delete function can be used to delete the current start and stop points on the map:
```python
finder.delete()
```
### Finding The Shortest Path
Once the start and stop points have been set, the findpath function can be used to find the shortest path between them.
The function returns the path as an Awkward Record Array which enables the user to manipulate the path using the functionalities provided by [Awkward Array Library](https://github.com/scikit-hep/awkward-1.0).
The different algorithms provided in the library are:
* Breadth-First Search
* Depth-First Search
* Dijkstra's Algorithm
* A-Star Algorithm (To be added)

For Breadth-First Search:
```python
path = finder.findpath("BFS")
```
For Depth-First Search:
```python
path = finder.findpath("DFS")
```
For Dijkstra's Algorithm:
```python
path = finder.findpath("DJK")
```



