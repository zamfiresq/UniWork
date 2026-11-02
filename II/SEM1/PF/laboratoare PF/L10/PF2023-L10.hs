import Data.List (nub)
import Data.Maybe (fromJust)

type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  | Prop :->: Prop
  | Prop :<->: Prop
  deriving (Eq, Read)
infixr 2 :|: -- v e asociativ de la dreapta la stanga si are precedenta 2
infixr 3 :&: -- ^ asociativ de la dreapta la stanga si are precedenta 3
--Ex1
--1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

--2
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

--3
p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: (Not (Var "P") :&: Not (Var "Q")) :&: (Not (Var "P") :&: Not (Var "R"))

--Ex2
instance Show Prop where
  show (Var nume)= nume
  show (a :|: b) = "("++show a ++ "|" ++ show b++")"
  show (a :&: b) = "("++show a ++ "&" ++ show b++")"
  show (a :->: b) = "("++show a ++ "->" ++ show b++")"
  show (a :<->: b) = "("++show a ++ "<->" ++ show b++")"
  show (Not p) = "(~"++show p++")"
  show F = "F"
  show T = "T"

test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

--Ex3
type Env = [(Nume, Bool)]

--functie care returneaza valoarea corespunzatoare primei perechi gasite in care cheia = a
impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

impl :: Bool -> Bool -> Bool
impl False _ = True
impl _ x = x

echiv :: Bool -> Bool -> Bool
echiv x y = x==y

eval :: Prop -> Env -> Bool
eval (Var x) env = impureLookup x env --gaseste valoarea asociata cheii x
eval T _ = True
eval F _ = False
eval (Not p) env = not $ eval p env
eval (p :&: q) env = eval p env && eval q env
eval (p :|: q) env = eval p env || eval q env
eval (p :->: q) env = eval p env `impl` eval q env
eval (p :<->: q) env = eval p env `echiv` eval q env

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

--Ex4
--nub = elimina duplicatele dintr o lista

variabile :: Prop -> [Nume]
variabile (Var p) = [p]
variabile (Not p) = nub $ variabile p
variabile (p :&: q) = nub (variabile p ++ variabile q)
variabile (p :|: q) = nub $ variabile p ++ variabile q
variabile (p :->: q) = nub $ variabile p ++ variabile q
variabile (p :<->: q) = nub $ variabile p ++ variabile q
variabile _ = [] -- T si F  

test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs [] = [[]]
envs (nume : ns) = [[(nume, valoare)] ++ env | env <- envs ns, valoare <- [False, True]]

-- envs [] = []
--envs [x] = [[(x,False)],[(x,True)]]
--envs (str:xs) = let r = envs xs in  map (\x-> (str,False):x) r  ++ map (\x->(str,True):x) r

test_envs =
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]


--Ex6
satisfiabila :: Prop -> Bool
--satisfiabila p = or $ map (eval p) $ envs $ variabile p
satisfiabila prop = or [eval prop env | env <- envs (variabile prop)]

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

--Ex7
valida :: Prop -> Bool
--valida p = not (satisfiabila (Not p))
valida prop = and [eval prop env | env <- envs (variabile prop)]
test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True


echivalenta :: Prop -> Prop -> Bool
--echivalenta p q = all (\env -> eval (p :<->: q) env) $ envs $ nub $ variabile p ++ variabile q
echivalenta prop1 prop2 = and [eval prop1 env == eval prop2 env | env <- envs (variabile (prop1 :|: prop2))]
test_echivalenta1 =
  True
  ==
  (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
  False
  ==
  (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 =
  True
  ==
  (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))


-----------------------------------------------------------------------------
