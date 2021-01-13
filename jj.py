import build.dijkstra
import awkward as ak
arr = [[4,4,0,4,4,4],
    [4,4,0,1,4,4],
    [4,4,0,4,4,4],
    [4,4,4,4,2,4]]
a = build.dijkstra.interface(arr)
form = list(a.keys())[-1]
print(form)
a.pop(form)
length = a['Length'][0]
a.pop('Length')
print(a)
