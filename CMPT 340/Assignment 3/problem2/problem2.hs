altMap :: [a -> a] -> [a] -> [a]
altMap [] x           = x
altMap f []           = []
altMap (x:xs) (y:ys)  = x y : altMap (xs ++ [x]) ys

luhn :: [Int] -> Bool
luhn = (h . g . f)
  where
    h z
      | z `rem` 10 == 0 = True
      | z == 0          = False 
      | otherwise       = False

    g []      = 0
    g (y:ys)  = y + g ys

    f x = (altMap[(greater)] . altMap[(\x -> x), (*2)]) (reverse x)

    greater y
      | y > 9     = y - 9
      | otherwise = y