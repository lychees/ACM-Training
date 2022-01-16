import qualified Data.ByteString.Lazy.Char8 as P
import Data.ByteString.Builder
import qualified Data.ByteString.Builder.Prim as Prim
import System.IO
import Control.Monad.Trans.State
import Data.Maybe
 
--import Data.ByteString.Builder.Extra (flush) -- for interactive problems
import Control.Monad
import Data.List
import Data.Array.Unboxed
 
 
mainFun :: SP Builder
mainFun = do
  ~[t] <- getInts 1
  fmap mconcat $ replicateM t $ do
    ~[n, m] <- getInts 2
    pure $ putInts $ sort [ 0 | i <- [0..n-1], j <- [0..m-1]]
 
type SP = State [P.ByteString]
 
getNext :: Int -> SP [P.ByteString]
getNext = state . splitAt
 
getInts :: Int -> SP [Int]
getInts k = map (fst . fromJust . P.readInt) <$> getNext k
 
putInts :: [Int] -> Builder
putInts vs = let
  sepPrim = (,) ' ' Prim.>$<
    Prim.liftFixedToBounded Prim.char7 Prim.>*< Prim.intDec
  in  case  vs  of
  [] -> char7 '\n'
  x : xs -> intDec x <> Prim.primMapListBounded sepPrim xs <> char7 '\n'
 
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  inp <- P.getContents
  let  outp = evalState mainFun $ P.words inp
  P.putStr $ toLazyByteString outp