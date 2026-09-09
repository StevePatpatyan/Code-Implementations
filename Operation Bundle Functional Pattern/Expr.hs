module Expr
    ( Expr(..)
    , number
    , addition
    , boolean
    ) where

-- a bundle of operations that can be performed on a type
data Expr = Expr
    { printExpr     :: String
    , interpretExpr :: Int
    , analyzeExpr   :: String
    }

-- a new type: Number
number :: Int -> Expr
number n = Expr
    { printExpr     = show n
    , interpretExpr = n
    , analyzeExpr   = "number"
    }

-- a new type: Addition
addition :: Expr -> Expr -> Expr
addition left right = Expr
    { printExpr     = "(" ++ printExpr left
                   ++ " + " ++ printExpr right ++ ")"

    , interpretExpr = interpretExpr left
                   + interpretExpr right

    , analyzeExpr = "addition"
    }

-- another new type: Boolean
boolean :: Bool -> Expr
boolean b = Expr
    { printExpr     = show b
    , interpretExpr = if b then 1 else 0
    , analyzeExpr   = "boolean"
    }

