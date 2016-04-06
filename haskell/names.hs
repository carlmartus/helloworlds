import System.Random
import Data.List

type Part = String

part1 :: [Part]
part1 = [
    "Pol",
    "Sand",
    "Wester",
    "Karl",
    "Gustav",
    "Nils",
    "Lund" ]

part2 :: [Part]
part2 = [
    "hem",
    "man",
    "sen",
    "sson",
    "gren" ]

count :: Int
count = 10 * (length part1 + length part2)


partFromList :: [String] -> Int -> String
partFromList list id = list !! (id `mod` length list)

nameFromIds :: Int -> Int -> String
nameFromIds id1 id2 = (partFromList part1 id1) ++ (partFromList part2 id2)

main :: IO ()
main = do
    gen1 <- getStdGen
    gen2 <- getStdGen

    let list1 = map (`mod` length part1) (randoms gen1 :: [Int])
    let list2 = map (`mod` length part2) (drop count $ randoms gen2 :: [Int])

    let q = zip (take count list1) (take count list2)
    let r = map (uncurry nameFromIds) q
    mapM_ putStrLn $ (nub . sort) r

