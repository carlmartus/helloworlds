{-# LANGUAGE JavaScriptFFI #-}

module Main where
import GHCJS.Prim

foreign import javascript unsafe "h2set($1);" h2set :: JSVal -> IO ()

main :: IO ()
main = do
    putStrLn "Hello from Haskell"
    h2set (toJSString "Title from Haskell")

