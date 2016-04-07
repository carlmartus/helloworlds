import System.Environment

data PaSym = PaLeft | PaRight | PaText String deriving (Show)

-- Lexical analysis
lxChar :: Char -> PaSym
lxChar '(' = PaLeft
lxChar ')' = PaRight
lxChar ch = PaText [ch]

lxString :: String -> [PaSym]
lxString = foldr lxFold [] . map lxChar

lx :: String -> [PaSym]
lx = concat . map lxString . words

lxFold :: PaSym -> [PaSym] -> [PaSym]
lxFold PaLeft xs = [PaLeft] ++ xs
lxFold PaRight xs = [PaRight] ++ xs
lxFold (PaText a) (PaText b:xs) = [PaText (a++b)] ++ xs
lxFold (PaText a) xs = [PaText a] ++ xs

-- Semantic analysis
smCount :: [PaSym] -> Int
smCount = foldl (\acc sym -> if acc < 0 then -1 else  acc + value sym) 0
    where
        value PaLeft = 1
        value PaRight = -1
        value _ = 0

sm :: [PaSym] -> Bool
sm = (== 0) . smCount

-- Entry point
main :: IO ()
main = do
    params <- getArgs
    if params == [] then
        errorUsage
    else
        print $ sm (lx (unwords params))

    where errorUsage = do putStrLn "Input S-Expression as parameter"

