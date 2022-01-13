import Data.Char
import Data.List

p119 = ([0]++) $ nub $ sort [a^b | a <- [2..200], b <- [2..20],
    (==a) $ sum  $ map (fromIntegral.digitToInt) $ show (a^b)]

main = print $ p119 !! 30