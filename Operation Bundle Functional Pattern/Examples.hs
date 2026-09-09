-- runghc Examples.hs

module Main where

import Expr

main :: IO ()
main = do
    let expr = addition (number 10) (number 20)

    putStrLn $ "Printed:    " ++ printExpr expr
    putStrLn $ "Interpreted: " ++ show (interpretExpr expr)
    putStrLn $ "Analyzed:   " ++ analyzeExpr expr

    let b = boolean True

    putStrLn $ "\nBoolean:"
    putStrLn $ "Printed:    " ++ printExpr b
    putStrLn $ "Interpreted: " ++ show (interpretExpr b)
    putStrLn $ "Analyzed:   " ++ analyzeExpr b