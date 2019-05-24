module HW1 where

--Data
------

type RealName = String
type UserName = String
type GroupName = String
type Message = String

data Post    = Post UserName Message deriving (Show, Eq)
data To 	 = UserID UserName | GroupID GroupName deriving (Show, Eq)
data User    = User UserName RealName [UserName] [Post] deriving (Show, Eq)
data Group   = Group GroupName [UserName] [Post] deriving (Show, Eq)
data DB		 = DB [User] [Group] deriving (Show, Eq)

--1. Commands

newUser      :: DB -> User -> DB
addFriend    :: DB -> UserName -> UserName -> DB
sendPost 	 :: DB -> UserName -> Message -> [To] -> DB
newGroup 	 :: DB -> GroupName -> DB
addMember 	 :: DB -> GroupName -> UserName -> DB
removeMember :: DB -> GroupName -> UserName -> DB

--2. Queries

getFriendNames :: DB -> UserName -> [RealName]
getPosts 	   :: DB -> To -> [Post]
listGroups 	   :: DB -> UserName -> [Group]
suggestFriends :: DB -> User -> Int -> [User]

---- IMPLEMENTATIONS ----
varmi :: [User] -> UserName -> Bool
varmi [] u = True					
varmi ( (User ux rx ulx plx) : lu ) u = (not( ux == u )) && (varmi lu u)


newUser (DB [] [] ) x = DB [x] []
newUser (DB lu lg ) (User ux rx ulx plx)  | bmi <= False =  (DB ((User ux rx ulx plx):lu) lg)
							   	  | otherwise =(DB lu lg)
							    where bmi = not (varmi lu ux) 	

-----------------------------------------------------------------------------------------------------------------

ekleyci :: [User] -> UserName -> UserName -> [User]
ekleyci [] u1 u2 = []
ekleyci ((User ux rx ulx plx) : lu) u1 u2 = if (not(ux == u1)) <= False then (User ux rx (u2:ulx) plx):(ekleyci lu u1 u2)
										else if (not(ux == u2)) <= False then (User ux rx (u1:ulx) plx):(ekleyci lu u1 u2)
											else (User ux rx ulx plx):(ekleyci lu u1 u2)
addFriend (DB [] lg ) _ _ = (DB [] lg ) 
addFriend (DB lu lg ) u1 u2 = (DB (ekleyci lu u1 u2) lg)

-----------------------------------------------------------------------------------------------------------------

sender_yardimci1 :: Post -> [User] -> String -> [User] 
sender_yardimci2 :: Post -> [Group] -> String -> [Group] 

sender_yardimci1 p [] uid = []
sender_yardimci1 p ((User un r ul1 pl) :ul) uid = if ((uid == un) && (notElem p pl) ) <= False then (User un r ul1 pl) : (sender_yardimci1 p ul uid)
						else  (User un r ul1 (p:pl)) : (sender_yardimci1 p ul uid)



sender_yardimci2 p [] gid = []
sender_yardimci2 p ((Group gn ul pl) : gl) gid = if ((gid == gn) && (notElem p pl) )  <= False then (Group gn ul pl) : (sender_yardimci2 p gl gid)
						else  (Group gn ul (p:pl)) : (sender_yardimci2 p gl gid)

bulucu :: [Group] -> String -> [UserName]
bulucu [] g = []
bulucu ((Group gn ul pl) : gl) gid = if (gid == gn) <= False then (bulucu gl gid)
					else ul 



sender_yardimci22 :: Post -> [User] -> [UserName] -> [User]

sender_yardimci22 p lu [] = lu
sender_yardimci22 p lu (u:unl) = (sender_yardimci22 p (sender_yardimci1 p lu u) unl )




sender :: Post -> DB -> To -> DB
sender p (DB lu lg) (UserID u) = (DB (sender_yardimci1 p lu u) lg)
sender p (DB lu lg) (GroupID g) = (DB (sender_yardimci22 p lu (bulucu lg g)) (sender_yardimci2 p lg g))

sendPost (DB lu gu ) u m [] = (DB lu gu) 
sendPost (DB lu gu ) u m (t:to_list) = sendPost (sender (Post u m) (DB lu gu) t) u m to_list 

