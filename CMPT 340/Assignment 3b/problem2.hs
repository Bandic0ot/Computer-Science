--A triple (x, y, z) of positive integers is pythagorean if x2 + y2 = z2.  Using a 
--list comprehension, define a function pyth which returns the list of all pythagorean 
--triples whose components are at most a given limit.  For example, function call pyth
--10 should return [(3, 4, 5), (4, 3, 5), (6, 8, 10), (8, 6, 10)]

pyth :: Int -> [(Int, Int, Int)]
pyth n = [(x, y, z) | x <- [1 .. n], y <- [1 .. n], z <- [1 .. n], (x * x) + (y * y) == (z * z)]