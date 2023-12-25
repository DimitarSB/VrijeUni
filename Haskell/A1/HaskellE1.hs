
module Practicum1 where

{-
Name:           Dimitar Bachvarov
VU-net id:      dbv900
Student number: 2728704
Discussed with: -
Remarks:        -
Sources:        
https://www.educba.com/haskell-let/
https://mmhaskell.com/blog/2019/5/13/quicksort-with-haskell
http://zvon.org/other/haskell/Outputprelude/abs_f.html
http://zvon.org/other/haskell/Outputprelude/foldr_f.html
https://stackoverflow.com/questions/41791489/list-of-prefixes-in-haskell
-}

-- Exercise 1
maxi :: Integer -> Integer -> Integer
maxi num1 num2 =
    if(num1 > num2)
        then num1
        else num2

-- maxi 10 100 == 100
-- maxi 0 (-78) == 0

-- Exercise 2
fourAscending :: Integer -> Integer -> Integer -> Integer -> Bool
fourAscending num1 num2 num3 num4 =
    if(num1 < num2 && num2 < num3 && num3 < num4)
        then True
        else False

-- fourAscending 1 2 3 4 == True
-- fourAscending 1 2 0 5 == False
-- fourAscending 1 5 5 5 == False

-- Exercise 3
fourEqual :: Integer -> Integer -> Integer -> Integer -> Bool
fourEqual num1 num2 num3 num4 =
    if(num1 == num2 && num2 == num3 && num3 == num4)
        then True
        else False

-- fourEqual 1 2 3 4 == False
-- fourEqual 7 8 7 7 == False
-- fourEqual 1 1 1 1 == True

-- Exercise 4
fourDifferent :: Integer -> Integer -> Integer -> Integer -> Bool
fourDifferent num1 num2 num3 num4 =
    if(num1 /= num2 && num1 /= num3 && num1 /= num4 && 
        num2 /= num3 && num2 /= num4 && 
            num3 /= num4)
        then True
        else False

-- fourDifferent 1 2 3 4 == True
-- fourDifferent 7 8 5 7 == False
-- fourDifferent 1 1 1 1 == False

-- Exercise 5
threeDifferent :: Integer -> Integer -> Integer -> Bool
threeDifferent a b c = 
    if( a /= b && a /= c && b /= c )
        then True
        else False
    
-- The given function returns wrong answer (True) when: a = 1 | b = 2 | c = 1
-- threeDifferent 1 2 1 == False
-- threeDifferent 7 8 5 == True

-- Exercise 6
factorial :: Integer -> Integer
factorial 0 = 1 
factorial f = f * factorial(f - 1)

-- factorial 3 == 6
-- factorial 5 == 120

-- Exercise 7
fib :: Integer -> Integer
fib 0 = 0
fib 1 = 1
fib n = fib(n - 1) + fib (n - 2)

-- fib 3 == 2
-- fib 10 == 55

-- Exercise 8
-- it is possible to define auxiliary functions
strangeSummation :: Integer -> Integer
countDown :: Integer -> Integer -> Integer -> Integer
countDown result 0 incrementor = result
countDown result i incrementor = countDown (result + (incrementor + 1)) (i - 1) (incrementor + 1)
strangeSummation result = countDown result 7 result

-- strangeSummation 2  == 44
-- strangeSummation -2 == 12

-- Exercise 9
lengthList :: [Integer] -> Integer
lengthList []  = 0
lengthList (h:t) = 1 + lengthList t

lengthListAlternative :: [Integer] -> Integer
lengthListAlternative l =
  case l of
    [] -> 0
    (h:t) -> 1 + (lengthListAlternative t)

sumList :: [Integer] -> Integer
traverseAndSum :: [Integer] -> Integer -> Integer
traverseAndSum [] result = result 
traverseAndSum (h:t) result = traverseAndSum t (result + h)
sumList [] = 0
sumList (h:t) = traverseAndSum (h:t) 0

-- sumList [] == 0
-- sumList [-1, -2, -3, -4, -5] == -15
-- sumList [8, 0, 0, 0, -8] == 0

-- Exercise 10
doubleList :: [Integer] -> [Integer]
doubleList [] = []
doubleList (h:t) = 2 * h : doubleList t

-- doubleList [1, 2, 3] == [2,4,6]
-- doubleList [-1, 0, 10, -11] == [-2,0,20,-22]

-- Exercise 11
myappend :: [a] -> [a] -> [a]
myappend [] res = res
myappend (h:t) res = h : myappend t res

-- myappend [1, 2, 3] [0, 0] == [1,2,3,0,0]
-- myappend [1, 2, -11, 0] [100, 0, -87] == [1,2,-11,0,100,0,-87]

-- Exercise 12
myreverse :: [a] -> [a]
myreverse [] = []
myreverse (h:t) = myappend (myreverse t) [h]

