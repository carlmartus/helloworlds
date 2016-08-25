import Data.Word
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BSC8

data Coord = Coord Int Int -- deriving Show
data Color a = Color a a a
data Image a = Image Int Int [Color a]

coordSlip :: Int -> [Coord]
coordSlip w = map (\i -> (Coord (mod i w) (div i w))) [0..]

concatPixels :: [Color a] -> [a]
concatPixels = concatMap convert
    where convert (Color r g b) = [r, g, b]

intToWord8 :: Int -> Word8
intToWord8 = fromIntegral

lookupPixel :: Coord -> Color Word8
lookupPixel (Coord x y) = Color (intToWord8 x) (intToWord8 y) 0

makePlainImage :: Int -> Int -> Image Word8
makePlainImage w h = Image w h pixels
    where pixels = take (w*h) (map lookupPixel $ coordSlip w)

writeImage :: String -> Image Word8 -> IO ()
writeImage fileName (Image w h pixels) = do
    BS.writeFile fileName $ BS.append header content
    where
        header = BSC8.pack $ "P6 " ++ (show w) ++ " " ++ (show h) ++ "\n"
        content = BS.pack $ concatPixels pixels

main :: IO ()
main = do
    writeImage "test.ppm" $ makePlainImage 256 256

