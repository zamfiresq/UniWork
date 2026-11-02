{-
FOLDR-> Fold FROM the RIGHT - arbore la dreapta
FOLDL-> Fold FROM the LEFT - arbore la stanga


Foldable t => (a -> b -> b) -> b -> t a -> b
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr (-) 0 [1,2,3,4] =>
(1 - (2 - (3 - (4 - 0)))) = -2
  -
 / \
1   -
   / \
  2   -
     / \
    3   -
       / \
      4   0

Date fiind o functie de actualizare a valorii calculate cu un element
curent, o valoare initiala, si o lista, calculati valoarea obtinuta prin
aplicarea repetata a functiei de actualizare fiecarui element din lista.

Foldable t => (b -> a -> b) -> b -> t a -> b
foldl :: (b -> a -> b) -> b -> [a] -> b
foldl (-) 0 [1,2,3,4] =>
((((0 - 1) - 2) - 3) - 4) = -10

        -
       / \
      -   4
     / \
    -   3
   / \
  -   2
 / \
0   1

Deci foldr aplica functia pe elementele din lista, apoi adauga si el neutru, iar
foldl adauga elementul neutru (valoarea initiala) la inceput 

foldr preserves the order of the right-recursive list constructors, 
while the foldl reverses the order of list constructor

foldl is tail-recursive, whereas foldr is not
-}

--1
sumImp :: [Int] -> Int
sumImp l = foldr (+) 0 (map (^2) (filter odd l )) --foldl mergea la fel

--2
alltrue :: [Bool] -> Bool
alltrue l = foldr (&&) True l --si aici mergea foldl, dar e precizat in cerinta sa folositi foldr

--3
allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies p list = foldr (\ x acc -> acc && p x) True list 
-- merge foldl, daca inversam x si acc 
--de ce trebuie si acc? foldr primeste o functie cu 2 parametri!!!!!!!!!
--initial, acc = True
--acc = acumulator care retine si combina (&&) toate rezultatele lui p x 
--test: allVerifies (>0) [1,2,3,4] == True

--4
anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies  p list = foldr (\ x acc -> acc || p x) False list 
--initial, acc = False 
--acc = acumulator care retine si aplica || pe toate rezultatele lui p x 
--test: anyVerifies odd [1,2,3,4]  == True

--5
mapFoldr :: (a->b) -> [a] -> [b]
mapFoldr f list = foldr (\ x acc -> f x : acc) [] list 
--acc la final, 1 : 2 : 3 : [] = [1,2,3]

--6
filterFoldr :: (a->Bool) -> [a] -> [a]
filterFoldr p list = foldr (\ x acc -> (if p x then [x] else [] ) ++ acc) [] list 

--7
listToInt :: [Integer]-> Integer
listToInt list = foldl (\acc x->acc * 10 + x) 0 list
--ca la prelucrarea numerelor, nr = 0 initial, nr = nr * 10 + x
--ce ar face foldr pe [1,2,3,4]? 4*10 + 3 * 10 + 2*10 + 1*10 (ar trebui pus x * 10 + acc si asta ar da 4321)

--7a
rmChar :: Char -> String -> String
rmChar c s = filter (/=c) s
{-
rmCharsRec :: String -> String -> String
rmCharsRec s1 "" = ""
rmCharsRec s1 (c:s)
   | c `elem` s1 = rmCharsRec s1 s
   | otherwise = c:rmCharsRec s1 s
-}

--7b
rmCharsRec :: String -> String -> String
rmCharsRec "" s2 = s2
rmCharsRec (c:s) s2 = rmCharsRec s (rmChar c s2)

--7c
rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr rmChar s2 s1

--8
myReverse :: [Int] -> [Int]
myReverse l = foldr f e l
  where
    f x r = r ++ [x]
    e     = []
--r e acumulatorul (initial []), iar x e fiecare element din lista (pe rand)
--pt [1,2,3,4] o sa avem:
--f 1 [] = [1]
--f 2 [1] = [2,1]
-- ...
-- f 5 [4,3,2,1] = [5,4,3,2,1]

--9
-- myElem x y <=> x `elem` y sau elem x y
myElem :: Int -> [Int] -> Bool
myElem y = foldr f e
  where
    f x r = (x == y) || r
    e = False
--la fel, r e acumulatorul care e initial False 
--verifica daca fiecare element e egal cu cel putin un element din lista


--10    
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip = foldr f e
  where
    f (a,b) (as,bs) = (a:as,b:bs)
    e = ([],[])
--unzip => [(1,2),(3,4)] => ([1,3], [2,4])
--(as, bs) acumulator, initial ([],[])
--adauga pe rand fiecare element din pereche la lista aferenta


--11    
union :: [Int] -> [Int] -> [Int]    
union xs ys = foldr f e ys
  where
    f y r | y `elem` xs = r
          | otherwise = r ++ [y] --y : r daca vreti elementele din a doua lista adaugate la inceput 
    e = xs    
--verifica daca fiecare element din a doua lista apartine primei liste
--daca da, nu face nimic, daca nu, il adauga la acumulator
--initial, acumulatorul e prima lista

--12    
intersect :: [Int] -> [Int] -> [Int]      
intersect xs ys = foldr f e ys
  where
    f y r | y `elem` xs = y:r
          | otherwise   = r
    e = []
--acumulatorul e initial lista vida
--verifica pe rand daca fiecare element din a doua lista apartine primei liste
--daca da, il adauga la lista, daca nu, acumulatorul ramane neschimbat

--13    
permutations :: [Int] -> [[Int]]
permutations = foldr f e
  where
    f x r = concatMap (insertEverywhere x) r
    e     = [[]]

--r e lista de permutari partiale
--x e elementul de introdus

--concatMap g = foldr f e
--  where
--    f x r = g x ++ r
--    e     = []

insertEverywhere :: Int -> [Int] -> [[Int]]
insertEverywhere x [] = [[x]]
insertEverywhere x xs@(y:ys) = (x:xs) : map (y:) (insertEverywhere x ys)    
--functie auxiliara care introduce nr dat ca parametru pe rand pe fiecare pozitie 
--din  intervalul [0..length list]  -> lungimea listei initiale + 1
--daca lista primita e goala, intoarce o lista care contine o lista cu un singur parametru, x 
--altfel, 
-- @ e folosit pentru a pastra lista initiala
--În pattern matching, simbolul @ poate fi folosit pentru a face referire la o sub-listă a unei liste. 
{-
(xs@(y:ys)) descompune lista de intrare într-o parte cu capul y și coada ys, 
iar apoi creeaza o referință la lista originală întreagă folosind xs
răm cu lista originală xs în mod separat, menținând-o neschimbată, 
și să aplicăm recursivitatea asupra cozii ys a listei
-}
