--unfold :: (a -> Bool) -> (a -> b) -> (a -> a) -> a -> [b]
unfold p h t x 
  | p x        = []
  | otherwise  = h x : unfold p h t (t x)

--mapf :: ([a] -> a) -> [a] -> [a]
--mapf f (x:xs) = unfold (== []) f x