-- myreverse [1, 2, 3] == [3,2,1]
-- myreverse [1, 2, -11, 0] == [0,-11,2,1]

-- Exercise 13
mymember :: (Eq a) => a -> [a] -> Bool
mymember a [] = False
mymember a (h:t) = 
    if (a == h)
        then True
        else mymember a t

-- mymember 1 [11,2,3,1] == True
-- mymember 1 [11,2,3] == False

-- Exercise 14
mysquaresum :: [Integer] -> Integer
square :: [Integer] -> [Integer]
square [] = []
square (h:t) = h * h : square t
mysquaresum [] = 0
mysquaresum (h:t) = sumList (square (h:t))

-- mysquaresum [0,-5,1] == 26
-- mysquaresum [] == 0

-- Exercise 15
range :: Integer -> Integer -> [Integer]
range x y = 
    if (x > y)
        then []
        else x : range (x + 1) y

-- range 3 8 == [3,4,5,6,7,8]
-- range (-10) 0 == [-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0]
-- range 10 0 == []

-- Exercise 16
myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (h:t) = h ++ myconcat t

-- myconcat [[1,2,3], [5,7,7]] == [1,2,3,5,7,7]
-- myconcat [[1,-2,3,-1.2], [0,1,0]] == [1.0,-2.0,3.0,-1.2,0.0,1.0,0.0]

-- Exercise 17
insert :: Ord a => a -> [a] -> [a]
insert a [] = [a]
insert a (h:t) =
    if (a > h)
        then h : insert a t 
        else a : h : t

-- insert 1 [-2, -1, 0, 2, 4] == [-2,-1,0,1,2,4]
-- insert 7 [-2, 7, 7, 7] == [-2,7,7,7,7]

insertionsort :: Ord a => [a] -> [a]
insertionsort [] = []
insertionsort (h:t) = insert h (insertionsort t)

-- insertionsort [-1, -100, 100, 0, 5, 8, 7] == [-100,-1,0,5,7,8,100]
-- insertionsort [0, 0, 0, 1, 0, 0, 0] == [0,0,0,0,0,0,1]

-- Exercise 18
minim :: Ord a => [a] -> a
minimHelper :: Ord a => a -> [a] -> a
minimHelper x [] = x 
minimHelper x (h:t) =
    if(x < h)
        then minimHelper x t
        else minimHelper h t
minim (h:t) = minimHelper h t

-- minim [100, 0, 4, 8, -100] == -100
-- minim [1,1,1,1] == 1

removeFirstOccurrence :: Eq t => t -> [t] -> [t]
removeFirstOccurrence t1 [] = []
removeFirstOccurrence t1 (h:t) =
    if (t1 /= h)
        then h : removeFirstOccurrence t1 t
        else t

-- removeFirstOccurrence 3 [2,-1,1,0,0,0,1] == [2,-1,1,0,0,0,1]
-- removeFirstOccurrence 0 [2,-1,1,0,0,0,1] == [2,-1,1,0,0,1]

selectionsort :: Ord a => [a] -> [a]
selectionsort [] = []
selectionsort (h:t) = minim (h:t) : selectionsort (removeFirstOccurrence (minim (h:t)) (h:t)) 

-- filter function:
-- filter odd [1..30] == [1,3,5,7,9,11,13,15,17,19,21,23,25,27,29]
-- filter (\x -> x < 10) [1..20] == [1,2,3,4,5,6,7,8,9]
-- filter (\x -> x < 15 && x > 5) [1..20] == [6,7,8,9,10,11,12,13,14]

-- Exercise 19
findSmaller :: Ord a => a -> [a] -> [a]
findSmaller _ [] = [] 
findSmaller pivot (h:t) =
    if (h <= pivot)
        then h : findSmaller pivot t   
        else findSmaller pivot t

findBigger :: Ord a => a -> [a] -> [a]
findBigger _ [] = [] 
findBigger pivot (h:t) =
    if (h > pivot)
        then h : findBigger pivot t 
        else findBigger pivot t 

quicksort :: Ord a => [a] -> [a]
quicksort [] = [] 
quicksort (h:t) =
    let smaller = findSmaller h t
        larger  = findBigger h t
    in quicksort smaller ++ [h] ++ quicksort larger

-- quicksort [1,0,-2,5,3] == [-2,0,1,3,5]
-- quicksort ["hi", "a", "bye"] == ["a","bye","hi"]

-- Exercise 20
evensB :: [Integer] -> [Integer]
evensB [] = []
evensB (h:t) = [x | x <- (h:t), abs (x) `mod` 2 == 0]

-- evensB [0,1,2,3,4,5,6,7] == [0,2,4,6]
-- evensB [-1,0,-2,8,-78] == [0,-2,8,-78]

-- Exercise 22

