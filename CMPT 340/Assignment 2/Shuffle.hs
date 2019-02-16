shuffle :: [a] -> [a] -> [a]
shuffle l1 [] = l1
shuffle [] l2 = l2
shuffle (x:xs) (y:ys) = [x, y] ++ shuffle xs ys

split :: [a] -> Int -> [[a]]
split l1 n = [(take n l1)] ++ [(drop n l1)]

outshuffle :: [a] -> [a]
outshuffle l1 = shuffle x y 
  where
  x = head (split l1 ((length l1) `div` 2))
  y = last (split l1 ((length l1) `div` 2))

inshuffle :: [a] -> [a]
inshuffle l1 = shuffle y x 
  where
  x = head (split l1 ((length l1) `div` 2))
  y = last (split l1 ((length l1) `div` 2))

nshuffle :: ([a] -> [a]) -> Int -> [a] -> [a]
nshuffle func num list
  | num == 0    = list
  | otherwise   = nshuffle func (num - 1) (func list)

howManyShuffles :: ([Integer] -> [Integer]) -> [Integer] -> [Integer] -> Integer
howManyShuffles func l1 l2 = delta func l1 l2 0
  where delta func l1 l2 n
          | l1 == l2    = n
          | otherwise   = delta func (func l1) l2 (n + 1)