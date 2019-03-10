unfold :: (a -> Bool) -> (a -> b) -> (a -> a) -> a -> [b]
unfold p h t x 
  | p x        = []
  | otherwise  = h x : unfold p h t (t x)

mapf :: Eq a => (a -> b) -> [a] -> [b]
mapf f = unfold (== []) (f . head) (tail)

iteratef f x = unfold (> 100) f f x

repHalve l = unfold (== []) (takehalf) (drophalf) l
  where 
    takehalf x
      | (even . length) x   = take ((div . length) x 2) x
      | otherwise           = take (((div . length) x 2) + 1) x
    drophalf y
      | (even . length) y   = drop ((div . length) y 2) y
      | otherwise           = drop (((div . length) y 2) + 1) y

