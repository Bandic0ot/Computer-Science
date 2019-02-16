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
    (numerator(a) * denominator (b)) == (numerator(b) * denominator (a)) ||
    (numerator(a) * denominator (b)) < (numerator(b) * denominator (a)) then True
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

