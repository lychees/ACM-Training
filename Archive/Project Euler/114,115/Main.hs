f n m = ff n m 
  where ff n m | n < m     = 1
               | n == m    = 2
               | otherwise = maybe undefined id $ lookup (n, m) h
        h                  = map g [(x, m) | x <- [m+1..n]]
        g (n, m)           = ((n, m), gg n m)
        gg n m             = 2 * (ff (n-1) m) - (ff (n-2) m) + (ff (n-m-1) m)

p114 = f 50 3
p115 = length $ takeWhile (<=10^6) [f i 50 | i <- [1..]]
main = print $ p115 + 1
