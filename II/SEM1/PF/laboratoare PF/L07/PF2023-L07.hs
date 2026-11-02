import Data.Maybe

data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
          deriving Eq
data Operation = Add | Mult
         deriving (Eq, Show)
data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

instance Show Expr where
  show (Const x) = show x
  show (e1 :+: e2) = "(" ++ show e1 ++ " + "++ show e2 ++ ")"
  show (e1 :*: e2) = "(" ++ show e1 ++ " * "++ show e2 ++ ")"

--1
evalExp :: Expr -> Int
evalExp (Const c) = c
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

--2
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add st dr) = evalArb st + evalArb dr
evalArb (Node Mult st dr) = evalArb st * evalArb dr

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

--3
expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)

data IntSearchTree value
  = Empty
  | BNode
      (IntSearchTree value)    -- elemente cu cheia mai mica
      Int                       -- cheia elementului
      (Maybe value)             -- valoarea elementului
      (IntSearchTree value)    -- elemente cu cheia mai mare


--4
lookupT :: Int -> IntSearchTree value -> Maybe value
lookupT _ Empty = Nothing
lookupT key (BNode leftTree currentKey val rightTree) 
 | key == currentKey = val
 | key < currentKey = lookupT key leftTree 
 | otherwise = lookupT key rightTree

testtree =
        BNode
          (BNode Empty 2 (Just "Two") Empty)
          5
          (Just "Five")
          (BNode Empty 8 (Just "Eight") Empty)

--5
keys ::  IntSearchTree value -> [Int]
keys Empty = []
keys (BNode leftTree key val rightTree) = keys leftTree ++ [key] ++ keys rightTree

--test 
-- keys testtree == [2,5,8]

--6
values :: IntSearchTree value -> [Maybe value]
values Empty = []
values (BNode leftTree key val rightTree) = values leftTree ++ [val] ++ values rightTree

--test
--values testtree == [Just "Two",Just "Five",Just "Eight"]

--7
insert :: Int -> value -> IntSearchTree value -> IntSearchTree value
insert key val Empty = BNode Empty key (Just val) Empty
insert key val (BNode lt k v rt)
 | key == k = BNode lt key (Just val) rt  -- Actualizam valoarea dacă cheia există deja
 | key < k =  BNode (insert key val lt) k v rt
 | otherwise = BNode lt k v (insert key val rt)

--test
insertTree = insert 6 "Six" testtree
-- values insertTree == [Just "Two",Just "Five",Just "Six",Just "Eight"]

--8
delete :: Int -> IntSearchTree value -> IntSearchTree value
delete _ Empty = Empty
delete key (BNode lt k v rt) 
  | key < k = BNode (delete key lt) k v rt
  | key > k = BNode lt k v (delete key rt)
  | otherwise = BNode lt k Nothing rt

--test
updatedTree = delete 5 testtree
-- values updatedTree == [Just "Two",Nothing,Just "Eight"]

--9
toList :: IntSearchTree value -> [(Int, value)]
toList Empty = []
toList (BNode lt key (Just val) rt) =
  toList lt ++ [(key, val)] ++ toList rt
toList (BNode lt key Nothing rt) = --ignoram Nothing-ul
  toList lt ++ toList rt

--test
--toList testtree == [(2,"Two"),(5,"Five"),(8,"Eight")]

--10
fromList :: [(Int,value)] -> IntSearchTree value 
fromList [] = Empty 
fromList ((key, val):rest) = insert key val (fromList rest)

--test
pairs = [(2, "Two"), (5, "Five"), (8, "Eight")]
listTree = fromList pairs
--values listTree == [Just "Two",Just "Five",Just "Eight"]

--11
printTree :: IntSearchTree value -> String
printTree Empty = ""
printTree (BNode lt key _ rt) =
   "(" ++ printTree lt ++ show key ++ printTree rt ++ ")"

f x = g x + x 
  where g x = x + 1
--printTree testtree == "((2)5(8))"

