 I didn't do check situation .Recursion function works but return always true becasue of the if statement ( I defined in this problem when it occurs)
so the program don't stop when x or o wins 

2nd problem is the letters don't change to capital again (check function problem)

3rd problem Also special situation that programs error FOR EXAMPLE;

	    A B
	1   X X . .
	2    X . . .
	3     . . . .
	4	. . . . 


like this situation orogram checks one way to bcktrace and doesn't go there but it didn't check second way 
Explaining : 

program check A1's possible movement B1,A2
if it goes B1 then program closes the way go back so it can't go back on B1 coordinant 
but B1 possible moves is A1 so it can't close this path and it cause a loop
