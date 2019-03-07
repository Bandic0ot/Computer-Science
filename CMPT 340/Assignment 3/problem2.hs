altMap :: [a -> a] -> [a] -> [a]
altMap [] x           = x
altMap f []           = []
altMap (x:xs) (y:ys)  = x y : altMap (xs ++ [x]) ys

luhn :: [Int] -> Bool
luhn = altMap [(*2)]