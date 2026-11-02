{-
[x^2 |x <- [1..10], x `rem` 3 == 2] -- rezultat: ia patratele lui x pentru care x impartit la 3 da restul 2 => [4, 25, 64]
[(x,y) | x <- [1..5], y <- [x..(x+2)]] -- rezultat: ia toate perechile (x,y) pentru x in [1..5] si y in [x..(x+2)] => [(1,1),(1,2),(1,3),(2,2),(2,3),(2,4),(3,3),(3,4),(3,5),(4,4),(4,5),(4,6),(5,5),(5,6),(5,7)]
[(x,y) | x <- [1..3], y <- [x..3]] -- rezultat: ia toate perechile (x,y) pentru x in [1..3] si y in [x..3] => [(1,1),(1,2),(1,3),(2,2),(2,3),(3,3)]
[(x,y) | x <- [1..3], let k = x^2, y <- [1..k]] -- rezultat: ia toate perechile (x,y) pentru x in [1..3], k = x^2 si y in [1..k] => [(1,1),(2,1),(2,2),(3,1),(3,2),(3,3)]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']] -- rezultat: ia toate literele mari din sirul de caractere => "FMI"
[[x..y] | x <- [1..5], y <- [1..5], x < y] -- rezultat: ia toate listele de la x la y pentru x in [1..5] si y in [1..5] astfel incat x < y => [[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5],[2,3],[2,3,4],[2,3,4,5],[3,4],[3,4,5],[4,5]]
-}

-- 1
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `mod` x == 0]

-- 2
prim :: Int -> Bool
prim n = length (factori n) == 2

-- 3
numerePrime :: Int -> [Int]
numerePrime np = [x | x <- [2..np], prim x]


ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = undefined
ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata = undefined