----------------------------------------------------------------------------------------------------------------
newGroup (DB lu []) x = (DB lu [(Group x [] [])])
newGroup (DB lu lg) x = (DB lu ((Group x [] []):lg))
-----------------------------------------------------------------------------------------------------------------


gruba_ekleyci :: [Group] -> GroupName -> UserName -> [Group]
gruba_ekleyci [] gn un = []
gruba_ekleyci ((Group gn1 ul pl):lg) gn un = if ((gn1 == gn) && (not(elem un ul)) ) <= False then  ((Group gn1 ul pl) : (gruba_ekleyci lg gn un) )   
										else ((Group gn1 (un:ul) pl ):(gruba_ekleyci lg gn un))

addMember (DB lu lg ) gn un = (DB lu (gruba_ekleyci lg gn un))


------------------------------------------------------------------------------------------------

remover_y :: [UserName] -> UserName -> [UserName]
remover_y [] un = []
remover_y (u:ul) un = if (u == un) <= False then (u:(remover_y ul un))
					else (remover_y ul un)

removerci :: [Group] -> GroupName -> UserName -> [Group]
removerci [] gn un = []
removerci ((Group gn1 ul pl):lg) gn un = if ((gn1==gn) && (elem un ul))<= False then ((Group gn1 ul pl) : (removerci lg gn un))
					else (Group gn1 (remover_y ul un) pl):(removerci lg gn un) 
														

removeMember (DB lu [] ) gn un = (DB lu [])

removeMember (DB lu lg ) gn un = (DB lu (removerci lg gn un) )

---------------------------------------------------------------------------------------------------



gercekden_alici :: [UserName] -> [User] -> [RealName]
gercekden_alici ul [] = []
gercekden_alici ul ((User u2 r2 ul2 pl2):lu2) = if(elem u2 ul) <= False then   (gercekden_alici ul lu2)
										else (r2 : (gercekden_alici ul lu2))

alici :: [User] -> [User] -> UserName -> [RealName]
alici ((User u1 r ul pl):lu1) lu2 u  = if (u1 == u) <= False then (alici lu1 lu2 u)
									else (gercekden_alici ul lu2)

getFriendNames (DB lu gl) u = (alici lu lu u) 


---------------------------------------------------------------------------------------------

getPosts (DB [] lg )  (UserID u) = []
getPosts (DB ((User u1 r ul pl) : lu) lg ) (UserID u) | bmu1 <= False = (getPosts (DB lu lg) (UserID u))
										    | otherwise = pl ++ (getPosts (DB lu lg) (UserID u))
										where bmu1 = (u1==u)
getPosts (DB lu [] )  (GroupID g) = []
getPosts (DB lu ((Group gn ul pl ):lg) ) (GroupID g) | bmu <= False = (getPosts (DB lu lg) (GroupID g))
										   | otherwise = pl ++ (getPosts (DB lu lg) (GroupID g))
										where bmu = (gn==g)

---------------------------------------------------------------------------------------------------

listGroups (DB lu [] ) u = []
listGroups (DB lu ((Group gn ul pl ):lg)) u |  bmu <= False = (listGroups (DB lu lg) u)
								    | otherwise = [(Group gn ul pl)] ++ (listGroups (DB lu lg) u)
										where bmu = (elem u ul)
-----------------------------------------------------------------------------------------------------

common_finder :: [UserName] -> [UserName] -> Int
common_finder [] unl2 = 0
common_finder (u1:unl1) unl2 = if (elem u1 unl2) <= False then (0 + (common_finder unl1 unl2))
							else (1 + (common_finder unl1 unl2))

checker :: [User] -> UserName ->[UserName] -> Int ->[User]

checker [] un ul i = []
checker ((User un1 rn1 ul1 pl1):lu) un ul i = if ((not (un1==un)) && (not (elem un1 ul) ) && ( i <= (common_finder ul1 ul))) <= False then (checker lu un ul i)
										else ((User un1 rn1 ul1 pl1) : (checker lu un ul i) ) 


suggestFriends (DB lu lg) (User un rn ul pl) i = (checker lu un ul i)



