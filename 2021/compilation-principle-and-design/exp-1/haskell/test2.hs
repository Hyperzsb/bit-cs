matMul x y =
    let
        col m = [x|x:xs <- m]
        rights m = [xs|x:xs <- m,length(xs) > 0 ]
        rowMulMat r []  = []
        rowMulMat r m   = sum(zipWith (*) r (col m)):(rowMulMat r (rights m))
    in case x of
        [r]     -> [rowMulMat r y]
        (r:rs)  -> (rowMulMat r y):(matMul rs y)