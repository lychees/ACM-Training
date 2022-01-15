import Data.List

parse :: String -> [Int]
parse = read . ('[':) . (++ "]")


f a n m = ff a n m 
    where ff a n m | n < 0 || m < 0 = maxBound :: Int
                   | n == 0 && m == 0 = head $ head a
                   | otherwise = maybe undefined id $ lookup (n, m) h 
          h                    = map g [(x, y) | x <- [0..n], y <- [0..m]]
          g (n, m)             = ((n, m), gg n m)
          gg n m               = (min (ff a (n-1) m) (ff a n (m-1))) + (a !! n !! m)

main = do
    s <- readFile "in.txt"
    let a = map parse.lines $ s
    print $ f a (length a - 1) ((length $ head a) - 1)
