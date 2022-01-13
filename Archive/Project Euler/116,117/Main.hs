f n m = ff n m 
  where ff n m | n < 0     = 0
               | n == 0    = 1
               | otherwise = maybe undefined id $ lookup (n, m) h
        h                  = map g [(x, m) | x <- [1..n]]
        g (n, m)           = ((n, m), gg n m)
        gg n m             = sum [ff (n-x) m | x <- m]

p116 = (f 50 [1,4]) + (f 50 [1,3]) + (f 50 [1,2]) - 3
p117 = f 50 [1,2,3,4]
main = print $ p117
