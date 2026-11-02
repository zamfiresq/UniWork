-- subiectul 3

-- tip de data
newtype BM a = BM {getBM :: (String, Maybe a)} deriving Show


-- instanta Functor
instance Functor BM where
    fmap f ma = f <$> ma

-- instanta Applicative 
instance Applicative BM where
    pure = return 
    mf <*> ma = do
        f <- mf
        f <$> ma

-- testare
testBM :: BM Int
testBM = ma >>= f 
    where
        ma = BM ("ana are mere", Just 7)
        f x = BM ("si pere!", if even x then Just x else Nothing)

-- instanta clasa Monad pentru BM
instance Monad BM where
    return va = BM ("", Just va)
    ma >>= k = BM (str1 1

 