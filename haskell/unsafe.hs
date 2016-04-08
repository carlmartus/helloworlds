-- Unsafe global varialble
-- Usable for async FFI environments

import System.IO.Unsafe
import Data.IORef

var :: IORef Int
var = unsafePerformIO (newIORef 4)

main :: IO ()
main = do

    x <- readIORef var
    print x
    writeIORef var (x+1)

    x <- readIORef var
    print x

