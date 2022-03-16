# CHESS-C-console-app
Description
The white pieces are represented in lowercase letters and the black pieces are represented by capital letters. They are all represented by the first letter of their names, the only exception being the Knight, which is represented by an N, leaving the K for the king).
The white squares are represented by “ . ” and the black squares are represented by “ - ”.
The pieces that are taken out from both players are shown above the board.

If the white player tries to move black pieces or the opposite, the program will print “Not valid!”.
If a player tries to move an empty square, the program will print “Not valid!”.
At every move the program check first that this move does not make the king in check and if it does, the program will print “Not valid move!” and ask the user again. 
The game ends with draw in case one of the following:
•	King versus king
•	King and bishop versus king
•	King and knight versus king
•	King and bishop versus king and bishop with the bishops with the same color.
Or when a player is not checked and there is no legal move to do, the program will print “The game ends with DRAW!”.

Features:
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

Overview of the design:
Firstly, we make a 2D array of characters and assign to it the initial state of the chess board, after scanning the input from the user we check if this valid move for this piece by making a function for every piece that check this move, then we do this move, and we check if this move make the king in danger, if true we undo this move, and ask the user for valid move, then we print the captured pieces array and display the board, if this move was a king or any of the rooks but not castling we  prevent the user to castle after that, then we check if this move check the opponent king or not, if it check the king the other player will play the move that get the king out of check like trying to move the king, capture the attacking piece or defend the king by another piece, Our program count the number of available moves for the attacked player, if there is no available moves to get out of check then the other player has won.
At every move we count the number of valid moves, if there is no valid move for the player and his king is not under attack, then the game ends with draw.
At every valid move we save it to a temp array, if the user undo once, we read the moves from this array except the last one and do them, and so on.
If the user redo a move, we read the moves from the array and do moves higher than the number of undo by one.
If the user needs to save the game, we will ask him about the file name and copy the content of the temp array to this file, and when he loads the game, he will enter the file name which he saved it, and we will read the moves from this file and do it.
If the user wants a new game, we will reset the board and clear the temp array.





Assumptions
•	In case of promotion, the user shouldn’t specify an additional character for the promoted piece, but he enter the original move like (a7a8) then the program will ask for the promoted piece.
•	In case of en-passant, the user doesn’t lose the right to do the en passant capture if he didn’t do it on the very next turn.
•	If the king is under check and the castling is valid, he can’t castle, and the program will print “you can’t do this move”.
•	If the king or one of the rooks moved from his start position them the castling will not valid any more in the game.

Description of the important functions
Promotion (); this function check if the white pawn reached to row 8 or the black pawn reached to row 1 and scan the promoted piece from the user and it returns that piece to replace it with this pawn.
Enpassent (); this function check if the white pawn moves to an empty square from row 5 to row 6 and the piece that in his row and the column next to it is black pawn and put it in the taken array, and if the black pawn moves to an empty square from row 4 to row 3 and the piece that in his row and the column next to it is white pawn and put it in the taken array.
Castling (); we check first if this piece is a white or black king and in row 1 or 8, and if this piece is white king, we check if the rook in her place and the squares between them are empty, and the same with the black king, then we return true.  
validRookMove (); this function checks firstly the horizontal move, if the rook moves from row to the same row, then check that the squares in his way are empty and return true if the destination cell is free. secondly, check the vertical move, if the rook moves from column to the same column, then check that the squares in his way are unoccupied, and return true if the destination cell is free.
validBishopMove (); this function checks the diagonal move for the bishop, if the index of his row plus his column equals the index of destination row plus destination column (right diagonal), or if the index of his column minus his row equals the index of destination column minus destination row (left diagonal), it returns true.
validQueenMove (); this function calls two function, for the horizontal move it calls validRookMove function, and for the diagonal move it calls validBishopMove function.
validKnightMove (); this function checks for the valid moves for the knight, if he moves two squares vertically and one square horizontally, or two squares horizontally and one square vertically, and the destination cell is free or occupied by the enemy piece.
validkingMove (); this function checks if the king can move one square in any direction (horizontally, vertically, or diagonally), and the destination cell is free or occupied by enemy piece, or if castling function returns true and the destination cell is not under attack from any of the enemy pieces by the help of global variable (notValidMove).
validCapturePawn (); this function checks the diagonal move for the pawn, if the white pawn moved from his row to row up and to column to his right or left and the destination cell is occupied by any black piece, and the same with the black pawn, then it returns true. 
validPawnMove (); this function checks firstly the vertical pawn move, if the white pawn move one row up or the black pawn move one row down, and the destination cell is empty, or if white pawn moved from row 2 to row 4 or the black pawn moved from row 7 to row 5 and the destination cell is empty, secondly it calls the validCapturePawn function, then it calls the enpassent function.
Check (); this function knows if the king is in check from the attacker piece, we check if the king is under attack from every valid move to the attacker piece.
PieceAttackTheKing (); if a player moved a piece we check if his king is under attack after this move or not.
numberOfMoves (); this function counts the number of valid moves in current turn, if the turn is on the white it checks the valid moves for all white pieces and for every valid move the white king should not be in check.
numberOfPieces (); this function count how many pieces of same kind in the board, it helps us in draw function.
 Draw (); it checks for the dead positions, firstly it checks if the white and black king only on the board. Secondly, it checks if a white king and one bishop with black king only on the board and the opposite. Then, it checks if a white king and one knight with black king only on the board and the opposite. Then it checks if a white king and bishop with black king and bishop only on the board and the bishops are on the same type of squares.
readMoves (); this function reads the moves from the txt file and store them in a temp array.
Load (); this function calls readmoves() function and do all this moves and print the captured pieces.
Undo (); this function calls the load() function but with different parameters  depending on the number of undo, e.g. when number of undo equal one the load function do all the moves except the last one. 
Redo (); this function calls also the load() function but it minus the number of undo, e.g. when number of undo equal one he becomes zero and the load function do all the moves.
afterUndo (); if the a player undo then moved a piece this function remove all the moves after this play.
Save (); it saves the moves in the temp array to a txt file.
