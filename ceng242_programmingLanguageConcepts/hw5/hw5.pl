:- module(hw5, [complete_path/5]).
check(east).
check2(west).
check3(south).
check4(north).	
check5(unknown).



complete_path(A, position(B,C),position(D,E),P,CP) :-
	var(CP) -> complete(A, position(B,C),position(D,E),P,CP);
	complete(A, position(B,C),position(D,E),P,CP), !.		


complete(A,position(B,C),position(D,E),[],[]) :-
	B =:= D,
	C =:= E.
complete(A, position(B,C), position(D,E), [H|T],P) :-
	check(H),	
	B1 is B + 1,
	C1 is C + 0,
	A > B1,
	append([H],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check(H),
	B1 is B+1,
	C1 is C+0,
	A =:= B1,
	append([],P1,P),
	complete(A,position(B,C),position(D,E),T,P1);
	check2(H),	
	B1 is B - 1,
	C1 is C + 0,
	-1 =:= B1,
	append([],P1,P),
	complete(A,position(B,C),position(D,E),T,P1);
	check2(H),	
	B1 is B - 1,
	C1 is C + 0,
	-1 < B1,
	append([H],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check3(H),	
	B1 is B + 0,
	C1 is C + 1,
	A > C1,
	append([H],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check3(H),
	B1 is B+0,
	C1 is C+1,
	A =:= C1,
	append([],P1,P),
	complete(A,position(B,C),position(D,E),T,P1);
	check4(H),	
	B1 is B + 0,
	C1 is C - 1,
	-1 < C1,
	append([H],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check4(H),
	B1 is B + 0,
	C1 is C - 1,
	-1 =:= C1,
	append([],P1,P),
	complete(A,position(B,C),position(D,E),T,P1);
	check5(H),
	B1 is B + 1,
	C1 is C + 0,
	A > B1,
	append([east],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check5(H),	
	B1 is B - 1,
	C1 is C + 0,
	-1 < B1,
	append([west],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check5(H),	
	B1 is B + 0,
	C1 is C + 1,
	A > C1,
	append([south],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1);
	check5(H),	
	B1 is B + 0,
	C1 is C - 1,
	-1 < C1,
	append([north],P1,P),
	complete(A,position(B1,C1),position(D,E),T,P1).

