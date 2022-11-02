#show him the test error you are getting
#how do I do the dynamic version? Show him your current attempt
import numpy as np
import sys

coins = [1,5,10,25]
#coins = [1, 2, 5]
calls = 0
reads = 0
matrix = []
def initializeMatrix(n):
   global matrix
   matrix = []
   for j in range(n+1):
      matrix.append([])
      for i in range(len(coins)+1):
         matrix[j].append(None)

#initializeMatrix(10)
#print(matrix)
''' Making Change based on the either or recursion
    slide 6 06-coinsPA lecture
'''
def mkChangeDC(n, c):
   global calls
   calls+=1

   left = None
   if coins[c] > n:
      left = 0
   elif coins[c] == n:
      left = 1
   else:
      if c < 1 and n % coins[c] == 0:
         left = 1
      else:
         left = mkChangeDC(n-coins[c], c)

   right = None
   if c < 1:
      right = 0
   else:
      right = mkChangeDC(n, c-1)

   return left+right

''' Dynamic Programming version of mkChangeDC'''     
def mkChangeDP(cap):
   global matrix
   # increment global reads with 1 if you do 1 read, and with 2 if you do 2
   initializeMatrix(cap)

   return runDP(cap, len(coins)-1)
   #return 0

def runDP(n, c):
   global matrix
   global reads

   left = None
   if coins[c] > n:
      left = 0
      
   elif coins[c] == n:
      left = 1
   else:
      if c < 1 and n % coins[c] == 0:
         left = 1
      else:
         if c >= 0 and n-coins[c] >= 0 and matrix[n-coins[c]][c] != None:
            left = matrix[n-coins[c]][c]
            reads += 1
         else:
            left = runDP(n-coins[c], c)
            matrix[n-coins[c]][c] = left

   right = None
   if c < 1:
      right = 0
   else:
      if c-1 >= 0 and matrix[n][c-1] != None:
         right = matrix[n][c-1]
         reads += 1
      else:
         right = runDP(n, c-1)

   matrix[n][c] = left+right

   return left+right

if __name__ == "__main__":
   c = len(coins)-1
   print()
   print("Making change with coins:", coins)

   # performance data: [[n, complexity], ... ]
   dataDC  = []
   dataDP  = []
   
   for n in range(200,2050,200):
      print()
      print("Amount:",n)
      
      calls = 0
      ways = mkChangeDC(n,c)
      print("DC", ways, calls, "calls")
      dataDC.append([n,calls])
                        
      reads = 0
      ways = mkChangeDP(n+1)
      print("DP", ways, reads, "reads")
      dataDP.append([n,reads])
      
      
   print("dataDC:", dataDC)
   np.savetxt('dataDC', dataDC, delimiter=',', fmt='%d')

   
   print("dataDP:", dataDP)
   np.savetxt('dataDP', dataDP, delimiter=',', fmt='%d')
   