import qualified Data.ByteString.Lazy.Char8 as P
import qualified Data.ByteString.Builder as B
import Data.ByteString.Builder.Prim
import System.IO

import Control.Monad
import Control.Monad.Trans.State
import Control.Monad.Trans.Class
import Data.Semigroup

import Data.List
import Data.Bits
-- import Data.Vector.Unboxed
import qualified Data.Map as M
import Data.Maybe (fromMaybe)
import Control.Monad ((<$!>))

type SP = StateT [P.ByteString]
type SIO = SP IO

getNext :: Monad m => Int -> SP m [P.ByteString]
getNext = state . splitAt

getInts :: Monad m => Int -> SP m [Int]
getInts k = do
    vs <- getNext k
    pure [v | Just (v, _) <- map P.readInt vs]

putInts :: [Int] -> SIO ()
putInts li = let
    spacePrim = (,) ' ' >$< liftFixedToBounded char7 >*< intDec
    in  lift $ B.hPutBuilder stdout $ case  li  of
    [] -> B.char7 '\n'
    x : xs -> B.intDec x <> primMapListBounded spacePrim xs <> B.char7 '\n'

{----------}

data Tree a = E | T (Tree a) a (Tree a) deriving (Show)

ins :: (Ord a) => Tree a -> a -> Tree a
ins E x = T E x E
ins s@(T l y r) x
    | x < y     = T (ins l x) y r
    | x > y     = T l y (ins r x)
    | otherwise = s

gao :: (Ord a) => Tree a -> [a]
gao E = []
gao s@(T l x r)
    | otherwise = (gao l) ++ [x] ++ (gao r) 

main :: IO ()
main = (P.words <$> P.getContents >>=) $ evalStateT $ do
    [n] <- getInts 1
    a <- getInts n
    putInts $ gao $ foldl ins E a
