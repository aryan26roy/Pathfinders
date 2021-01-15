#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h> 
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <algorithm>

using namespace std;
namespace py = pybind11;
//Class for storing node info temporarily

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
//implementation of the breadth first search algorithm for pathfinding

Struct BFS(vector<vector<int>> grid,  int N, int M){
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
	else
		visited[i][j] = false;
	if(grid[i][j] == 1) //storing the source and destination in the class instances
	{
	source.row = i;
	source.col = j;
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
            q.push(CT(p.row - 1, p.col, p.dist + 1)); 	//pushing the adjacent node to the queue
            visited[p.row - 1][p.col] = true;			//marking it visited
            distgrid[p.row - 1][p.col] = p.dist + 1; 	//incrementing the distance by one and storing it in the distgrid
        } 
        if (p.row + 1 < N && visited[p.row + 1][p.col] == false) { 
            q.push(CT(p.row + 1, p.col, p.dist + 1)); 
            visited[p.row + 1][p.col] = true;
            distgrid[p.row + 1][p.col] = p.dist + 1;  
        } 
        if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false) { 
            q.push(CT(p.row, p.col - 1, p.dist + 1)); 
            visited[p.row][p.col - 1] = true; 
            distgrid[p.row][p.col - 1] = p.dist + 1; 
        } 
        if (p.col + 1 < M && visited[p.row][p.col + 1] == false) { 
            q.push(CT(p.row, p.col + 1, p.dist + 1)); 
            visited[p.row][p.col + 1] = true; 
            distgrid[p.row][p.col+1] = p.dist + 1; 
        } 
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

//int main() 
//{   int N = 4;
    //int M = 4; 	
    //vector<vector<char>> grid = { { '0', '*', '0', '1' }, 
      //                  	   { '*', 'd', '*', '*' }, 
        //                	   { '0', '*', '*', '*' }, 
         //               	   { '*', '*', '*', '*' } }; 
    //Struct out;  
    //out = BFS(grid, N, M); 
    //for (int i = 0; i<out.rows.size(); i++){
	//cout<<"{"<<out.rows[i]<<","<<out.cols[i]<<"}"<< "  ";
//}
    //cout<<endl;
    //out = DFS(grid, N, M);
    ///for (int i = 0; i<out.rows.size(); i++){
	//cout<<"{"<<out.rows[i]<<","<<out.cols[i]<<"}"<< "  ";
//}
    //return 0; 
//} 

std::map<std::string, py::array_t<int>>BFS_CPP(py::array_t<int> xs) {

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
    out = BFS(grid, dims[0], dims[1]); 
int jk = out.rows.size();
auto x = py::array(py::buffer_info(
        nullptr,            // Pointer to data
        sizeof(int),     // Size of one item 
        py::format_descriptor<int>::value, // Buffer format 
        1,          // number of dimensions? 
        {jk},  // Number of elements for each dimension 
        {sizeof(int) }  // Strides for each dimension
        ));
auto y = py::array(py::buffer_info(
        nullptr,            // Pointer to data
        sizeof(int),     // Size of one item 
        py::format_descriptor<int>::value, // Buffer format 
        1,          // number of dimensions? 
        {jk},  // Number of elements for each dimension 
        {sizeof(int) }  // Strides for each dimension
        ));
auto offset = py::array(py::buffer_info(
        nullptr,            // Pointer to data
        sizeof(int),     // Size of one item 
        py::format_descriptor<int>::value, // Buffer format 
        1,          // number of dimensions? 
        {2},  // Number of elements for each dimension 
        {sizeof(int) }  // Strides for each dimension
        ));
auto length = py::array(py::buffer_info(
        nullptr,            // Pointer to data
        sizeof(int),     // Size of one item 
        py::format_descriptor<int>::value, // Buffer format 
        1,          // number of dimensions? 
        {1},  // Number of elements for each dimension 
        {sizeof(int) }  // Strides for each dimension
        ));
auto form = py::array(py::buffer_info(
        nullptr,            // Pointer to data
        sizeof(int),     // Size of one item 
        py::format_descriptor<int>::value, // Buffer format 
        1,          // number of dimensions? 
        {1},  // Number of elements for each dimension 
        {sizeof(int) }  // Strides for each dimension
        ));
auto buf3 = offset.request();
    int *ptr3 = (int *) buf3.ptr;
auto buf = x.request();
    int *ptr1 = (int *) buf.ptr;
auto buf2 = y.request();
    int *ptr2 = (int *) buf2.ptr;
auto buf4 = length.request();
    int *ptr4 = (int *) buf4.ptr;
auto buf5 = form.request();
    int *ptr5 = (int *) buf5.ptr;
size_t idx = 0;
for (int i = 0; i < out.rows.size(); i++){
ptr1[idx] = out.rows[i];
ptr2[idx] = out.cols[i];
        idx++;}
idx = 0;
ptr3[idx] = 0;
ptr4[idx] = jk;
ptr5[idx] = 0;
idx++;
ptr3[idx] = jk;

  
  //for (int i = 0 ; i<out.rows.size(); i++){
  //builder.beginlist();
  //builder.integer(x[i]);
  //builder.integer(y[i]);
  //builder.endlist();
  //}
   
  //for (int i = 0 ; i<9; i++){
  
  //}
  string str = R"({
    "class": "RecordArray",
    "contents": {
        "x": {
            "class": "NumpyArray",
            "itemsize": 8,
            "format": "l",
            "primitive": "int64",
            "form_key": "node1"
        },
        "y": {
            "class": "NumpyArray",
            "itemsize": 8,
            "format": "l",
            "primitive": "int64",
            "form_key": "node2"
        }
    },
    "form_key": "node0"
})";
  std::map<std::string, py::array_t<int>> m{{str,form},{"Length",length},{"part0-node1-data", x}, {"part0-node2-data", y}, };

  return m;
}

PYBIND11_MODULE(BFS, m) {	//pybind11 declaration
    m.def("BFS_FIND", &BFS_CPP);
}
