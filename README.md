# Associated with Alexandria University

## CHESS-C-console-app
### Description
The white pieces are represented in lowercase letters and the black pieces are represented by capital letters. They are all represented by the first letter of their names, the only exception being the Knight, which is represented by an N, leaving the K for the king).
The white squares are represented by “ . ” and the black squares are represented by “ - ”.
The pieces that are taken out from both players are shown above the board.

If the white player tries to move black pieces or the opposite, the program will print “Not valid!”.
If a player tries to move an empty square, the program will print “Not valid!”.
At every move the program check first that this move does not make the king in check and if it does, the program will print “Not valid move!” and ask the user again. 
The game ends with draw in case one of the following:
-	King versus king
-	King and bishop versus king
-	King and knight versus king
-	King and bishop versus king and bishop with the bishops with the same color.
Or when a player is not checked and there is no legal move to do, the program will print “The game ends with DRAW!”.

### Features:
1.	Castling:
 You can castle right or left if there is the first move to each of the king or any of the two rooks, and the squares between them are empty, if the king is under attack it will not castle in this condition, and if the king destination of castling is under attack from opponent’s piece it will not castle, and the program will print “you can’t do this move”.

2.	Promotion:
 If the white pawn arrives to row 8 the program will ask you to the promoted piece and the same if the black pawn arrives to row 1.

3.	En passant:
It is a special pawn capture that can only occur immediately after a pawn makes a move of two squares from its starting square, and it could have been captured by an enemy pawn had it advanced only one square. The opponent captures the just-moved pawn "as it passes" through the first square.

4.	Redo the promotion
After doing the promotion and replacing the pawn by the promoted piece and undone this play then redo it, we are saving the move with its promoted piece like (a7a8q), and during the redo we replace that pawn with the promoted piece.

5.	Undo the loaded game
if the user saved the game and then he loaded it, he can undo the till the first move.

### Overview of the design:
Firstly, we make a 2D array of characters and assign to it the initial state of the chess board, after scanning the input from the user we check if this valid move for this piece by making a function for every piece that check this move, then we do this move, and we check if this move make the king in danger, if true we undo this move, and ask the user for valid move, then we print the captured pieces array and display the board, if this move was a king or any of the rooks but not castling we  prevent the user to castle after that, then we check if this move check the opponent king or not, if it check the king the other player will play the move that get the king out of check like trying to move the king, capture the attacking piece or defend the king by another piece, Our program count the number of available moves for the attacked player, if there is no available moves to get out of check then the other player has won.
At every move we count the number of valid moves, if there is no valid move for the player and his king is not under attack, then the game ends with draw.
At every valid move we save it to a temp array, if the user undo once, we read the moves from this array except the last one and do them, and so on.
If the user redo a move, we read the moves from the array and do moves higher than the number of undo by one.
If the user needs to save the game, we will ask him about the file name and copy the content of the temp array to this file, and when he loads the game, he will enter the file name which he saved it, and we will read the moves from this file and do it.
If the user wants a new game, we will reset the board and clear the temp array.

### Assumptions
-	In case of promotion, the user shouldn’t specify an additional character for the promoted piece, but he enter the original move like (a7a8) then the program will ask for the promoted piece.
-	In case of en-passant, the user doesn’t lose the right to do the en passant capture if he didn’t do it on the very next turn.
-	If the king is under check and the castling is valid, he can’t castle, and the program will print “you can’t do this move”.
-	If the king or one of the rooks moved from his start position them the castling will not valid any more in the game.

### Sample Runs
#### Begining
![image](https://user-images.githubusercontent.com/73740339/176269417-2a21e578-3580-4eab-919f-c194c022f297.png)
#### Promotion
![image](https://user-images.githubusercontent.com/73740339/176269558-a6b8a184-a492-4dea-b62c-dc18c62da335.png)
#### Checkmate
![image](https://user-images.githubusercontent.com/73740339/176269661-57738e5b-f938-4ce1-91be-173b54a18387.png)
![image](https://user-images.githubusercontent.com/73740339/176269713-ccf1cfb7-133d-4f20-9f82-1a138311c7dd.png)
#### Draw
![image](https://user-images.githubusercontent.com/73740339/176269812-b943353a-d9d6-4052-8579-11492fcc5387.png)
#### Win
![image](https://user-images.githubusercontent.com/73740339/176269916-fa5d6a2e-78fb-4445-95da-5009ad68818c.png)
![image](https://user-images.githubusercontent.com/73740339/176269943-25f1fad5-34ea-4f04-89df-cf5aea9dbe6c.png)
#### Save & Load
![image](https://user-images.githubusercontent.com/73740339/176269978-118d1942-b41d-411f-9599-2b8c74c82324.png)
![image](https://user-images.githubusercontent.com/73740339/176270062-8a6bf5e6-0a43-4778-b05e-2f9e47dfebe6.png)
#### Undo & Redo
![image](https://user-images.githubusercontent.com/73740339/176270266-35e5006c-e351-4821-98ea-e036b7edc22c.png)
![image](https://user-images.githubusercontent.com/73740339/176270347-b8302239-7043-4d0b-965d-890d087ca47c.png)
