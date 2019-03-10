--A positive integer is perfect if it equals the sum of all of its factors, excluding 
--the number itself.  For example, 6, 28, 496, and so on.  Define a list comprehension
--to generate an infinite list of perfect numbers.  Do not make external function calls.  
--Try to be efficient in the search for factors. [Hint: One way to do this is by (1) 
--placing a comprehension for finding factors in a qualifier of the the top-level comprehension, 
--(2) adding the factors using an appropriate higher-order function, and (3) 
--checking to see whether the sum equals the number.]

perfect :: [Integer]
perfect = [x | x <- [1 ..], foldr (+) 0 (init (filter (\y -> x `mod` y == 0) [1 .. x])) == x]
--x == (foldr (+) (filter (== 0) (x `mod` y)))
--foldr (+) 0 (init (filter (\x -> 6 `mod` x == 0) [1 .. 10]))