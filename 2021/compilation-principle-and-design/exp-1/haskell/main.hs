import Data.List (transpose)

rawDataFile = "/home/data.txt"

matrixMultiply :: [[Int]] -> [[Int]] -> [[Int]]
matrixMultiply matrixA matrixB = [ [ sum $ zipWith (*) x y | y <- transpose matrixB ] | x <- matrixA ]

initMatrix :: [String] -> ([[Int]], [[Int]])
initMatrix xs = (fun matrixA, fun matrixB)
    where
    matrixA = takeWhile (not . null) xs
    matrixB = tail $ dropWhile (not . null) xs
    fun = map (map read . words)

main = do
    rawData <- readFile rawDataFile
    let (matrixA, matrixB) = initMatrix $ lines rawData
    let matrixC = matrixMultiply matrixA matrixB
    print matrixC