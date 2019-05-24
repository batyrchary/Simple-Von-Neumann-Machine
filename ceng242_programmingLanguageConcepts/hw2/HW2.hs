
module HW2(FeatureStruct, FeatureTerm(Simple, Struct), emptyfs, getpath, addpath, delpath, union, intersect) where

data FeatureTerm = Simple String | Struct FeatureStruct
data FeatureStruct = FS [(String, FeatureTerm)]
 
emptyfs     :: FeatureStruct
getpath     :: FeatureStruct -> [String] -> Maybe FeatureTerm
addpath     :: FeatureStruct -> [String] -> FeatureTerm -> FeatureStruct
delpath     :: FeatureStruct -> [String] -> FeatureStruct
union       :: FeatureStruct -> FeatureStruct -> Maybe FeatureStruct
intersect   :: FeatureStruct -> FeatureStruct -> FeatureStruct

-- DO NOT MODIFT ABOVE

instance Show FeatureTerm where
	show (Simple s) = "\"" ++ s ++ "\""
	show (Struct f) = (show f)


    -- Implement it here
instance Show FeatureStruct where
	show f = "[" ++ (shower f) ++ "]"

shower :: FeatureStruct -> String		
shower (FS []) = ""
shower (  FS [(x , (Simple y))]) = x ++ "=" ++ (show y)
shower (  FS [(x , (Struct y))]) = x ++ "=>" ++ "[" ++ (shower y) ++ "]"
shower (  FS ((x , (Simple y)) :f)) = x ++ "=" ++ (show y) ++ ", " ++ (shower (FS f))		
shower (  FS ((x , (Struct y)) :f)) = x ++ "=>" ++ "[" ++ (shower y) ++ "]" ++ ", " ++ (shower (FS f))

instance Eq FeatureStruct where
	(==) f1 f2 = (show f1) == (show f2)    
	

-- Implement it here


----------------------------------------------------

--emptyfs     :: FeatureStruct

emptyfs = FS []
----------------------------------------------------


--getpath (FS []) [] = Just (Struct (FS [])) 
getpath (FS []) xs = Nothing 
getpath (FS f) [] = Nothing
--getpath (FS f) [] = Just (Struct (FS f))


getpath (FS ((x,(Simple y)) :f))  (s:xs) = if ((x == s) &&  (xs ==[])) <= False then (getpath (FS f) (s:xs)) 
						else Just (Simple y)


getpath (FS ((x,(Struct (FS y))) :f) ) (s:xs) = if ((x == s) && (xs ==[])) then (Just (Struct (FS y)))
							else if  ((x == s) && (xs /= [])) then (getpath (FS y) xs)
								else (getpath (FS f) (s:xs))


---------------------------------------------------------------------------------------------------------

ekleyci :: [String] -> FeatureTerm -> (String,FeatureTerm)
ekleyci (s:xs) (Simple v) = if (xs == []) then (s,Simple v)
				else (s,Struct (FS [(ekleyci xs (Simple v))]))

ekleyci (s:xs) (Struct p) = if (xs == []) then (s,Struct p)
				else (s,Struct (FS[(ekleyci xs (Struct p))]))


--addpath     :: FeatureStruct -> [String] -> FeatureTerm -> FeatureStruct

add :: FeatureStruct -> FeatureStruct -> FeatureStruct

add (FS []) f =  f
add f (FS []) =  f

add (FS(f1:f11)) (FS(f2:f22)) =  FS((f1:f11) ++ (f2:f22))

addpath (FS []) s (Simple v) = FS [(ekleyci s (Simple v))]
addpath (FS []) s (Struct p) = FS [(ekleyci s (Struct p))]
addpath (FS ((x, (Struct (FS y))) :f))  (s:xs) v_p = if ((x==s)  && (xs==[])) then FS ((ekleyci [s] v_p):f) 
						else if ((x==s) && (xs /= [])) then FS( [(x, (Struct(addpath (FS y) xs v_p)))] ++ f )
						else if (x<s) then (add(FS [(x,(Struct (FS y)))]) (addpath (FS f) (s:xs) v_p))
						else (add (addpath (FS []) (s:xs) v_p) (FS ((x, (Struct (FS y))) :f)))  
addpath (FS ((x, (Simple y)) :f))  (s:xs) v_p = if ((x==s) && (xs==[])) then FS ((ekleyci [s] v_p):f) 
						else if ((x==s) && (xs /= [])) then  FS ((ekleyci (s:xs) v_p):f)
						else if (x<s) then (add (FS [(x,(Simple y))]) (addpath (FS f) (s:xs) v_p))
						else (add (addpath (FS[]) (s:xs) v_p) (FS ((x, (Simple y)) :f))   )


--------------------------------------------------------------------------------------------------------



delpath f [] = f
delpath (FS []) xs = (FS []) 


delpath (FS ((x, (Simple y)) :f))  (s:xs) = if ((x==s) && (xs==[])) then (FS f) 
						else if ((x==s) && (xs /= [])) then (FS f) -- (FS ((x, (Simple y)) :f))    
						else (add (FS [(x,(Simple y))]) (delpath (FS f) (s:xs) ))
						
						
						
