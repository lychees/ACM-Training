f n m = ff n m 
  where ff x y | n < 0     = 0
               | n == 0    = 1
               | otherwise = maybe undefined id $ lookup (x, y) h
                         h = map g [(x, m) | x <- [0..n]]
                  g (n, m) = ((n, m), gg n m)
                    gg n m = sum [ff (n-x) m | x <- m]

p117 = f 50 [1,2,3,4]
main = print $ p117