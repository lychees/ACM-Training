import Data.List

p120 = sum [(a-1)`div`2*2*a | a <- [3..1000]]

s1 n m = ff n m 
    where
        ff n m | m == 0 = 1
               | m > n = 0
               | otherwise = maybe undefined id $ lookup (n, m) h
        h                  = map g [(x, y) | x <- [0..n], y <- [0..m]]
        g (n, m)           = ((n, m), gg n m)
        gg n m             = n * (ff (n-1) (m-1)) + (ff (n-1) (m)) 
 
p121 n = div total win 
    where 
        total = product [1..n+1]
        win   = sum $ map (s1 n) [x | x <- [0..(div n 2)]]

main = print $ p121 15