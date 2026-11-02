-- 1
poly :: Double -> Double -> Double -> Double -> Double
poly x a b c  = (a * x^2) + (b * x^2) + c

-- 2
eeny :: Integer -> String
eeny x = if (mod x 2 == 0)
           then "eeny"
      else "meeny"

-- 3
fizzbuzz :: Integer -> String
fizzbuzz x 
    | mod x 3 == 0 && mod x 5 == 0 = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = []


fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)
    
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
    
-- 4
tribonacci :: Integer -> Integer
tribonacci n
    | n == 1   = 1
    | n == 2   = 1
    | n == 3   = 2
    | n > 3   = tribonacci (n - 1) + tribonacci (n - 2) + tribonacci (n - 3)
    | otherwise = 0


-- 5
binomial :: Integer -> Integer -> Integer
binomial n k 
    | k == 0 || k == n = 1
    | n == 0 || k > n = 0
    | otherwise = binomial (n - 1) (k - 1) + binomial (n - 1) k 

-- 6 - verificam daca lungimea unei liste este para
verifL :: [Int] -> Bool
verifL l 
    | mod (length l) 2 == 0 = True
    | otherwise = False

-- 7 - intoarce o lista care contime ultimele n elemente ale listei l
takefinal :: [Int] -> Int -> [Int]
takefinal l n 
    | n == 0 = []
    | n > length l = l
    | otherwise = drop (length l - n) l

-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t) -- h = head, t = tail 
 | even h    = h `div` 2 : t'
 | otherwise = t'
 where t' = semiPareRec t
 

-- 7 a
-- intoarcem lista ce contine n elemente egale cu v
myreplicate :: Int -> Int -> [Int]
myreplicate n v
    | n == 0 = []
    | otherwise = v : myreplicate (n - 1) v -- adaugam elementul v in lista si apelam recursiv functia cu n - 1

-- 7 b
sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t)
    | mod h 2 == 1 = h + sumImp t
    | otherwise = sumImp t

-- 7 c - suma lungimilor sirurilor care incep cu 'A'
-- nu merge
totalLen :: [String] -> Int
totalLen [] = 0
totalLen (x:xs)
  | x == "A"  = length x + totalLen xs
  | otherwise = totalLen xs
