import Data.List (transpose)

(*.) :: [[Int]] -> [[Int]] -> [[Int]]
a *. b = [ [ sum $ zipWith (*) x y | y<- transpose b] | x<-a ]

readMatrix :: [String] -> ([[Int]], [[Int]])
readMatrix xs = (f a, f b)
    where
    a = takeWhile (not . null) xs
    b = tail $ dropWhile (not . null) xs
    f = map (map read . words)

main :: IO ()
main = do
    s <- getContents
    let (a, b) = readMatrix $ lines s
        c  = a *. b
        c1 = map (unwords . map show) c
        c2 = unlines c1
    putStr c2