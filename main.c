#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 1000
int underAttack,turn,moves,enpassentPerm,enpasentFlag,undoFlag,redoFlag,loadFlag,tempMoves;
int square,notValidMove,fileMoves,numOfUndo;
int WKCastle,WR1Castle,WR2Castle,BKCastle,BR1Castle,BR2Castle;
int castling_x,castling_y,isCastling;
char blackCaptured[]={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
char whiteCaptured[]={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
char EMPTY  = '.',type,tempArray[MAX_SIZE][5];
char* attacked;
char emptyBoard[8][8]={
        
        {'.','-','.','-','.','-','.','-'},
        {'-','.','-','.','-','.','-','.'},
        {'.','-','.','-','.','-','.','-'},
        {'-','.','-','.','-','.','-','.'},
        {'.','-','.','-','.','-','.','-'},
        {'-','.','-','.','-','.','-','.'},
        {'.','-','.','-','.','-','.','-'},
        {'-','.','-','.','-','.','-','.'}
};
char board[8][8]={
        {'R','N','B','Q','K','B','N','R'},
        {'P','P','P','P','P','P','P','P'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'p','p','p','p','p','p','p','p'},
        {'r','n','b','q','k','b','n','r'}};
char tempBoard[8][8]={
        {'R','N','B','Q','K','B','N','R'},
        {'P','P','P','P','P','P','P','P'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'p','p','p','p','p','p','p','p'},
        {'r','n','b','q','k','b','n','r'}};
void printBoardElements(char A[8][8]);
bool isUpper(char x);
bool isLower(char x);
int changeType(char x,char y,int n);
bool isTherePromotionn(char pawn, int toRow);
char promotion(char pawn,int toRow);
bool enPassent(int fromRow, int fromCol, int toRow, int toCol);
bool castling(int fromRow, int fromCol, int toRow, int toCol);
bool validRookMove(int fromRow, int fromCol, int toRow, int toCol);
bool validBishopMove(int fromRow, int fromCol, int toRow, int toCol);
bool validQueenMove(int fromRow, int fromCol, int toRow, int toCol);
bool validKnightMove(int fromRow, int fromCol, int toRow, int toCol);
bool validKingMove(int fromRow, int fromCol, int toRow, int toCol);
bool validCapturePawn(int fromRow, int fromCol, int toRow, int toCol);
bool validPawnMove(int fromRow, int fromCol, int toRow, int toCol);
int fileInput(char c);
void printCapturedPieces(int fromRow, int fromCol, char x);
void move(int fromRow, int fromCol, int toRow, int toCol);
void rookCastle(int fromRow ,int fromCol,int toRow,int toCol);
void kingCastle(int fromRow ,int fromCol,int toRow,int toCol);
void check(char attacker,int toRow, int toCol);
void kingOutOfCheck(char c,int a_row,int a_col);
void pieceAttackTheKing(char attacker);
void uncheckedMove( char attacked );
bool switchValidMove(int fromRow, int fromCol, int toRow, int toCol);
bool switchTurn(char x);
int numberOfMoves();
int numberOfPieces(char piece);
bool sameSquare();
bool Draw();
void reset();
void newGame();
void readMoves();
void load(int movement);
void Undo();
void Redo();
void afterUndo();
void saveMoves(char fromColChar,int fromRow,char toColChar,int toRow);
void save();
int FileExist(const char * filename);
void delay(unsigned meliseconds);

int main(){
    int fromRow,toRow,fromCol,toCol;
    char fromColchar,toColchar,attacker,temp,start;
    printf("------------------------------------------------------------\n");
    printf("Commands: (N)ew game   (U)ndo  R(ed0) (S)ave  (L)oad  (Q)uit\n");
    printf("------------------------------------------------------------\n");
    printBoardElements(board);

    while (true) {
        notValidMove=0;
        if (turn%2==0){
            printf("white turn\n");
            printf("----------\n");
        } else if ((turn%2==1)){
            printf("black turn\n");
            printf("----------\n");
        }
        if (underAttack == 1)
            underAttack+=1;

        numberOfMoves();
        if (moves==0 && underAttack == 2){
            if (turn % 2 != 0)
                printf("white Win \n");
            else if (turn % 2 != 1)
                printf("black Win \n");
            delay(10000);
            break;
        }else if(Draw()){
            printf("The game ends with DRAW\n");
            delay(10000);
            break;
        }
        scanf(" %c",&fromColchar);
        if (fromColchar=='N'||fromColchar=='n'){
            newGame();
            printBoardElements(board);
            continue;
        }else if (fromColchar=='L'||fromColchar=='l'){
            loadFlag=1;
            readMoves();
            tempMoves=fileMoves;
            turn=tempMoves;
            load(0);
            continue;
        }else if (fromColchar=='U'||fromColchar=='u'){
            undoFlag=1;
            if (tempMoves - numOfUndo > 0){
                reset();
                Undo();
                turn--;
                continue;
            }else{
                printf("you can't Undo more\n");
                continue;
            }
        }else if(fromColchar=='R'||fromColchar=='r'){
            redoFlag=1;
            if (tempMoves - numOfUndo < tempMoves){
                reset();
                Redo();
                turn++;
                continue;
            }else{
                printf("You can't Redo more\n");
                continue;
            }
        }else if(fromColchar=='S'||fromColchar=='s'){
            save();
            break;
        }else if (fromColchar=='Q'||fromColchar=='q'){
            printf("GOOD BYE!");
            delay(10000);
            break;
        }
        scanf("%d %c %d",&fromRow,&toColchar,&toRow);
        fflush(stdin);
        if (numOfUndo!=0){
            afterUndo();
            numOfUndo=0;
        }
        if ( (fromRow<1||fromRow>8)||(toRow<1||toRow>8)||(fromColchar<'a'||fromColchar>'h')
             ||(toColchar<'a'||toColchar>'h')){
            printf("not valid Input!\n");
            continue;
        }
        fromCol=fileInput(fromColchar);
        toCol=fileInput(toColchar);
        fromRow=8-fromRow;
        toRow=8-toRow;

        if (isLower(board[fromRow][fromCol])&&(turn%2 == 1)){
            printf("not valid\n");
            continue;
        } else if (isUpper(board[fromRow][fromCol])&&(turn%2==0)){
            printf("not valid\n");
            continue;
        } else if (board[fromRow][fromCol]==EMPTY){
            printf("not valid\n");
            continue;
        }

        if (switchValidMove(fromRow,fromCol,toRow,toCol)) {
            if ((board[fromRow][fromCol]=='p')||(board[fromRow][fromCol]=='P')) {
                board[fromRow][fromCol] = promotion(board[fromRow][fromCol], toRow);
                if (isTherePromotionn(board[fromRow][fromCol], toRow))
                    tempArray[turn][4]=board[fromRow][fromCol];
            }
            temp=board[toRow][toCol];
            move(fromRow, fromCol, toRow, toCol);
            pieceAttackTheKing(attacker);
            uncheckedMove(board[toRow][toCol]);
            if (notValidMove==1){
                printf("%s king under attack \n",attacked);
                printf("you can't do this move your king is under attack\nplay again\n");
            }
            if (underAttack == 1){
                move(toRow,toCol,fromRow,fromCol);
                board[toRow][toCol]=temp;
                if (isCastling){
                    move(fromRow,(toCol-castling_x),toRow,castling_y);
                    isCastling=0;
                }
                continue;
            }

            printCapturedPieces(toRow,toCol,temp);
            attacker=' ';
            printBoardElements(board);
            kingCastle(fromRow,fromCol,toRow,toCol);
            rookCastle(fromRow,fromCol,toRow,toCol);
            check(board[toRow][toCol],toRow,toCol);
            if (underAttack == 1){
                printf("%s king under attack \n",attacked);
                attacker=board[toRow][toCol];
            }
        }else{
            printf("you can't do this move\n");
            continue;
        }
        saveMoves(fromColchar,8-fromRow,toColchar,8-toRow);
        turn++;
        tempMoves++;
        isCastling=0;
    }
}

void printBoardElements(char A[8][8]){
    int i , j ;
    printf("   a b c d e f g h \n");
    printf("   - - - - - - - -  \n");
    for (i=0 ; i<8 ; i++){
        printf("%d| ",8-i);
        for (j=0 ; j<8 ; j++){
            if (A[i][j]==EMPTY){
                printf("%c ",emptyBoard[i][j]);
            } else
                printf("%c ",A[i][j]);
        }
        printf("|%d",8-i);
        printf("\n");
    }
    printf("   - - - - - - - -  \n");
    printf("   a b c d e f g h \n");
}
//function return true if char is capital
bool isUpper(char x){
    if (x>='A'&&x<='Z')
        return true;
    else
        return false;
}
//function return true if char is lowercase
bool isLower(char x){
    if (x>='a'&&x<='z')
        return true;
    else
        return false;
}
//function return true if same type piece in their destination
int changeType(char x,char y,int n){
    if(isLower(x)&&n==0)
        return isUpper(y);
    else if (isLower(x)&&n==1)
        return isLower(y);
    else if (isUpper(x)&&n==0)
        return isLower(y);
    else if (isUpper(x)&&n==1)
        return isUpper(y);
}
bool isTherePromotionn(char pawn, int toRow) {
    if (isLower(pawn) && toRow == 0) {
        return true;
    } else if (isUpper(pawn) && toRow == 7) {
        return true;
    } else
        return false;
}

char promotion(char pawn,int toRow){
    char promoted ;
    char queen,rook,bishop,knight;
    int isPromotinonFlag=0;
    if (toRow==0){
        queen='q';rook='r';bishop='b';knight='n';
        isPromotinonFlag=1;
    } else if(toRow==7){
        queen='Q';rook='R';bishop='B';knight='N';
        isPromotinonFlag=1;
    }
    if(isPromotinonFlag){
        printf("Enter the required promoted piece: ");
        scanf(" %c", &promoted);
        if(promoted == queen )
            return queen;
        else if(promoted == rook)
            return rook;
        else if(promoted == bishop)
            return bishop;
        else if(promoted == knight)
            return knight;
        else{
            printf("Wrong input please try again!\n");
            promotion(pawn, toRow);
        }
    }else
        return pawn;
}

bool enPassent(int fromRow, int fromCol, int toRow, int toCol){
    //white pawn
    if(((board[fromRow][fromCol]=='p')&&(board[toRow][toCol] == EMPTY)&&(fromRow==3)&&(toRow==2)&&board[fromRow][toCol]=='P')||
       (board[fromRow][fromCol]=='P'&&board[toRow][toCol] == EMPTY&&(fromRow==4)&&(toRow==5)&&(board[fromRow][toCol])=='p')){
        if(enpassentPerm != 1)
            board[fromRow][toCol]=EMPTY;
        enpasentFlag=1;
        return true;
    }else {
        enpasentFlag = 0;
        return false;
    }
}

bool castling(int fromRow, int fromCol, int toRow, int toCol){
    int i,j=0,k,r1,r2;
    char king ,rook;
    if (fromRow==7&&(fromCol==4)) {
        king = 'k';
        rook='r';
        k=WKCastle;r1=WR1Castle;r2=WR2Castle;
    }
    else if  (fromRow==0&&fromCol==4){
        king='K';
        rook='R';
        k=BKCastle;r1=BR1Castle;r2=BR2Castle;
    } else
        return false;

    if ((board[fromRow][4]==king)&&(board[fromRow][7]==rook||board[fromRow][0]==rook)
        &&(toRow==fromRow)&&(k==0)&&((toCol==6&&r2==0)||(toCol==2&&r1==0))){
        castling_x=(toCol>4?1:-1);
        castling_y=(toCol>4?7:0);
        for(i=fromCol+castling_x;i!=castling_y;i+=castling_x){
            if (board[fromRow][i]!=EMPTY) {
                j++;
                break;
            }
        }
        if ((j==0)&&(castling_x==1)){
            board[fromRow][5]=rook;
            board[fromRow][7]=EMPTY;
            isCastling=1;
            return true;
        } else if((j==0)&&(castling_x==-1)) {
            board[fromRow][3]=rook;
            board[fromRow][0]=EMPTY;
            isCastling=1;
            return true;
        } else {
            isCastling=0;
            return false;
        }
    }else{
        isCastling=0;
        return false;
    }
    return 0;
}

bool validRookMove(int fromRow, int fromCol, int toRow, int toCol){
    int i,j=0;
    // Attempt to move to the same cell
    if (fromRow == toRow && fromCol == toCol)
        return false;

    if (fromRow == toRow) { // Horizontal move
        int x = (fromCol < toCol) ? 1 : -1;
        for (i = fromCol + x; i != toCol; i += x)
            if (board[fromRow][i]!=EMPTY)
                j++;
        if ((changeType(board[fromRow][fromCol],board[fromRow][i],1))|| j!=0)
            return false;
    }else if (fromCol == toCol) { // Vertical move
        int y = (fromRow < toRow) ? 1 : -1;
        for (i = fromRow + y; i != toRow; i += y)
            if (board[i][fromCol]!=EMPTY)
                j++;
        if ((changeType(board[fromRow][fromCol],board[i][fromCol],1)) ||j!=0)
            return false;
    } else // Not valid rook move
        return false;

    // Return true if destination cell is free
    return ((board[toRow][toCol] == EMPTY)||changeType(board[fromRow][fromCol],board[toRow][toCol],0));
}

bool validBishopMove(int fromRow, int fromCol, int toRow, int toCol){
    int i,j,k=0,diagonal1,diagonal2,temp;

    // Attempt to move to the same cell
    if (fromRow == toRow && fromCol == toCol)
        return false;

    diagonal1= (fromRow > toRow) ? -1 : 1;
    diagonal2= (fromCol > toCol) ? -1 : 1;
    if (((fromCol+fromRow)==(toCol+toRow)) || ((fromCol-fromRow)==(toCol-toRow))){
        temp=diagonal2;
        for (i = fromRow + diagonal1; i != toRow; i += diagonal1) {
            j = fromCol + diagonal2;
            if (board[i][j]!=EMPTY)
                k++;
            diagonal2+=temp;
        }
        if (((board[i][toCol] != EMPTY) && (changeType(board[fromRow][fromCol],board[i][toCol],1))) || k != 0)
            return false;

    } else
        return false;
    return ((board[toRow][toCol] == EMPTY)||(changeType(board[fromRow][fromCol],board[toRow][toCol],0)));
}
bool validQueenMove(int fromRow, int fromCol, int toRow, int toCol){
    if (validBishopMove(fromRow,fromCol,toRow,toCol)||validRookMove(fromRow,fromCol,toRow,toCol))
        return true;
    else
        return false;
}

bool validKnightMove(int fromRow, int fromCol, int toRow, int toCol){
    // Attempt to move to the same cell
    if (fromRow == toRow && fromCol == toCol)
        return false;

    if (fromRow == toRow-1 || fromRow == toRow+1 ){ //Horizontal then vertical
        if(fromCol == toCol-2 || fromCol == toCol+2)
            return ((board[toRow][toCol] == EMPTY)||(changeType(board[fromRow][fromCol],board[toRow][toCol],0)));
        else
            return false;
    }else if(fromRow == toRow-2 || fromRow == toRow+2 ){//Vertical then horizontal
        if(fromCol == toCol-1 || fromCol == toCol+1)
            return ((board[toRow][toCol] == EMPTY)||(changeType(board[fromRow][fromCol],board[toRow][toCol],0)));
        else
            return false;
    }else
        return false;
}

bool validKingMove(int fromRow, int fromCol, int toRow, int toCol){
    // Attempt to move to the same cell
    if (fromRow == toRow && fromCol == toCol)
        return false;
    if ((((fromRow +1== toRow)&&(fromCol==toCol))||((fromRow-1 == toRow)&&(fromCol==toCol))||
         ((fromCol+1 == toCol)&&(fromRow==toRow))||((fromCol-1 == toCol)&&(fromRow==toRow)))||
        ( ((fromRow+1==toRow )&& (fromCol+1==toCol) ) || ((fromRow-1==toRow)&&(fromCol-1==toCol))||
          ((fromRow+1==toRow)&&(fromCol-1==toCol))||((fromRow-1==toRow)&&(fromCol+1==toCol))))
        return ((board[toRow][toCol] == EMPTY) || (changeType(board[fromRow][fromCol], board[toRow][toCol], 0)));
    else if((underAttack!=2)&&castling(fromRow, fromCol, toRow, toCol))
        return true;
    else
        return false;
}
bool validCapturePawn(int fromRow, int fromCol, int toRow, int toCol){
    if(((fromRow -1==toRow)&&(fromCol+1==toCol||fromCol-1==toCol))&&
       (isUpper(board[toRow][toCol]))&&(isLower(board[fromRow][fromCol])))
        return true;
    else if(((fromRow +1==toRow)&&(fromCol+1==toCol||fromCol-1==toCol))&&
            (isLower(board[toRow][toCol]))&&isUpper(board[fromRow][fromCol]))
        return true;
    else
        return false ;
}
bool validPawnMove(int fromRow, int fromCol, int toRow, int toCol){
    int x,y;
    x=isLower(board[fromRow][fromCol])?-1:1;
    y=isLower(board[fromRow][fromCol])?6:1;
    // Attempt to move to the same cell
    if (fromRow == toRow && fromCol == toCol)
        return false;

    if (fromCol == toCol) { // Vertical move
        if(toRow == fromRow+x)
            return (board[toRow][toCol] == EMPTY);
        else if(fromRow == y&&(toRow == fromRow+2*x && board[fromRow+x][toCol]==EMPTY))
            return (board[toRow][toCol] == EMPTY);
        else
            return false;
    }else if(validCapturePawn(fromRow,fromCol,toRow,toCol))// diagonal pawn attack
        return true;
    else if(enPassent(fromRow,fromCol,toRow,toCol))
        return true;
    else
        return false ;
}

int fileInput(char c){
    if (c=='a'||c=='A')
        return 0;
    else if(c=='b'||c=='B')
        return 1;
    else if(c=='c'||c=='C')
        return 2;
    else if(c=='d'||c=='D')
        return 3;
    else if(c=='e'||c=='E')
        return 4;
    else if(c=='f'||c=='F')
        return 5;
    else if(c=='g'||c=='G')
        return 6;
    else if(c=='h'||c=='H')
        return 7;
}

void printCapturedPieces(int fromRow, int fromCol, char x){
    //white piece capture black piece
    if (isLower(board[fromRow][fromCol])&&(isUpper(x) || enpasentFlag == 1)){
        if(enpasentFlag == 1)
            x='P';
        int i=0;
        while (blackCaptured[i]!=EMPTY){
            i++;
        }
        blackCaptured[i]=x;

        //black piece capture white piece
    }else if(isUpper(board[fromRow][fromCol])&&(isLower(x) || enpasentFlag == 1)){
        if(enpasentFlag == 1)
            x='p';
        int i=0;
        while (whiteCaptured[i]!=EMPTY){
            i++;
        }
        whiteCaptured[i]=x;
    }
    int i=0;
    if (loadFlag == 0 && undoFlag==0 && redoFlag==0) {
        printf("-------------------------------------\n");
        printf("Black captured pieces: ");
        for (i = 0; blackCaptured[i] != EMPTY; i++)
            printf("%c ", blackCaptured[i]);
        printf("\nWhite captured pieces: ");
        for (i = 0; whiteCaptured[i] != EMPTY; i++)
            printf("%c ", whiteCaptured[i]);
        printf("\n-------------------------------------\n");
    }
}

void move(int fromRow, int fromCol, int toRow, int toCol){
    board[toRow][toCol]=board[fromRow][fromCol];
    board[fromRow][fromCol]=EMPTY;
}
void rookCastle(int fromRow ,int fromCol,int toRow,int toCol){
    if (board[toRow][toCol]=='R'||board[toRow][toCol]=='r'){
        if(fromRow==7&&fromCol==0)
            WR1Castle++;
        else if(fromRow==7&&fromCol==7)
            WR2Castle++;
        else if(fromRow==0&&fromCol==0)
            BR1Castle++;
        else if(fromRow==0&&fromCol==7)
            BR2Castle++;
    }
}
void kingCastle(int fromRow ,int fromCol,int toRow,int toCol){
    if ((board[toRow][toCol]=='k')||board[toRow][toCol]=='K'){
        if(fromRow==7&&fromCol==4)
            WKCastle++;
        else if(fromRow==0&&fromCol==4)
            BKCastle++;
    }
}

//Knowing if the king is in check
void check(char attacker,int toRow, int toCol){
    int i,j;
    char king,pawn,queen,rook,bishop,knight,attackerKing;
    if(isLower(board[toRow][toCol])){ //black king is in check
        king='K';pawn='p'; queen='q';rook='r';bishop='b';knight='n';attackerKing='k';
        attacked="Black";
    }else if(isUpper(board[toRow][toCol])){ //white king is in check
        king='k';pawn='P'; queen='Q';rook='R';bishop='B';knight='N';attackerKing='K';
        attacked="White";
    }
    for(i=0;i<8;i++){
        for (j=0;j<8;j++){
            if ((board[i][j]==king)&&switchValidMove(toRow,toCol,i,j))
                underAttack=1;
        }
    }
}

void kingOutOfCheck(char c,int a_row,int a_col){
    if (underAttack == 2){
        check(c,a_row,a_col);
        if (underAttack == 1) {
            notValidMove=1;
            return;
        }else if (square == 64)
            underAttack = 0;
    }
}

void pieceAttackTheKing(char attacker){
    int i,j;
    square=0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; ++j) {
            square++;
            if(changeType(attacker,board[i][j],1) || square == 64)
                kingOutOfCheck(board[i][j], i, j);
        }
}
//check if the move Does not subject the king to attack
void uncheckedMove( char attacked ){
    underAttack=2;
    if (isLower(attacked))
        pieceAttackTheKing('A');
    else if (isUpper(attacked))
        pieceAttackTheKing('a');
}
//check if the move is valid
bool switchValidMove(int fromRow, int fromCol, int toRow, int toCol){
    if ((board[fromRow][fromCol]=='n')||(board[fromRow][fromCol]=='N'))
        return (validKnightMove(fromRow,fromCol,toRow,toCol));
    else if ((board[fromRow][fromCol]=='r')||(board[fromRow][fromCol]=='R'))
        return (validRookMove(fromRow,fromCol,toRow,toCol));
    else if ((board[fromRow][fromCol]=='b')||(board[fromRow][fromCol]=='B'))
        return(validBishopMove(fromRow, fromCol, toRow, toCol)) ;
    else if ((board[fromRow][fromCol]=='q')||(board[fromRow][fromCol]=='Q'))
        return (validQueenMove(fromRow, fromCol, toRow, toCol));
    else if ((board[fromRow][fromCol]=='k')||(board[fromRow][fromCol]=='K'))
        return ((validKingMove(fromRow, fromCol, toRow, toCol)) );
    else if ((board[fromRow][fromCol]=='p')||(board[fromRow][fromCol]=='P'))
        return  (validPawnMove(fromRow, fromCol, toRow, toCol));
    else
        return false;
}
//check if the player moves his pieces
bool switchTurn(char x){
    if (turn%2==0){
        type='A';
        return isLower(x);
    }else{
        type='a';
        return isUpper(x);
    }
}
//count number of valid moves in current turn
int numberOfMoves(){
    int temps[]={underAttack, notValidMove, isCastling, square};
    int i,j,k,l;
    char temp;
    moves=0, enpassentPerm=1;
    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            if (switchTurn(board[i][j])){
                for (k = 0; k < 8; ++k) {
                    for (l = 0; l < 8; ++l) {
                        if (switchValidMove(i,j,k,l)){
                            if (underAttack == 1)
                                underAttack+=1;
                            temp=board[k][l];
                            move(i, j, k, l);
                            if (isCastling){
                                move(i,(l-castling_x),k,castling_y);
                                isCastling=0;
                            }
                            pieceAttackTheKing(type);
                            uncheckedMove(board[k][l]);
                            move(k,l,i,j);
                            board[k][l]=temp;
                            if (underAttack != 1){
                                moves++;
                            }
                        }
                    }
                }
            }
        }
    }
    enpassentPerm=0, underAttack=temps[0];
    notValidMove=temps[1], isCastling=temps[2], square=temps[3];
    return moves;
}
//count how many piece of same kind on the board
int numberOfPieces(char piece){
    int count=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]==piece)
                count++;
        }
    }
    return count;
}
//check if the oppenent's bishops on the same type of square (black or white)
bool sameSquare(){
    int i,j,k=0,l=0;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (board[i][j]== 'b')
                k=(i+j)%2;
            else if (board[i][j]=='B')
                l=(i+j)%2;
        }
    }
    if (k==l)
        return true;
}

