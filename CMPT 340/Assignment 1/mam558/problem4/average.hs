averageThree :: Integer -> Integer -> Integer -> Integer
averageThree x y z = (x + y + z) `div` 3

howManyAboveAverage :: Integer -> Integer -> Integer -> Integer
howManyAboveAverage x y z = calc x + calc y + calc z
  where 
  calc n
    | n > averageThree x y z  = 1
    | n <= averageThree x y z = 0

averageThreeInOne :: (Integer -> Integer -> Integer) -> Integer
averageThreeInOne (x, y, z) = averageThree fst snd 1