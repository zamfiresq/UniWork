import Control.Monad.Writer

-- subiectul 1

-- lista de nr dupa codificare
-- cifrele se dubleaza
-- numerele pari mai mari ca 10 se elimina
-- nr din lista [11,33,55] se ridica la patrat


-- exemplu lista: [3,11,24,6] = [3,3,121,6,6]

-- rezolvare fara monade
transformareLista :: [Int] -> [Int]
transformareLista [] = [] -- lista vida
transformareLista (x:xs)
    -- cifrele se vor dubla
    | x < 10  = x : x : transformareLista xs 
    -- nr pari > 10 se elimina
    | x > 10 && x `mod` 2 == 0 = transformareLista xs
    -- nr din lista [11,33,55] le vom ridica la patrat
    | x `elem` [11,33,55] = x^2 : transformareLista xs
    -- restul numerelor
    | otherwise = x : transformareLista xs

-- transformareLista [3,11,24,6]


    -- rezolvare cu monade
    -- vom folosi monada Writer

transformareListaMonada :: [Int] -> Writer String [Int]
transformareListaMonada [] = return []
