shuffle :: [a] -> [a] -> [a]
shuffle l1 [] = l1
shuffle [] l2 = l2
shuffle (x:xs) (y:ys) = [x, y] ++ shuffle xs ys

split :: [a] -> Int -> [[a]]
split l1 n = [(take n l1)] ++ [(drop n l1)]