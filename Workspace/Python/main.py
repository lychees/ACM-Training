I = lambda: [int(x) for x in input().split()]

for t in range(int(input())):
    n, m = I()
    print(*sorted([max(x, n-1-x) + max(y, m-1-y) for x in range(n) for y in range(m)]))