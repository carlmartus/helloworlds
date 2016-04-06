import Debug.Trace

sumFunc :: [Int] -> Int
sumFunc (x:xs) = trace ("Sum add " ++ show x) x + (sumFunc xs)
sumFunc [] = trace "End of sum element" 0

main :: IO ()
main = do
    print $ sumFunc [1..10]

