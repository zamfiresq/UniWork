import Data.List

myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x + x

triple :: Integer -> Integer
triple x = 3 * x

--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in (maxim  u z)

               
-- ca sa anulez un modul, fac: "ghci> :module -Data.List.NonEmpty"

-- a
sumaPatrate :: Integer -> Integer -> Integer
sumaPatrate x y = x^2 + y^2

-- b 
parImpar :: Integer -> String
parImpar x = if (mod x 2 == 0)
               then "par"
          else "impar"

-- c
factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n-1)

-- d
dublu2 :: Integer -> Integer -> Bool
dublu2 x y = if (x > 2 * y)
               then True
          else False

-- e
elementMaximLista :: [Integer] -> Integer
elementMaximLista [] = error "Lista vida"
elementMaximLista (x:xs) = do
     if (null xs)
          then x
     else if (x > elementMaximLista xs)
          then x
     else elementMaximLista xs

