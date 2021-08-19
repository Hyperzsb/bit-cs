-- @Author: DarkDawn
-- @Date:   2020-02-22 13:54:59
-- @Last Modified by:   DarkDawn
-- @Last Modified time: 2020-02-23 14:40:25

import Data.Time
import Text.Printf
import Data.List (SplitOn)

num = 10
rep_num = 5
in_PATH = "data.txt"
out_PATH = "result.txt"

trans:: [[a]]->[[a]] 
trans ([]:_) = [] 
trans x = (map head x) : trans (map tail x) 

mulMatrix :: Num a => [[a]] -> [[a]] -> [[a]]
mulMatrix mA mB = [ [ sum $ zipWith (*) mAr mBc | mBc <- (trans mB) ] | mAr <- mA ]

rep_mul :: Int -> [[Int]] -> [[Int]] -> IO([[Int]])
rep_mul i aM bM = do
    let cM = mulMatrix aM bM
    if i == 0 then do
        return cM
    else do
        tmp <- rep_mul (i-1) aM bM
        return tmp

runMain :: Int -> [[Int]] -> [[Int]] -> IO([[Int]])
runMain i aM bM = do
    cM <- (rep_mul rep_num aM bM)
    -- print (cM!!0!!0)
    return cM

round' :: Int -> [[[Char]]] -> IO(([Char],Float))
round' i context = do
    start <- getCurrentTime
    let n = read (context!!0!!0) :: Int
    let aM = [[read x :: Int | x <- y] | y <- (drop 1 (take (n+1) context))]
    let bM = [[read x :: Int | x <- y] | y <- (drop (n+2) (take (n*2+2) context))]
    cM <- (runMain i aM bM)
    let context' = drop (n*2+2) context
    let m = [[(show x)++" " | x <- y]++["\n"] | y <- cM]
    let output = (show n) ++ "\n" ++ (concat (concat m))
    end <- getCurrentTime
    let tim = (1000 * (realToFrac (diffUTCTime end start) ::Float))
    -- print tim
    printf "Test %d: %.2f ms\n" (num-i) tim
    if i == 0 then do
        return (output, tim)
    else do
        (tmp_output, tmp_tim) <- round' (i-1) context'
        return (output ++ tmp_output,tim + tmp_tim)

main = do
    print "Matrix multiplication implemented by Haskell."
    cont <- readFile in_PATH
    let context = [splitOn " " x | x <- (splitOn "\n" cont)]
    start <- getCurrentTime
    (output, all_time) <- round' (num-1) context
    -- end <- getCurrentTime
    -- print (take 50 output)
    writeFile out_PATH output
    mid <- getCurrentTime
    writeFile out_PATH output
    end <- getCurrentTime
    printf "Average Time: %.2f ms\n" (all_time / (fromIntegral num))
    let mulandwrite' = (1000 * (realToFrac (diffUTCTime mid start) ::Float))
    -- print mulandwrite'
    let write' = (1000 * (realToFrac (diffUTCTime end mid) ::Float))
    -- let mul' = (mulandwrite' - write')
    printf "Calculate and WriteFile Time: %.2f ms\n" mulandwrite'
    printf "WriteFile Time: %.2f ms\n" write'
    printf "Real Average Time: %.2f ms\n" ((mulandwrite' - write') / (fromIntegral num) / (fromIntegral rep_num))