-- map (\x -> x * x + 1) [1,2,3] == [2,5,10]
-- map (\x -> x * (-1)) [1,2,3] == [-1,-2,-3]
-- map (\x -> x / (-1) * 0) [1,2,3,0,100] == [-0.0,-0.0,-0.0,-0.0,-0.0]
mymap :: (a -> b) -> [a] -> [b]
mymap _ [] = []
mymap func (h:t) = func h : mymap func t 

-- mymap (\x -> x * x + 1) [1,2,3] == [2,5,10]
-- mymap (\x -> x * (-1)) [1,2,3] == [-1,-2,-3]
-- mymap (\x -> x / (-1) * 0) [1,2,3,0,100] == [-0.0,-0.0,-0.0,-0.0,-0.0]

-- Exercise 23
twice :: (a -> a) -> a -> a
twice f a = f (f a)

-- twice (\x -> x + 1) 3 == 5
-- twice (\x -> x * 3) 3 == 27
-- twice (\x -> x) 0 == 0

-- Exercise 24
compose :: (b -> c) -> (a -> b) -> a -> c
compose f g a = f (g a)

-- compose  (\x -> x * 5) (\x -> x +4) 7 == 55
-- compose  (\x -> x + 4) (\x -> x * 5) 7 == 39

-- Exercise 25
mylast :: [a] -> a
mylast (h:t) = mylastHelper h (h:t)

mylastHelper :: a -> [a] -> a
mylastHelper a [] = a
mylastHelper a (h:t) = mylastHelper (head (h:t)) t

-- mylast [1,2,3,5,6,-100] == -100
-- mylast [1] == 1
-- mylast [1,2,3,5,6,0] == 0

-- Exercise 26
--drop 1 (drop 1 [1,2,3,4]) == [3,4]
mylastb :: [a] -> a
mylastb [a] = a
mylastb (h:t) = head (drop (length (h:t) - 1) (h:t))

-- mylastb [0] == 0
-- mylastb [1,2,3,-1] == -1

-- Exercise 27
myinit, myinitb :: [a] -> [a]

myinit (h:t) = take (length (h:t) - 1) (h:t)

-- myinit [3,8,7,5] == [3,8,7]
-- myinit [0] == []

myinitb (h:t) = reverse (tail(reverse(h:t)))

-- myinitb [3,8,7,5] == [3,8,7]
-- myinitb [0] == []

-- Exercise 28
mysecondconcat :: [[a]] -> [a]
mysecondconcat [[]] = []
mysecondconcat (h:t) = foldr (\x emptyL -> x ++ emptyL) [] (h:t)

-- mysecondconcat [[1,2,3], [1,2,3], [0,0]] == [1,2,3,1,2,3,0,0]
-- mysecondconcat [[], [-100], [8,7]] == [-100,8,7]
-- mysecondconcat ["hi", "bye"] == "hibye"

mysecondreverse :: [a] -> [a]
mysecondreverse [] = []
mysecondreverse (h:t) = foldr (\x emptyL -> emptyL ++ [x]) [] (h:t)

-- mysecondreverse [1,2,3,4,5] == [5,4,3,2,1]
-- mysecondreverse [-1,5,5,0] == [0,5,5,-1]
-- mysecondreverse ["hello", "hi"] == ["hi","hello"]


-- Exercise 28
mythirdconcat :: [[a]] -> [a]
mythirdconcat [[]] = []
mythirdconcat (h:t) = foldl (\x emptyL -> x ++ emptyL) [] (h:t)

-- mythirdconcat ["hi", "bye"] == "hibye"
-- mythirdconcat [[1,2,3], [1,2,3], [0,0]] == [1,2,3,1,2,3,0,0]
-- mythirdconcat [[], [-100], [8,7]] == [-100,8,7]

mythirdreverse :: [a] -> [a]
mythirdreverse [] = []
mythirdreverse (h:t) = foldl (\emptyL x -> [x] ++ emptyL) [] (h:t)

-- mythirdreverse ["hello", "hi"] == ["hi","hello"]
-- mythirdreverse [-1,5,5,0] == [0,5,5,-1]

-- Exercise 29

prefix :: [a] -> [[a]]
prefix [] = [[]]
prefix (h:t) = [] : (map (h :) (prefix t))

-- prefix [1,2,3,-1] == [[],[1],[1,2],[1,2,3],[1,2,3,-1]]
-- prefix [0,0] == [[],[0],[0,0]]

-- Exercise 30

suffix :: [a] -> [[a]]
suffix [] = [[]]
suffix (h:t) = (h:t) : suffix t

-- suffix [1,2,3] == [[1,2,3],[2,3],[3],[]]
-- suffix ["hi", "bye", "fry", "cry"] == [["hi","bye","fry","cry"],["bye","fry","cry"],["fry","cry"],["cry"],[]]
