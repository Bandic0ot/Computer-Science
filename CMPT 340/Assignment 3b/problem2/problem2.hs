-- Use pythagorean theorem to check if the tuple is pythagorean.
-- Separate generators are used to check every combination of numbers up to n.
pyth :: Integer -> [(Integer, Integer, Integer)]
pyth n = [(x, y, z) | x <- [1 .. n], y <- [1 .. n], z <- [1 .. n], (x * x) + (y * y) == (z * z)]