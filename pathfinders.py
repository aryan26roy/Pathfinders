import build.DFS	#importing the compiled modules
import build.BFS
import build.dijkstra
import awkward as ak

class pathfinder: #wrapper class on python side
    def map(self,obs,dims,start,stop):
        for elem in obs:
            if elem[0]>dims[0]or elem[1]>dims[1]:
                print("Obstacle Outside Map")
                raise ValueError
        if start[0]>dims[0] or start[1]>dims[1] or stop[0]>dims[0] or stop[1]>dims[1]:
            print("Start/Stop Outside Map")
            raise ValueError
        if start in obs or stop in obs:
            print("Can't mark obstacles")
            raise ValueError
        grid = []
        for i in range(dims[0]):
            aee = []
            for j in range(dims[1]):
                if [i,j] in obs:
                    aee.append(0)
                    continue
                if [i,j] == start:
                    aee.append(2)
                    continue
                if [i,j] == stop:
                    aee.append(1)
                    continue
                else:
                    aee.append(4)
            grid.append(aee)
        for elem in grid:
            print(elem)
        self.grid = grid

    def mapras(self,grid):
        lg = len(grid[0])
        for elem in grid:
            if len(elem) != lg:
                print("Dimension Mismatch")
                raise ValueError
        self.grid = grid 	#the map
        self.rows = len(grid)	#metadata of the map
        self.cols = len(grid[0])
        
    def mark(self,start,stop): #function to mark the start and stop point on the map
        if start[0]>self.rows or start[1]>self.cols or start[0]>self.rows or start[1]>self.cols:
            print("Start/Stop outside the map")
            raise ValueError
        count = 0
        for elem in self.grid: #raise exception if there is no start/stop
            if 1 in elem:
                count += 1
            if 2 in elem:
                count += 1
        if count == 2:
            	raise ValueError 
        if self.grid[start[0]][start[1]] == 0 or self.grid[stop[0]][stop[1]] == 0:
            return print("Error: Cannot Mark Obstacles")	
        for i in range(self.rows):
    	    for j in range(self.cols):
    	        if i == start[0] and j == start[1]:
    		        self.grid[i][j] = 2
    	        if i == stop[0] and j == stop[1]:
    		        self.grid[i][j] = 1
        for elem in self.grid:
            print(elem)
    	
    def delete(self):	#function to delete the start and stop points
        for i in range(self.rows):
            for j in range(self.cols):
                if self.grid[i][j] == 2 or self.grid[i][j] == 1:
                    self.grid[i][j] =4
        print(self.grid)
        
    def findpath(self, algo):
        count = 0
        for elem in self.grid: #raise exception if there is no start/stop
            if 1 in elem:
            	count += 1
            if 2 in elem:
            	count += 1
        if count < 2 or count > 2:
            raise ValueError    	
        if algo == "BFS":
            f = build.BFS.BFS_FIND(self.grid)	#call the BFS algorithm
        if algo == "DFS":
            f = build.DFS.DFS_FIND(self.grid)	#call the DFS algorithm
        if algo == "DJK":
            f = build.dijkstra.interface(self.grid) #call the Dijkstra Algorithm
        form1 = list(f.keys())[-1]
        f.pop(form1)
        length1 = f['Length'][0]
        f.pop('Length')
        for key in f:
            f[key] = f[key].astype('int64')
        aa = ak.from_buffers(form1,length1,f)
        return aa
        
        

