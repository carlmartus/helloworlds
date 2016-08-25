import Data.Word
import Data.ByteString as B
import Data.ByteString.Char8 as BC8

data Color a = Color a a a
data Image a = Image Int Int [Color a]

colorW8 :: Color Word8 -> [Word8]
colorW8 (Color r g b) = [r, g, b]

writePpm :: String -> Image Word8 -> IO ()
writePpm fileName (Image width height colors) = do
    B.writeFile fileName $ append header content
    where
        header = Prelude.foldl1 append $ Prelude.map BC8.pack dataList
        content = B.pack $ Prelude.foldl1 (++) $ Prelude.map colorW8 colors
        dataList = ["P6 ", show width, " ", show height, "\n"]

makeResolution :: Int -> Int -> [(Int, Int)]
makeResolution w h = Prelude.map (\n -> (mod n w, div n w)) [0..(w*h-1)]

makeImage0 :: Int -> Int -> Image Word8
makeImage0 w h = Image w h (Prelude.map pixel $ makeResolution w h)
    where pixel (x, y) = Color 0xff 0xff 0x0

main :: IO ()
main = do
    writePpm "Hello.ppm" $ makeImage0 20 20

