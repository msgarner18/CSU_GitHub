import sys

#global variable, keeping track in dfs whether a cycle was found
cyclic = False 

# Don't change helper functions
#   read, dump, white, dfsInit

def read(fnm):
  """  
  read file fnm containing a graph into a dictionary and return the dictionary
  each line has a nodeName followed by its adjacent nodeNames
  """
  f = open(fnm)
  gr = {} #graph represented by dictionary
  for line in f:
    #strip removes space to left and right of string
    #split turns a string into a list seperated by spaces
    l =line.strip().split(" ")
    # ignore empty lines
    if l==['']:continue#continue=immediately return to beginning of for loop
    # dictionary: key: nodeName  value: (color, adjacency List of names)
    gr[l[0]]= ('white',l[1:])
  return gr

#prints graph gr
def dump(gr):
  print("Input graph: nodeName (color, [adj list]) dictionary ")
  for e in gr:
    print(e, gr[e])

def white(gr) :
  """
   paint all gr nodes white
  """
  for e in gr :
    gr[e] = ('white',gr[e][1])

def dfsInit(gr,root):
   """
   dfs keeps track of cycles in global cyclic
   call dfs with appropriate initial parameters
   """ 
   global cyclic
   cyclic = False
   visited = dfs(gr,root,[])
   return (visited,cyclic)

# Work on bfs, dfs 

def bfs(gr,q):
  """
  q is an array representing a queue of (node,distance) pairs
  initially queue q contains 1 (node,distance) pair: (root,0)
  (see the call to bfs in main)
  breadth first search gr from the root, keep track of distance
  from root
  return the queue of all (node, distance) pairs visited
  """
  
  visited = []
  while len(q) > 0:
    #a node is popped off queue and turned red
    node = q.pop(0)
    cur = node[0]
    gr[cur] = ('black',gr[cur][1])
    visited.append(node)

    # current node checks through each of its neighbor nodes
    for neighbor in gr[cur][1]:
      if gr[neighbor][0] == "white":
        gr[neighbor] = ('grey',gr[neighbor][1])
        q.append((neighbor, node[1] +1))

  return visited

#def backtrack():

def dfs(gr,r,visited):

    """  
    depth first search gr from root r for cycles,
    when a cycle is detected, set global cyclic to True
    return array of nodes visited, i.e. append node to visited
    when encountering it for the first time (i.e. when it is white)
    """
    """
    first check
    check next node:
    1) there is no next node
      set root to black, attempt to backtrack if isGrey, set cyclic to true break
    2) next node is white
      set root to grey, set root to white node if isGrey, set cyclic to true break
    3) next node is grey or black(else)
      set isGrey to true
      run loop again, except check next node

    backtrack code:
    set root to whichever grey node that is pointing to root
    if there is no node pointing to root, set root to black and end program

    root = a
    check node b
    b is white
    root = b
    root is set to grey
    root has no neighbors
    root is set to black
    root checks for grey neighbors
    root is set to first/only grey neighbor a
    check node b
    node b is black, so continue to next neighbor
    check node c
    node c is white
    set root to node c
    root is set to grey
    c checks node d
    node d is white
    root is set to node d
    root is set to grey
    d checks node e
    e is white
    root is set to node e
    root is set to grey
    e checks node a
    a is grey
    no other branches available. All nodes here are either black or grey, so this node has been fully explored
    e is set to black
    e checks for grey node that is pointing to it
    root is set to d
    d checks node e
    e is black, d continues
    d checks f
    f is white
    d is set to grey
    root is set to f
    f checks g
    g is white
    f is set to grey
    root is set to g
    g has no neighbors
    g is set to black
    g checks for grey neighbors pointing to it
    g finds f and sets root to f
    f's only neighbor is black,
    f checks for grey neighbors pointing to it
    f finds d and sets root to d
    d has only black neighbors, and so backtracks once
    c only has black neighbors, and so backtracks once which also sets c to black
    a has only black neighbors, and so attempts to backtrack, but fails
    program ends
    black neighbors are added to visited list
    white = start
    grey = currently being explored
    black = finished being explored
    gr = adjacency list 
    r = root
    visited = return value: list of nodes visited
    Algorithm:
    for each neighbor of root,
    check color of neighbors
    if any neighbor is white, change root's color to grey and set root to neighbor break
    else, if no white neighbors, attempt to backtrack
    if backtracking doesn't work, set root to black and end program

    Backtrack code:

    """
    # r starts as 'a'
    global cyclic
    greyQueue = []
    visited.append(r)
    while True:
      isGrey = False#this keeps track of whether we backtracked because a grey node was seen, or a black node was seen
      isWhite = False#this is set to true if a white node was found
      #neighbor in list of r's neighbors
      for neighbor in gr[r][1]:
        #if the color of next neighbor is white
        if gr[neighbor][0] == "white":
          visited.append(neighbor)
          if isGrey:
            cyclic = True
          isWhite = True
          #set root to grey and set root to neighbor
          gr[r] = ('grey', gr[r][1])
          greyQueue.append(r)
          r = neighbor
          break
        if gr[neighbor][0] == "grey":
          isGrey = True

      #if there was no next neighbor
      if not isWhite:
        if isGrey:
            cyclic = True
        #set root to black, attempt to backtrack
        gr[r] = ('black', gr[r][1])
      
        #backtrack code- set root to first grey node pointing to root
        if len(greyQueue) > 0:
          r = greyQueue.pop()
        else:
          return visited

if __name__ == "__main__":
  
  print(sys.argv[0])      # program name
  gr = read(sys.argv[1])  # graph file name
  root = sys.argv[2]      # root node
  print("BFS")
  dump(gr)
  print("Root node:", root)
  # don't need grey for bfs
  gr[root] = ('black',gr[root][1])
  q = bfs(gr,[(root,0)])
  print("BFS queue: (node name, distance) pairs")
  print(q)
  print("END BFS")
  print()
  white(gr)
  print("DFS")
  dump(gr)
  print("Root node", root)
  vis,cyc = dfsInit(gr,root)
  print("DFS from root visited:")
  print(vis)
  if cyc:
    print("graph with root",root,"is cyclic")
  else:
    print("graph with root",root,"is not cyclic")
  print("END DFS")