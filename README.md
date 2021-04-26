8x8 Checkers project by Team 34
Alphabetically - Hardik, Mayank, Nachiket, Rahul, Sukhjinder



External Libraries used
rlutil: https://github.com/tapio/rlutil


#ANALYSIS and EXPLANATATION---------

1. first of all we have to use some std data types to store position....to do we have made 5 structs as follows - 
a.pawn it stores - x co-ordinate, y co-ordinate, is it White/Black, is_king
b.coords - stores x co-ordinate, y co-ordinate. (though it isn't neccesary, but we found it to be rather useful)
c.game_state - our main course, it store the current state of board. it cantains an array of pawn structs for white and black, it contains turn specifier, (and a 4th if you see....that was majboori for colour..). above pawn struct was thus came naturally from here
d.move - it cantains name(info. regarding it..) of the pawn, its new x and y co-ordinates. it isn't obvious why we made it, but think like this we have a function that tells the best move....we naturally made a struct specially for it, its outputs a move struct......we are thinking of making a bot (whom i am telling too though, we all know ????)
e.undostack - this is obvious, an stack using double linked list to store entire game log (....we typedef it to log), it cantains the current gamestate, next and prev ptr to prev and fwd gamestates(..you get what i want to say, not exactly gamestate, but to undostack)

2.now are basic data types are out in wild, we are left to the task of giving life to the functions. we have many function in place but most of them are just formed out of making a clean big imp function...(like move_enter req check func which further req. draw,win/lost,legal, also move_enter req. to update undo stack.. and lots more). So i will mention in the clean way-

//starting game
we have 2 function playing with 'bot' and with 'friend', also in it function 'start' is used(of O(1)) and a function 'toss' is used.
#########################################################################its analysis

// within game we might need to resign, or offer a draw or results need to be published
we have resign, askdraw.
#########################################################################its analysis

//updating the board
A.in this we have first the 'move_enteries' function, the imp of all. what it does is 
first it checks if that (it takes game state, pawn, hori, vert as input where hori is new x and similarly vert is new y), pawn really do exist using fuction called is_present(g,P) (in O(1)), then it checks if that move is legal or not(we will talk about it separately as its very big), then after validation we just 'update'(updating the turn and promoting the pawn to king is done in controller function) the game state simplily using for loops (O(1)).
now as said lets talk about is_legal(P,new pawn,gamestate), it checks if the movement of pawn P to its new position given in new pawn valid. it checks in 4 steps-
a. if the new pawn position going outside the board. (O(1))
b. we all know a white pawn allways inc its y-coordinate and black dec (bottom left is 0,0), so we checks this (that new pawn.y > P.y in case of white and similarly for black in O(1)). aslo now user might even makes absurd hori and ver like pawn moving 3 times up and 2 times right..such acts are wrong. and we correct that in O(1), (the diff. is 1/2 and angle or diff in x and y is equal)
c. now we check whether that new pawn position is occupied or not in O(1)
d. now we check whether it follows capture rules or not. in O(1) using capture function..though it looks very big, its very intutive and easy to follow. just read the code and see..explaining every word/action in words is very tidious.....
(in this function movee_entries we have used many functions- ispresent, islegal, isoccupied, capturepossible) 

B.simple move check, checks whether the position to which move is being moved empty or not. its as says simple and O(1)

C.
