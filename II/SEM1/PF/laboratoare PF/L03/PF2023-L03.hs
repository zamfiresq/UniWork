-- 1
nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (x:xs) = if x == reverse x
                    then length [c | c <- x, c `elem` "aeiouAEIOU"] + nrVocale xs
                    else nrVocale xs


-- nrVocale ["sos", "civic", "palton", "desen", "aerisirea"] == 9


-- 2 
f :: Int -> [Int] -> [Int]
f _ [] = []
f n (x:xs) = if mod x 2 == 0
                then x : n : f n xs
                else x : f n xs
                
-- f 3 [1,2,3,4,5,6] = [1,2,3,3,4,3,5,6,3]


semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

-- 3 
divizori :: Int -> [Int]
divizori n = [x | x <- [1..n], mod n x == 0]
-- divizori 4 == [1,2,4]

-- 4
listadiv :: [Int] -> [[Int]]
listadiv l = [divizori x | x <- l]
-- listadiv [1,4,6,8] == [[1],[1,2,4],[1,2,3,6],[1,2,4,8]]

-- 5 
inInterval :: Int -> Int -> [Int] -> [Int]
inInterval a b l = [x | x <- l, x >= a, x <= b]
-- inInterval 5 10 [1..15] == [5,6,7,8,9,10]

-- 5 a) 
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] = []
inIntervalRec a b (x:xs) = if x >= a && x <= b
                            then x : inIntervalRec a b xs
                            else inIntervalRec a b xs

-- 5 b) folosind lista de liste
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b l = concat [inInterval a b [x] | x <- l]
-- inInterval 5 10 [1,3,5,2,8,-1] == [5,8]

-- 6 
pozitive :: [Int] -> Int
pozitive l = length [x | x <- l, x > 0]
-- pozitive [0,1,-3,-2,8,-1,6] == 3

-- 6 a) recursiv
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0 
pozitiveRec (x:xs) = if x > 0
                        then 1 + pozitiveRec xs
                        else pozitiveRec xs

-- 6 b) folosind lista in lista
pozitiveComp :: [Int] -> Int
pozitiveComp l = sum [1 | x <- l, x > 0]


-- 7
pozitiiImpare :: [Int] -> [Int]
pozitiiImpare l = [poz | (x, poz) <- zip l [0..], odd x]
-- pozitiiImpare [0,1,-3,-2,8,-1,6,1] == [1,2,5,7]

-- 7 a) recursiv
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitiiImpareRecAux l 0 -- functie auxiliara
    where
    pozitiiImpareRecAux :: [Int] -> Int -> [Int]
    pozitiiImpareRecAux [] _ = []
    pozitiiImpareRecAux (x:xs) poz = if odd x -- daca x este impar
                                        then poz : pozitiiImpareRecAux xs (poz + 1) -- adaugam pozitia lui in lista
                                        else pozitiiImpareRecAux xs (poz + 1) -- altfel trecem la urmatorul element

-- 7 b) folosind lista in lista
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [poz | (x, poz) <- zip l [0..], odd x] -- zip -> creeaza o lista de tupluri, fiecare tuplu contine un element din fiecare lista

-- 8 
multDigits :: String -> Int
multDigits s = product [read [x] :: Int | x <- s, x `elem` "0123456789"]

-- multDigits "The time is 4:25" == 40
-- multDigits "No digits here!" == 1

-- 9 functie care primeste o lista si intoarce toate permuatiile acesteia
permutari :: [a] -> [[a]]
permutari [] = [[]]
permutari (x:xs) = [zs | ys <- permutari xs, zs <- insert x ys]
    where
    insert :: a -> [a] -> [[a]]
    insert x [] = [[x]]
    insert x (y:ys) = (x:y:ys) : [y:zs | zs <- insert x ys]

-- 10 
combinari :: Int -> [a] -> [[a]]
combinari 0 _ = [[]]
combinari _ [] = []
combinari k (x:xs) = map (x:) (combinari (k-1) xs) ++ combinari k xs

-- 11 sa se scrie o functie care primeste un numar n si o lista si intoarce toate aranjamentele de k elemente din lista
aranjamente :: Int -> [a] -> [[a]]
aranjamente 0 _ = [[]]
aranjamente _ [] = []
aranjamente k (x:xs) = map (x:) (aranjamente (k-1) xs) ++ aranjamente k xs

-- 12 functie ce primeste ca argument dimensiunea unei table de sah si intoarce nr de dame ce trebuie plasate pe tabla astfel incat sa nu se atace reciproc
nrdame :: Int -> Int
nrdame n = length (permutari [0..n-1]) - length (filter (atac n) (permutari [0..n-1]))
    where
    atac :: Int -> [Int] -> Bool
    atac n l = or [abs (l !! i - l !! j) == j - i | i <- [0..n-2], j <- [i+1..n-1]]

-- nrDame 4 == 2