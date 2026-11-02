-- subiectul 1

-- tip de date ce reprezinta puncte cu nr variabil de coordonate intregi
data Point = Pt [Int]
            deriving Show


-- tip de date ce repreazinta arbori binari (noduri sortate)
data Arb = Empty | Node Int Arb Arb
            deriving Show


-- clasa ToFromArb
class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a


-- Sa se faca o instanta a clasei ToFromArb pentru tipul Point. Inserarea in arbore se va face tinand cont de proprietate arborelui de a fi sortat.
instance ToFromArb Point where
    toArb (Pt []) = Empty -- daca lista e vida, arborele e vid
    toArb (Pt (x:xs)) = Node x (toArb (Pt xs)) Empty -- altfel, nodul curent e radacina, iar restul listei se imparte in stanga si dreapta
    fromArb Empty = Pt [] 
    fromArb (Node x l r) = Pt (x : (fromPt (fromArb l)) ++ (fromPt (fromArb r))) -- se construieste lista concatenand elementul curent cu listele obtinute din subarborii stang si drept
        where fromPt (Pt x) = x -- functie auxiliara pentru a extrage lista dintr-un punct
        
-- testare
main :: IO ()
main = do
    print $ toArb (Pt [1,2,3,4,5])


-- subiectul 2

-- Sa se scrie o functie care primeste doua numere intregi si o lista de numere intregi si construieste din lista initiala, lista numerelor aflate in intervalul definit de cele doua numere. Sa se rezolve problema in doua moduri (o solutie fara monade si o solutie cu monade).

--getFromInterval 5 7 [1,2,3,4,5,6,7,8,9,10] -- [5,6,7]
getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval a b l = filter (\x -> x >= a && x <= b) l

