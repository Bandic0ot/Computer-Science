fastExp1 :: Integer -> Integer -> Integer
fastExp1 n k = 
  if(even k) then
    (n ^ (k `div` 2)) ^ 2
  else
    n * n ^ (k - 1)

fastExp2 :: Integer -> Integer -> Integer
fastExp2 n k  | even k    = (n ^ (k `div` 2)) ^ 2
              | otherwise = n * n ^ (k - 1)

fastExp3 :: Integer -> Integer -> Integer
fastExp3 n k = (n ^ (k `div` 2)) ^ 2
fastExp3 n k = n * n ^ (k - 1)
