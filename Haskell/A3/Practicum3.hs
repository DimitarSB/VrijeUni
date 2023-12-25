module Practicum3 where

{-
Name:           Dimitar Bachvarov
VU-net id:      dbv900
Student number: 2728704
Discussed with: -
Remarks:        -
Sources:        
https://www.47deg.com/blog/game-of-life-haskell/
https://crypto.stanford.edu/~blynn/haskell/life.html
https://codereview.stackexchange.com/questions/225556/a-haskell-implementation-of-conways-game-of-life-viewable-on-the-console-no-e
-}


-- Exercises Arithmetical Expressions
data IntExp  = Lit Int | Add IntExp IntExp | Mul IntExp IntExp
  deriving Show

showintexp :: IntExp -> String
showintexp (Lit exp) = show exp
showintexp (Add exp1 exp2) = "(" ++ showintexp exp1 ++ " + " ++ showintexp exp2 ++ ")"
showintexp (Mul exp1 exp2) = "(" ++ showintexp exp1 ++ " * " ++ showintexp exp2 ++ ")"

evalintexp :: IntExp -> Int
evalintexp (Lit exp) = exp
evalintexp (Add exp1 exp2) = evalintexp exp1 + evalintexp exp2
evalintexp (Mul exp1 exp2) = evalintexp exp1 * evalintexp exp2

-- Exercises Combinatory Logic
data Term = S | K | I | App Term Term

instance Show Term where
  show a = showterm a

showterm :: Term -> String
showterm S = "S"
showterm K = "K"
showterm I = "I"
showterm (App t1 t2) = "(" ++ showterm t1 ++ showterm t2 ++ ")"

isredex :: Term -> Bool
isredex (App (App (App S _ ) _) _) = True
isredex (App (App K _) _) = True 
isredex (App I _) = True
isredex _ = False 

hasredex :: Term -> Bool 
hasredex (App p q) = isredex (App p q) || hasredex p || hasredex q
hasredex t = isredex t

isnormalform :: Term -> Bool
isnormalform x =
  if(hasredex x)
    then False
    else True

-- I P → P
-- K P Q → P
-- S P Q R → (P R) (Q R)

headstep :: Term -> Term
headstep (App (App (App S p) q) r) = App (App (headstep p) (headstep r)) (App (headstep q) (headstep r))
headstep (App (App K p) _) = p
headstep (App I p) = p
headstep x = x 

doall :: Term -> Term
doall t@(App t1 t2) =
  if(isredex t)
    then doall (headstep t)
    else
    let reducedT1 = if isredex t1 then doall (headstep t1) else t1
        reducedT2 = if isredex t2 then doall (headstep t2) else t2
    in App (headstep reducedT1) (headstep reducedT2)
doall t = t

-- Exercises Equational Specifications
data Thing = X | Y | Z
  deriving (Show, Eq, Bounded, Enum)

-- nxt(nxt(c)) = d
-- nxt(nxt(nxt(x))) = x

-- X-> Y -> Z -> X

nxt :: Thing -> Thing
nxt X = Y
nxt Y = Z
nxt Z = X
----------------------------------------------- 
data I = Zero | One
  deriving (Show, Eq, Bounded, Enum)

s :: I -> I
s Zero = One
s One = Zero

p :: I -> I
p Zero = One
p One = Zero
