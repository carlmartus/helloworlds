{-# LANGUAGE ForeignFunctionInterface #-}

import Foreign
import Foreign.C.Types

foreign import ccall hello :: CInt -> IO ()

main :: IO ()
main = do
    putStrLn "Hello World"
    mapM_ hello [1..4]

