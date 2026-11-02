-- subiectul 2

-- tipuri de date

data Pereche a b = MyP a b deriving Show
newtype Lista a = MyL [a] deriving Show


-- clasa MyOp

class MyOp m where
    myZip :: m a -> m b -> m (Pereche a b)


-- sa se instantieze clasa MyOp pentru tipul Lista

-- exemple pt testare
-- lp1 = MyL [97,3,100]
-- lp2 = MyL ['a'..'d']
-- myZip lp1 lp2 = MyL [MyP 97 'a', MyP 3 'b', MyP 100 'c']

instance MyOp Lista where
    myZip (MyL []) _ = MyL []
    myZip _ (MyL []) = MyL []
    myZip (MyL (x:xs)) (MyL (y:ys)) = MyL [MyP x y] `concatL` myZip (MyL xs) (MyL ys)
        where
            concatL (MyL l1) (MyL l2) = MyL (l1 ++ l2)

