import System.Random

main :: IO ()
main = do
    g <- getStdGen
    map show $ take 2 g
    putStrLn "Hej"

