--Problem 1 [20 Points] Show how the single comprehension 
--[(x, y) | x <- [1, 2, 3], y <- [4, 5, 6]] with two generators 
--can be alternatively expressed using two comprehensions with 
--single generators. [Hint: make use of the library function 
--concat, and nest one comprehension within the other.]
--[(1,4),(1,5),(1,6),(2,4),(2,5),(2,6),(3,4),(3,5),(3,6)]

gen = drop 3 (x:xs)
  where
    (x:xs) = [x | x <- [1, 2, 3] ++ [y | y <- [4, 5, 6]]] 
