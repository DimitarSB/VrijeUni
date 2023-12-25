{-# LANGUAGE RankNTypes #-}
module Practicum2A where

{-
Name: Dimitar Bachvarov
VU-net id: dbv900
Student number: 2728704
Discussed with: -
Remarks:        -
Sources:        
https://www.youtube.com/watch?v=NvLOz-W4PsA&ab_channel=PhilippHagenlocher
https://literateprograms.org/sieve_of_eratosthenes__haskell_.html
https://hackage.haskell.org/package/sieve-0.1.0.1/docs/Data-Sieve.html
https://wiki.haskell.org/The_Fibonacci_sequence
https://hackage.haskell.org/package/type-indexed-queues-0.2.0.0/docs/Data-BinaryTree.html

-}

-- -------------------------
-- Exercises Infinite Lists
-- -------------------------

-- Exercise 1
naturals :: [Integer]
naturals = 1 : map (+ 1) naturals

-- take 10 naturals = [1,2,3,4,5,6,7,8,9,10]
-- take 0 naturals = []

-- Exercise 2
zeroesandones :: [Integer]
zeroesandones = 0 : 1 : map(+ 0) zeroesandones

-- take 10 zeroesandones = [0,1,0,1,0,1,0,1,0,1]
-- take 0 zeroesandones = []

-- Exercise 3
threefolds :: [Integer]
threefolds = 0 : map(* 3) naturals

-- take 10 threefolds = [0,3,6,9,12,15,18,21,24,27]
-- take 0 threefolds = []

-- Exercise 4
removeif :: (a -> Bool) -> [a] -> [a]
removeif f [] = []
removeif f (h:t) = 
  if(f h == True)
    then removeif f t
    else h : removeif f t

nothreefolds :: [Integer]
nothreefolds = removeif (\x -> x `mod` 3 == 0) naturals

-- take 10 nothreefolds = [1,2,4,5,7,8,10,11,13,14]
-- take 0 nothreefolds = []

-- Exercise 5
allnfolds :: Integer -> [Integer]
allnfolds x = 0 : map(* x) naturals

-- take 10 (allnfolds 5) = [0,5,10,15,20,25,30,35,40,45]
-- take 10 (allnfolds 0) = [0,0,0,0,0,0,0,0,0,0]

-- Exercise 6
allnaturalsexceptnfolds :: Integer -> [Integer]
allnaturalsexceptnfolds i = removeif (\x -> x `mod` i == 0) naturals

-- take 10 (allnaturalsexceptnfolds 5) = [1,2,3,4,6,7,8,9,11,12]
-- take 10 (allnaturalsexceptnfolds 2) = [1,3,5,7,9,11,13,15,17,19]

-- Exercise 7
allelementsexceptnfolds :: Integer -> [Integer] -> [Integer]
allelementsexceptnfolds i [] = []
allelementsexceptnfolds i l = removeif (\x -> x `mod` i == 0) l

-- allelementsexceptnfolds 2 [1,2,3,4,5,6] = [1,3,5]
-- allelementsexceptnfolds 5 [100, 10, -5, 7, 8] = [7,8]

-- Exercise 8
removeMultiples :: Integer -> [Integer] -> [Integer]
removeMultiples _ [] = []
removeMultiples z l = filter (\x -> x `mod` z /= 0) l

naturalsFrom2 :: [Integer]
naturalsFrom2 = 2 : map (+ 1) naturalsFrom2

eratosthenes :: [Integer]
eratosthenes = sieve naturalsFrom2
  where
    sieve (h:t) = h : sieve (removeMultiples h t)

-- take 10 eratosthenes = [2,3,5,7,11,13,17,19,23,29]
-- take 0 eratosthenes = []

-- Exercise 9
naturalsFrom0 :: [Integer]
naturalsFrom0 = 0 : map (+ 1) naturalsFrom0

fibonacci :: [Integer]
fibonacci = 0 : 1 : zipWith (+) fibonacci (tail fibonacci)

-- take 10 fibonacci = [0,1,1,2,3,5,8,13,21,34]
-- take 0 fibonacci = []

-- -----------------------
-- Exercise Church Numerals
-- -----------------------
-- we need polymorphic types for the Church Numerals 
type ChurchNumeral = forall a . (a -> a) -> a -> a

-- Exercise 1
churchnumeral :: (Eq a, Num a) => a -> ChurchNumeral 
churchnumeral n =
  if   n == 0
  then \s z -> z
  else \s z -> churchnumeral (n - 1) s (s z)

backtointeger :: (Num a) => ChurchNumeral -> a
backtointeger cn = cn (+1) 0

-- backtointeger (churchnumeral 2) = 2
-- backtointeger (churchnumeral 0) = 0

-- Exercise 2
churchequality ::  ChurchNumeral  -> ChurchNumeral  -> Bool
churchequality x y = 
  if backtointeger x == backtointeger y
    then True
    else False

-- churchequality (churchnumeral 3) (churchnumeral 2) = False
-- churchequality (churchnumeral 3) (churchnumeral 3) = True

-- Exercise 3 given as example
successor ::  ChurchNumeral -> ChurchNumeral
successor x = \s z -> x s (s z)
 
-- Exercise 4
successorb :: ChurchNumeral -> ChurchNumeral
successorb x s z = x s (s z)

-- Exercise 5
apply1 :: (Eq a, Num a) => (ChurchNumeral-> ChurchNumeral) ->  a -> a
apply1 f n =  backtointeger ( f ( churchnumeral n ) ) 

-- Exercise 6
addition :: ChurchNumeral -> ChurchNumeral -> ChurchNumeral
addition x y s z  = undefined

multiplication ::  ChurchNumeral -> ChurchNumeral -> ChurchNumeral
multiplication x y s  = undefined

exponentiation ::  ChurchNumeral -> ChurchNumeral -> ChurchNumeral 
exponentiation x y  = undefined 

-- Exercise 7
apply2 :: (Eq a, Num a) => (ChurchNumeral -> ChurchNumeral -> ChurchNumeral) -> a -> a -> a
apply2 f m n  = undefined


-- ---------------------
-- Exercises Binary Trees
-- ---------------------
data BinaryTree a = Leaf | Node (BinaryTree a) a (BinaryTree a)
  deriving (Show, Eq)

single :: a -> BinaryTree a
single x = Node (Leaf) x (Leaf)


-- Exercise 1
numberofnodes :: BinaryTree a -> Integer
numberofnodes Leaf = 0
numberofnodes (Node leftSide _ rightSide) = 1 + numberofnodes leftSide + numberofnodes rightSide

-- Exercise 2
height :: BinaryTree a -> Integer
height Leaf = 0
height (Node leftSide _ rightSide) = 1 + max (height leftSide) (height rightSide)

-- Exercise 3
sumnodes :: (Num a) => BinaryTree a -> a
sumnodes Leaf = 0
sumnodes (Node leftSide value rightSide) = value + sumnodes leftSide + sumnodes rightSide

-- Exercise 4
mirror :: BinaryTree a -> BinaryTree a
mirror Leaf = Leaf
mirror (Node leftSide value rightSide) = Node (mirror rightSide) value (mirror leftSide)

-- Exercise 5
flatten :: BinaryTree a -> [a]
flatten Leaf = []
flatten (Node leftSide value rightSide) = flatten leftSide ++ [value] ++ flatten rightSide

-- Exercise 6
treemap :: (a -> b) -> BinaryTree a -> BinaryTree b
treemap _ Leaf = Leaf
treemap f (Node leftSide value rightSide) = Node (treemap f leftSide) (f value) (treemap f rightSide)

-- -------------------------
-- Exercises Binary Search Trees
-- -------------------------

-- Exercise 1
smallerthan :: (Ord a) => a -> BinaryTree a -> Bool
smallerthan _ Leaf = True
smallerthan x (Node leftSide value rightSide) = value < x && smallerthan x leftSide && smallerthan x rightSide

largerthan :: (Ord a) => a -> BinaryTree a -> Bool
largerthan _ Leaf = True
largerthan x (Node leftSide value rightSide) = value > x && largerthan x leftSide && largerthan x rightSide

-- Exercise 2
isbinarysearchtree :: (Ord a) => BinaryTree a -> Bool
isbinarysearchtree Leaf = True
isbinarysearchtree (Node leftSide value rightSide) = smallerthan value leftSide && isbinarysearchtree leftSide && 
                                                           largerthan value rightSide && isbinarysearchtree rightSide

-- Exercise 3
iselement :: (Ord a, Eq a) => a -> BinaryTree a -> Bool
iselement _ Leaf = False
iselement x (Node leftSide value rightSide) =
    if x == value
        then True
    else if x < value
        then iselement x leftSide
    else
        iselement x rightSide

-- Exercise 4
insert :: (Ord a, Eq a) => a -> BinaryTree a -> BinaryTree a
insert x Leaf = Node Leaf x Leaf
insert x (Node leftSide value rightSide) =
    if x == value
        then Node leftSide value rightSide
    else if x < value
        then Node (insert x leftSide) value rightSide
    else
        Node leftSide value (insert x rightSide)

-- Exercise 5
duplicateRemoval :: (Eq a) => [a] -> [a]
duplicateRemoval [] = []
duplicateRemoval (h:t) = h : duplicateRemoval (filter (/= h) t)

createbinarysearchtree :: (Ord a, Eq a) => [a] -> BinaryTree a
createbinarysearchtree [] = Leaf
createbinarysearchtree (h:t) = foldl (\acc y -> insert y acc) Leaf (duplicateRemoval (h:t))

-- Exercise 6
findMin :: (Ord a) => BinaryTree a -> a
findMin (Node Leaf value _) = value
findMin (Node leftSide _ _) = findMin leftSide

removeRoot :: (Ord a, Eq a) => BinaryTree a -> BinaryTree a
removeRoot Leaf = Leaf
removeRoot (Node Leaf _ rightSide) = rightSide
removeRoot (Node leftSide _ Leaf) = leftSide
removeRoot (Node leftSide _ rightSide) =
    let minRight = findMin rightSide
    in Node leftSide minRight (remove minRight rightSide)

remove :: (Ord a, Eq a) => a -> BinaryTree a -> BinaryTree a
remove _ Leaf = Leaf
remove x (Node leftSide value rightSide)= 
  if x < value
  then Node (remove x leftSide) value rightSide
  else if x > value
      then Node leftSide value (remove x rightSide)
      else removeRoot (Node leftSide value rightSide)

----------------------------
-- Exercise Tower of Hanoi
----------------------------

-- comment out the following two lines in case you take a different approach
-- and in that case adapt the type of the function hanoi accordingly
type Rod = String
type Move = (Integer, Rod, Rod)
hanoi :: Integer -> Rod -> Rod -> Rod -> [Move]
hanoi 1 firstRod finalRod helper = [(1, firstRod, finalRod)]
hanoi n firstRod finalRod helper =
    hanoi (n - 1) firstRod helper finalRod ++ [(n, firstRod, finalRod)] ++ hanoi (n - 1) helper finalRod firstRod
    