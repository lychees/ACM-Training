import sys
from atcoder.maxflow import MFGraph
I = lambda: [int(x) for x in input().split()]

n, m = I()
s = 2*n
t = s+1
G = MFGraph(t+1)
a = I()
b = I()
z = 0

a1 - a2n - 1        
(a1 - a2n - k)!  (k-1)!


 a2n! (k-1)!
 


for i in range(n):
    bb = abs(b[i])
    z += bb
    G.add_edge(i, i+n, a[i] + bb)
    bb *= 2
    if (b[i] < 0):
        G.add_edge(i+n, t, bb)
    else:
        G.add_edge(s, i, bb)

for i in range(m):
    x, y = I()
    x -= 1
    y -= 1
    G.add_edge(x+n, y, sys.maxsize)
    G.add_edge(y+n, x, sys.maxsize)

print(z-G.flow(s,t))