delpath (FS ((x, (Struct (FS y))) :f))  (s:xs) = if ((x==s)  && (xs==[])) then (FS f) 
						else if ((x==s) && (xs /= [])) then FS( [(x, (Struct(delpath (FS y) xs)))] ++ f )
						else  (add(FS [(x,(Struct (FS y)))]) (delpath (FS f) (s:xs)))





-----------------------------------------------------------------------------------------------------
--union       :: FeatureStruct -> FeatureStruct -> Maybe FeatureStruct




addU :: Maybe FeatureStruct -> Maybe FeatureStruct -> Maybe FeatureStruct

addU (Just (FS [])) (Just f) = (Just f)
addU (Just f) (Just (FS [])) =  (Just f)

addU (Just (FS(f1:f11))) (Just (FS(f2:f22)) )= (Just (FS((f1:f11) ++ (f2:f22))))


converter :: Maybe FeatureStruct -> FeatureStruct 
converter Nothing = (FS [])
converter (Just (FS f)) = (FS f)


union (FS []) (FS []) = (Just (FS []))

union (FS []) (FS f) = (Just (FS f))

union (FS f) (FS []) = (Just (FS f))



union (FS ((x1, (Struct (FS y1))) :f1)) (FS ((x2, (Struct (FS y2))) :f2)) = if ((x1==x2)  && (  (union (FS y1) (FS y2)) /= Nothing    )) then (addU (Just (FS [(x1, (Struct  (converter (union (FS y1) (FS y2)))))]))  (union (FS f1) (FS f2)))
										else if ((x1==x2) && ((union (FS y1) (FS y2)) == Nothing) ) then Nothing
										else if (x1<x2) then (addU (Just (FS [(x1, (Struct(FS y1)))])) (union (FS f1) (FS ((x2, (Struct (FS y2))) :f2)))  )
										else  (addU (Just (FS [(x2, (Struct(FS y2)))])) (union (FS ((x1, (Struct (FS y1))) :f1)) (FS f2)))





union (FS ((x1, (Struct (FS y1))) :f1)) (FS ((x2, (Simple y2)) :f2))    = if (x1==x2) then Nothing 
										else if ((x1 /= x2) && (x1<x2)) then (addU (Just (FS [(x1, (Struct(FS y1)))])) (union (FS f1) (FS ((x2, (Simple y2)) :f2)))    )
										
										else (addU (Just (FS [ (x2, (Simple y2))])) (union (FS ((x1, (Struct (FS y1))) :f1)) (FS f2))    )
										



union   (FS ((x1, (Simple y1)) :f1)) (FS ((x2, (Struct (FS y2))) :f2)) = if (x1==x2) then Nothing 
										else if ((x1 /= x2) && (x1<x2)) then (addU (Just (FS [ (x1, (Simple y1))])) (union  (FS f1) (FS ((x2, (Struct (FS y2))) :f2)) )    )
										else (addU (Just (FS [(x2, (Struct(FS y2)))])) (union (FS ((x1, (Simple y1)) :f1)) (FS f2) )    )
										
										

union   (FS ((x1, (Simple y1)) :f1)) (FS ((x2, (Simple y2)) :f2)) = if ((x1 == x2) && (y1 == y2)) then (addU (Just (FS [ (x1, (Simple y1))]))  (union (FS f1) (FS f2)) )
									else if ((x1==x2) && (y1 /= y2)) then Nothing
									else if ((x1/=x2) && (x1 < x2)) then (addU (Just (FS [ (x1, (Simple y1))])) (union (FS f1) (FS ((x2, (Simple y2)) :f2)))    )
									
									else (addU (Just (FS [ (x2, (Simple y2))]))  (union (FS ((x1, (Simple y1)) :f1)) (FS f2) ))



---------------------------
--intersect   :: FeatureStruct -> FeatureStruct -> FeatureStruct


intersect (FS []) (FS []) = (FS [])

intersect (FS []) (FS f) = (FS [])

intersect (FS f) (FS []) = (FS [])



intersect (FS ((x1, (Simple y1)) :f1)) (FS f2) = if ( ((union (FS [(x1, (Simple y1))]) (FS f2)) /= Nothing) && ((converter (union (FS [(x1, (Simple y1))]) (FS f2))) == (FS f2))) then (add (FS [(x1, (Simple y1))]) (intersect (FS f1) (FS f2)))
										else (intersect (FS f1) (FS f2))


intersect (FS ((x1, (Struct (FS y1))) :f1)) (FS ((x2, (Struct (FS y2))) :f2)) = if (x1 == x2) then (add  (FS [(x1,(Struct (intersect (FS y1) (FS y2) )))])  (intersect (FS f1) (FS f2))) 
												else (intersect (FS f1) (FS ((x2, (Struct (FS y2))) :f2)) )


intersect (FS ((x1, (Struct (FS y1))) :f1)) (FS ((x2, (Simple y2)) :f2))  = if (x1 == x2) then (add  (FS [])  (intersect (FS f1) (FS f2))) 
												else (intersect (FS f1) (FS ((x2, (Simple y2)) :f2))) 







