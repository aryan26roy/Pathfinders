// BSD 3-Clause License; see https://github.com/scikit-hep/awkward-1.0/blob/main/LICENSE

#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h> 
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#define infinity 9999
#include "awkward/builder/ArrayBuilder.h"
#include "awkward/builder/ArrayBuilderOptions.h"
#include "awkward/kernels.h"
#include <algorithm>

namespace py = pybind11;
namespace ak = awkward;
using namespace std;

class CT{	
public:
	int row;
	int col;
	int dist;
	CT(int x, int y, int D): row(x), col(y), dist(D){}
};
//struct to return data from pathfinding algorithm

struct output{
	vector<int> rows;
	vector<int> cols;
	};
	
typedef struct output Struct;

Struct DJK(vector<vector<int>> grid,  int N, int M){
Struct s;
int distgrid[N][M];//for storing the distance of each node from the source
CT source(0,0,0);//the source
CT dest(0,0,0);//the destination
bool visited[N][M];

for (int i = 0; i< N; i++){	
	for(int j = 0; j < M; j++){
	if (grid[i][j] == 0){		//marking the obstacles as visited 
		visited[i][j] = true;
		distgrid[i][j] = 1000;}
	else{
		visited[i][j] = false;
		distgrid[i][j] = infinity;}
	if(grid[i][j] == 1) //storing the source and destination in the class instances
	{
	source.row = i;
	source.col = j;
	//visited[i][j] = true;
	}
	if(grid[i][j] == 2)
	{
	dest.row = i;
	dest.col = j;
	}	
}	
}

queue<CT> q;	//queue for breadth first search
q.push(source);
distgrid[source.row][source.col] = 0;
visited[source.row][source.col] = true; //marking the source as visited

while(!q.empty()){
	CT p = q.front();
	q.pop();
        if (p.row - 1 >= 0 && visited[p.row - 1][p.col] == false) { 
        if(p.dist+1 < distgrid[p.row-1][p.col]){
            q.push(CT(p.row - 1, p.col, p.dist + 1)); 	//pushing the adjacent node to the queue
            distgrid[p.row - 1][p.col] = p.dist + 1; 	//incrementing the distance by one and storing it in the distgrid
        } }
        if (p.row + 1 < N && visited[p.row + 1][p.col] == false) { 
        if(p.dist+1 < distgrid[p.row+1][p.col]){
            q.push(CT(p.row + 1, p.col, p.dist + 1)); 
            distgrid[p.row + 1][p.col] = p.dist + 1;  
        } }
        if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false) { 
        if(p.dist+1 < distgrid[p.row][p.col-1]){
            q.push(CT(p.row, p.col - 1, p.dist + 1)); 
            distgrid[p.row][p.col - 1] = p.dist + 1; 
        } }
        if (p.col + 1 < M && visited[p.row][p.col + 1] == false) { 
        if(p.dist+1 < distgrid[p.row][p.col+1]){
            q.push(CT(p.row, p.col + 1, p.dist + 1)); 
            distgrid[p.row][p.col+1] = p.dist + 1; 
        } }
}

int srow = dest.row;	
int scol = dest.col;
vector <int> path_col;	//output vector for the column values of the path  
vector <int> path_row; //output vector for the row values of the path
path_row.push_back(srow); //starting the path from the source
path_col.push_back(scol);

while (srow != source.row || scol != source.col){ //working back from the destination to the source as each node had a weight of 1
	if (distgrid[srow+1][scol] == distgrid[srow][scol]-1){
	srow = srow+1;
	scol = scol;
	path_row.push_back(srow); //adding the column and row values to the vectors
	path_col.push_back(scol);
	continue;}
	if (distgrid[srow][scol+1] == distgrid[srow][scol]-1){
	srow = srow;
	scol = scol+1;
	path_row.push_back(srow);
	path_col.push_back(scol);
	continue;}
	if (distgrid[srow-1][scol] == distgrid[srow][scol]-1){
	srow = srow-1;
	scol = scol;
	path_row.push_back(srow);
	path_col.push_back(scol);
	continue;}
	if (distgrid[srow][scol-1] == distgrid[srow][scol]-1){
	srow = srow;
	scol = scol-1;
	path_row.push_back(srow);
	path_col.push_back(scol);
	continue;}}
s.rows = path_row;
s.cols = path_col;
return s;
}

std::shared_ptr<ak::Content> interface(py::array_t<int> xs) {

	 py::buffer_info info = xs.request(); 	//requesting buffer information of the input
    auto ptr = static_cast<int *>(info.ptr);	//pointer to the initial value
    vector<int> dims;				//the dimensions of the input array
    int n = 1;
    for (auto r: info.shape) {
      dims.push_back(r);
      n *= r;					//total number of elements
    }
    vector<vector<int>> grid = {{1,2,3},{1,2,3}};
    grid.clear();
    vector <int> too;      
    for (int i = 0; i < dims[0]; i++) { 
        // Vector to store column elements 
        vector <int> too; 
  
        for (int j = 0; j < dims[1]; j++) { 
            too.push_back(*ptr); 
            ptr++; 
        } 
  
        // Pushing back above 1D vector 
        // to create the 2D vector 
        grid.push_back(too); 
    } 
    Struct out;  
    out = DJK(grid, dims[0], dims[1]); 



 int x[out.rows.size()];
 int y[out.cols.size()];
 std::copy(out.rows.begin(),out.rows.end(),x);
 std::copy(out.cols.begin(),out.cols.end(),y);
 
  ak::ArrayBuilder builder(ak::ArrayBuilderOptions(1024, 2.0));
  
  for (int i = 0 ; i<out.rows.size(); i++){
  builder.beginlist();
  builder.integer(out.x[i]);
  builder.integer(out.y[i]);
  builder.endlist();
  }
   
  //for (int i = 0 ; i<9; i++){
  
  //}
  
  return builder.snapshot();
}


PYBIND11_MODULE(dijkstra, m) {
  // Ensure dependencies are loaded.
  py::module::import("awkward");

  m.def("interface", &interface);
}
