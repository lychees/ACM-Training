{-# LANGUAGE BangPatterns #-}
import qualified Data.ByteString.Lazy.Char8 as P
import Data.ByteString.Builder
import qualified Data.ByteString.Builder.Prim as Prim
import System.IO
import Control.Monad.Trans.State
import Data.Maybe
import Data.Bits
 
--import Data.ByteString.Builder.Extra (flush) -- for interactive problems
import Control.Monad
import Data.List
--import Data.Array.Unboxed
 
 
prefMins :: Ord t => (a -> t) -> [a] -> [t]
prefMins f li = tail $ scanl' min (f $ head li) $ map f li

sqr x = x*x

pow x n | (n==0) = 1
        | ((mod n 2) == 0) = sqr $ pow x $ div n 2
        | otherwise = x * (pow x (n-1))

gao (a, k) | k == 0 = 0
           | (length a) == 1 = ((pow 10 (head a)) * k)
           | otherwise = ((gao ((tail a), (k - d))) + ((pow 10 (head a)) * d)) where d = (min (k) ((pow 10 ((a !! 1) - (head a))) - 1))      

binomial x y =div (prodxy (y+1) x) (prodxy 1 (x-y))
prodxy x y=product[x..y]
fun m n=sum[binomial (k+a) (k-a)|a<-[0..div (n+1) (m+1)],let k=1-a*m+n]

{-}
f n m | n < m     = 1
      | n == m    = 2
      | otherwise = 2 * (f (n-1) m) - (f (n-2) m) + (f (n-m-1) m)
-}

{-
f :: Int -> Int -> Int
f n m = ff n m 
  where ff x y    = maybe undefined id $ lookup (x, y) h
        h         = map g [(x, y) | x <- [0..n], y <- [0..m]]
        g (n, m)  = ((n, m), gg n m)
        gg n m | n < m     = 1
               | n == m    = 2
               | otherwise = (ff (n-1) m) + (ff (n-m) m)
-}

f :: Int -> [Int] -> Int
f n m = ff n m 
  where ff x y    = maybe undefined id $ lookup (x, y) h
        h         = map g [(x, m) | x <- [-40..n]]
        g (n, m)  = ((n, m), gg n m)
        gg n m | n < 0    = 0
               | n == 0   = 1
               | otherwise = sum [ff (n-x) m | x <- m]

--p114 = f 50 3
-- p115 = (+1)$length$takeWhile (<10^6) [f i 50 |i<-[1..]]
p117 = f 50 [1,2,3,4]
main = print $ p117