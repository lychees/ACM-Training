import Data.List

parse :: String -> [Int]
parse = read . ('[':) . (++ "]")


f a d n m = ff a d n m
    where ff a d n m | m < 0 || (m >= length (head a)) = maxBound :: Int                     
                     | n == 0 = (head a) !! m                     
                     | otherwise = maybe undefined id $ lookup (d, n, m) h 
          h                      = map g [(dd, x, y) | dd <- [0..2], x <- [0..80], y <- [0..80]]
          g (d, n, m)            = ((d, n, m), (gg d n m) + (a !! n !! m))
          gg d n m | n == (length a - 1) = ff a 0 (n-1) m
                   | d == 0 = minimum [ff a 0 (n-1) m, ff a 1 n (m-1), ff a 2 n (m+1)] 
                   | d == 1 = minimum [ff a 0 (n-1) m, ff a 1 n (m-1)]
                   | d == 2 = minimum [ff a 0 (n-1) m, ff a 2 n (m+1)]
                                      
main = do
    s <- readFile "in.txt"
    let a = transpose $ map parse.lines $ s
        n = (length a) - 1
        m = (length $ head a) - 1
    print $ minimum $ map (f a 0 n) [0..m]