bool Draw(){
    int n=0,n1=0,n2=0,n3=0,n4=0,n5=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((board[i][j] != EMPTY ) && (board[i][j] != 'k')&&(board[i][j]!='K'))
                n++;
            if((board[i][j]!=EMPTY)&&(board[i][j]!='k')&&(board[i][j]!='b')&&
               (board[i][j]!='K')||(numberOfPieces('b') == 2))
                n1++;
            if ((board[i][j]!=EMPTY)&&(board[i][j]!='k')&&(board[i][j]!='n')&&
                (board[i][j]!='K')||(numberOfPieces('n') == 2))
                n2++;
            if (((board[i][j] != EMPTY) && (board[i][j] != 'k') && (board[i][j] != 'K') && (board[i][j] != 'b')&&(board[i][j] != 'B'))||
                (!sameSquare() || numberOfPieces('b' == 2) || numberOfPieces('B') == 2))
                n3++;
            if ((board[i][j]!=EMPTY)&&(board[i][j]!='k')&&(board[i][j]!='B')&&(board[i][j]!='K')||(numberOfPieces('B') == 2))
                n4++;
            if ((board[i][j]!=EMPTY)&&(board[i][j]!='k')&&(board[i][j]!='N')&&(board[i][j]!='K')||(numberOfPieces('N') == 2))
                n5++;
        }
    }
    if (n==0)
        return true;
    else if (n1==0)
        return true;
    else if (n2==0)
        return true;
    else if (n3==0)
        return true;
    else if (n4==0)
        return true;
    else if (n5==0)
        return true;
    else if((moves==0)&&(underAttack != 2))
        return true;
    else
        return false;
}

