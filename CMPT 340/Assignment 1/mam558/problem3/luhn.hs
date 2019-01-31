luhnDouble :: Integer -> Integer
luhnDouble x 
  | (double x) > 9  = (double x) - 9
  | (double x) < 9  = double x  --Because the result of a doubled integer can never be 9 we don't need to check for equal to 9.

double x = x * 2

luhn :: Integer -> Integer -> Integer -> Integer -> Bool
luhn a b c d 
  | ((luhnDouble a + b + luhnDouble c + d) `rem` 10) == 0   = True 
  | otherwise                                               = False