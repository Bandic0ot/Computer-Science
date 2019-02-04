averageThree :: Integer -> Integer -> Integer -> Integer
averageThree x y z = (x + y + z) `div` 3

howManyAboveAverage :: Integer -> Integer -> Integer -> Integer
howManyAboveAverage x y z = calc x + calc y + calc z
  where 
  calc n
    | n > averageThree x y z  = 1
    | otherwise               = 0

averageThreeInOne :: (Integer, Integer, Integer) -> Integer
averageThreeInOne (x, y, z) = averageThree x y z

orderTriple :: (Integer, Integer, Integer) -> (Integer, Integer, Integer)
orderTriple (x, y, z)
    | howManyAboveAverage x y z == 1  = largest
    | otherwise                       = smallest
      where largest
              | x > averageThreeInOne(x, y, z)  = orderTriple (y, z, x)
              | y > averageThreeInOne(x, y, z)  = orderTriple (x, z, y)
              | x > y                           = (y, x, z)
              | otherwise                       = (x, y, z)
            smallest
              | z < averageThreeInOne(x, y, z)  = orderTriple (z, x, y)
              | y < averageThreeInOne(x, y, z)  = orderTriple (y, x, z)
              | y < x                           = (y, x, z)
              | otherwise                       = (x, y, z)