void reset(){
    int i,j;
    for ( j = 0; j < 16; ++j) {
        blackCaptured[j]='.';
        whiteCaptured[j]='.';
    }
    for ( i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            board[i][j]=tempBoard[i][j];
        }
    }
}

void newGame() {
    //clear the temp array
    for (int i = 0; i < turn; ++i) {
        for (int j = 0; j < 5; ++j) {
            tempArray[i][j]='\0';
        }
    }
    underAttack = 0, turn = 0,tempMoves= 0,enpassentPerm = 0, square = 0, notValidMove = 0;
    WKCastle = 0, WR1Castle = 0, WR2Castle = 0, BKCastle = 0, BR1Castle = 0, BR2Castle = 0;
    castling_x = 0, castling_y = 0, isCastling = 0, numOfUndo=0;
    reset();
}

//read the moves saved in the file
void saveMoves(char fromColChar,int fromRow,char toColChar,int toRow){
    tempArray[turn][0]=fromColChar;
    tempArray[turn][1]=fromRow + '0';
    tempArray[turn][2]=toColChar;
    tempArray[turn][3]=toRow + '0';
}

void readMoves(){
    char *token;
    char help[MAX_SIZE];
    FILE *InputFile = NULL;
    char fileName[MAX_SIZE];
    printf("Enter name of the file: ");
    scanf(" %s", fileName);
    strcat(fileName,".txt");
    if(!(FileExist(fileName)))
        printf("The file dosen't exist!\n");
    else
        InputFile =fopen(fileName,"r");
    fscanf(InputFile,"%s",help);
    token=strtok(help,",");
    int i=0;
    while(token!=NULL){
        for (int j = 0; j <5 ; ++j) {
            if (j==4&&token[4]!='\0')
                tempArray[i][4]=token[4];
            else if (j!=4)
                tempArray[i][j]=token[j];
        }
        token=strtok(NULL,",");
        i++;
    }
    fileMoves=i;
}

