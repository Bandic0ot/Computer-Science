-- Problem 3
data MyFraction = Fraction (Integer, Integer)

instance Num MyFraction where
  (+) = fractionAdd
  (-) = fractionSub
  (*) = fractionMult
  negate = fractionNeg

fractionAdd a b =
  Fraction(numerator(a) * denominator(b) + numerator(b) * denominator(a), (denominator(a) * denominator(b)))

fractionSub a b =
  Fraction(numerator(a) * denominator(b) - numerator(b) * denominator(a), (denominator(a) * denominator(b)))

fractionMult a b = 
  Fraction(numerator(a) * numerator(b), denominator(a) * denominator(b))

fractionNeg a = 
  Fraction((-numerator(a)), denominator(a))

instance Fractional MyFraction where
  (/) = fractionDiv

fractionDiv a b = 
  Fraction(numerator(a) * denominator(b), denominator(a) * numerator(b))

instance Eq MyFraction where
  (==) = fractionEquality

fractionEquality a b =
  if
    numerator(a) * denominator(b) == numerator(b) * denominator(a) then True
  else
    False

instance Ord MyFraction where
  (<) = fractionLess
  (<=) = fractionLessEqual
  x > y = not (x < y)
  x >= y = not (x <= y)

fractionLess a b =
  if
    (numerator(a) * denominator (b)) < (numerator(b) * denominator (a)) then True
  else
    False

fractionLessEqual a b =
  if
    (numerator(a) * denominator (b)) < (numerator(b) * denominator (a)) then True
  else if
    (numerator(a) * denominator (b)) == (numerator(b) * denominator (a)) then True
  else
    False

instance Show MyFraction where
  show(Fraction (x, y)) = show x ++ "/" ++ show y

numerator :: MyFraction -> Integer
numerator (Fraction (x, y))
  | y == 0    = error "Division by 0."
  | y < 0     = error "Denominator must be positive."
  | otherwise = x

denominator :: MyFraction -> Integer
denominator (Fraction (x, y))
  | y == 0    = error "Division by 0."
  | y < 0     = error "Denominator must be positive."
  | otherwise = y

whole :: MyFraction -> Integer
whole (Fraction (x, y))
  | y == 0    = error "Division by 0."
  | y < 0     = error "Denominator must be positive."
  | otherwise = x `div` y

fractional :: MyFraction -> MyFraction
fractional (Fraction (x, y))
  | y == 0    = error "Division by 0."
  | y < 0     = error "Denominator must be positive."
  | otherwise = Fraction (x `rem` y, y)

-- Problem 4(a)
shuffle :: [a] -> [a] -> [a]
shuffle l1 [] = l1
shuffle [] l2 = l2
shuffle (x:xs) (y:ys) = [x, y] ++ shuffle xs ys

-- Problem 4(b)
split :: [a] -> Int -> [[a]]
split l1 n = [(take n l1)] ++ [(drop n l1)]

-- Problem 4(c)
outshuffle :: [a] -> [a]
outshuffle l1 = shuffle x y 
  where
  x = head (split l1 ((length l1) `div` 2))
  y = last (split l1 ((length l1) `div` 2))

inshuffle :: [a] -> [a]
inshuffle l1 = shuffle y x 
  where
  x = head (split l1 ((length l1) `div` 2))
  y = last (split l1 ((length l1) `div` 2))

-- Problem 4(d)
nshuffle :: ([a] -> [a]) -> Int -> [a] -> [a]
nshuffle func num list
  | num == 0    = list
  | otherwise   = nshuffle func (num - 1) (func list)

-- Problem 4(e)
howManyShuffles :: ([Integer] -> [Integer]) -> [Integer] -> [Integer] -> Integer
howManyShuffles func l1 l2 = delta func l1 l2 0
  where delta func l1 l2 n
          | l1 == l2    = n
          | otherwise   = delta func (func l1) l2 (n + 1)