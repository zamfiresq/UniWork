{-
Clasa de tipuri
-> determinata de o multime de functii
-> o interfata
-> tipurile care apartin clasei = instante ale clasei

Pentru a preciza ca o functie este intr-o anumita clasa:
my elem :: Eq a => a -> [a] -> Bool 
Eq = constrangere de tip
=> separa constrangerile de tip de restul signaturii

Clasele pot fi extinse:
class (Eq a) => Ord a where          --orice instanta a clasei Ord trebuie sa fie instanta a clasei Eq
  ...

Clase de tipuri existente:
- Eq a (==, /=)
- Ord a (<, >, <=, >=)
- Show a (afisare pe ecran ca String)
- Num a (tipuri de date numerice: +, -, * etc.) - Integer, Fractional, Rational, Real, Integral (div, mod)

Cu :i se poate verifica ce contine o anumita clasa de tipuri

Instantierea clasei se poate face prin:
- derivare automata:
data Point a b = Pt a b
                  deriving Eq
- explicita:
instance Eq a => Eq (Point a b) where 
        (==) (Pt x1 y1) (Pt x2 y2) = (x1 == x2)

Egalitatea (Eq), relatia de ordine (Ord) si modalitatea de afisare (Show) sunt definite implicit 
daca este posibil.
  
-}

--Ord key => key e instanta a clasei Ord
--pentru a permite compararea cheilor și menținerea unei ordini în colecție
--c = tipul de colectie, key și value sunt tipurile cheilor și valorilor din colecție
class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  clookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  values :: c key value -> [value]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  --1
  keys c = [fst p | p <- toList c]

  values c = [snd p | p <- toList c]

  fromList [] = empty
  fromList ((k,v):es)  = insert k v (fromList es)

newtype PairList k v = PairList { getPairList :: [(k, v)] }
  deriving Show

--2
--trebuie sa scriem definitii pentru fiecare metoda din clasa

instance Collection PairList where
    empty = PairList []
    singleton k v = PairList [(k, v)]
    insert k v (PairList l) = PairList $ (k, v) : filter ((/= k) . fst) l
    clookup :: Ord key => key -> PairList key value -> Maybe value
    clookup k = lookup k  . getPairList  
    delete :: Ord key => key -> PairList key value -> PairList key value
    delete k (PairList l) = PairList $ filter ((/= k) . fst) l
    keys (PairList l) = map fst l
    values (PairList l) = map snd l
    toList (PairList l) = getPairList (PairList l)
    --fromList = PairList

data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare
        deriving Show

--3
instance Collection SearchTree where
   empty = Empty
   singleton k v = BNode Empty k (Just v) Empty
   insert k v = go
     where
       go Empty = singleton k v
       go (BNode t1 k1 v1 t2)
         | k == k1   = BNode t1 k1 (Just v) t2
         | k < k1    = BNode (go t1) k1 v1 t2
         | otherwise = BNode t1 k1 v1 (go t2)

  {-
  sau
    insert k v Empty = singleton k v
    insert k v (BNode left key oldValue right)
        | k == key = BNode left key (Just v) right
        | k < key  = BNode (insert k v left) key oldValue right
        | otherwise = BNode left key oldValue (insert k v right)
  -}
   delete k = go
     where
       go Empty = Empty
       go (BNode t1 k1 v1 t2)
         | k == k1   = BNode t1 k1 Nothing t2
         | k < k1    = BNode (go t1) k1 v1 t2
         | otherwise = BNode t1 k1 v1 (go t2)

   clookup k = go 
     where
       go Empty = Nothing
       go (BNode t1 k1 v1 t2)
         | k == k1   = v1
         | k < k1    = go t1
         | otherwise = go t2

   keys Empty = []
   keys (BNode left key _ right) = keys left ++ [key] ++ keys right
    
   values Empty = []
   values (BNode left _ (Just value) right) = values left ++ [value] ++ values right
   values (BNode left _ Nothing right) = values left ++ values right

   toList Empty = []
   toList (BNode ltk k v gtk) = toList ltk ++ embed k v ++ toList gtk
     where
       embed k (Just v) = [(k,v)]
       embed _ _ = []

-- *Main> fromList [(1,"a"),(2,"b"),(3,"c")] :: PairList Int String
-- PairList [(1,"a"),(2,"b"),(3,"c")]
-- *Main> fromList [(1,"a"),(2,"b"),(3,"c")] :: SearchTree Int String
-- Node (Node (Node Empty 1 (Just "a") Empty) 2 (Just "b") Empty) 3 (Just "c") Empty

--test:
{-
let tree = insert 3 "three" (insert 1 "one" (insert 2 "two" empty))
clookup 1 tree  -- Ar trebui să returneze Just "one"
clookup 4 tree  -- Ar trebui să returneze Nothing

let tree = delete 2 (insert 3 "three" (insert 1 "one" (insert 2 "two" empty)))
toList tree    -- Ar trebui să returneze [(1, "one"), (3, "three")]

let tree = insert 3 "three" (insert 1 "one" (insert 2 "two" empty))
keys tree      -- Ar trebui să returneze [1, 2, 3]
values tree    -- Ar trebui să returneze ["one", "two", "three"]

let tree = fromList [(3, "three"), (1, "one"), (2, "two")]
toList tree    -- Ar trebui să returneze [(1, "one"), (2, "two"), (3, "three")]
-}

data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
          deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

--4
instance Show Punct where
  show (Pt []) = "()"
  show (Pt l) = "(" ++ parse l ++")"
     where
        parse [] = ""
        parse [x] = show x
        parse (x:y:xs) = show x ++ ", " ++ parse (y:xs)

--5
-- toArb (Pt [1,2,3])
-- N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
--  (1,2,3)

instance ToFromArb Punct where
    toArb (Pt []) = Vid
    toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))
    fromArb (Vid) = Pt []
    fromArb (F x) = Pt [x]
    fromArb (N l r) = Pt (p1++p2)
      where  Pt p1 = fromArb l
             Pt p2 = fromArb r


data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
  perimeter :: (Floating a) => g a -> a
  area :: (Floating a) =>  g a -> a

--6
instance GeoOps Geo where
  perimeter (Square l) = 4 * l
  perimeter (Rectangle l1 l2) = 2*l1 + 2*l2
  perimeter (Circle r) = 2 * pi * r

  area (Square l) = l^2
  area (Rectangle l1 l2) = l1*l2
  area (Circle r) = pi * r^2

--7
instance  (Eq a, Floating a) => Eq (Geo a) where
      fig1 == fig2 = perimeter fig1 ==  perimeter fig2