void load(int movement){
    WKCastle = 0, WR1Castle = 0, WR2Castle = 0;
    BKCastle = 0, BR1Castle = 0, BR2Castle = 0;
    char fromColChar,toColChar;
    int fromRow,toRow,fromCol,toCol;
    for (int i = 0; i < tempMoves - movement; ++i) {
        fromColChar=tempArray[i][0];
        fromRow=tempArray[i][1] - '0';
        toColChar=tempArray[i][2];
        toRow=tempArray[i][3] - '0';
        fromCol=fileInput(fromColChar);
        toCol=fileInput(toColChar);
        fromRow=8-fromRow;
        toRow=8-toRow;

        if ((board[fromRow][fromCol]=='p')||(board[fromRow][fromCol]=='P')) {
            enPassent(fromRow, fromCol, toRow, toCol);
            if (isTherePromotionn(board[fromRow][fromCol], toRow))
                board[fromRow][fromCol]=tempArray[i][4];
        }
        if (castling(fromRow,fromCol,toRow,toCol));
        printCapturedPieces(fromRow,fromCol,board[toRow][toCol]);//save the captured pieces
        move(fromRow,fromCol,toRow,toCol);
    }
    if(tempMoves == movement)
        reset();
    else{
        loadFlag=0;undoFlag=0;redoFlag=0;
        printCapturedPieces(fromRow,fromCol,board[toRow][toCol]);
    }
    printBoardElements(board);
}

void Undo(){
    numOfUndo++;
    load(numOfUndo);
}

void Redo(){
    numOfUndo--;
    load(numOfUndo);
}

void afterUndo(){
    for (int j = turn; j<=turn+numOfUndo; ++j) {
        for (int i = 0; i < 5; ++i) {
            tempArray[j][i] = '\0';
        }
    }
    tempMoves=turn;
}

void save(){
    char fileName[MAX_SIZE];
    FILE *fp;
    printf("Enter name of the file: ");
    scanf("%s",fileName);
    strcat(fileName,".txt");
    fp = fopen(fileName, "w");
    for (int i = 0; i < turn; ++i) {
        for (int k = 0; k < 5; ++k) {
            if (k==4&& tempArray[i][4] != '\0')
                fprintf(fp,"%c",tempArray[i][4]);
            else if (k!=4)
                fprintf(fp, "%c", tempArray[i][k]);
        }
        fprintf(fp,",");
    }
    fclose(fp);
}
//Check if a file exist return 1 otherwise return 0
int FileExist(const char * filename) {
    FILE *file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}
void delay(unsigned meliseconds){
    for (int c = 1; c <= 32767; c++)
        for (int d = 1; d <= 32767; d++)
            {}
}
