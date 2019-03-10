-- Start from the inside of the qualifier
-- [1 .. x] gives us all numbers up to the current x we are checking,
-- from these we filter out a list of factors
-- init to remove x from the list of factors
-- foldr to sum all the factors
-- Finally check to see if sum equals x, if it does we have a perfect number.
perfect :: [Integer]
perfect = [x | x <- [1 ..], foldr (+) 0 (init (filter (\y -> x `mod` y == 0) [1 .. x])) == x]