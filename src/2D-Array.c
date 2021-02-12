#include<stdio.h>
#include<stdlib.h>

void displayBoard(char**, int);
void choiceToCoordinates(int*, int*, int);

char** createBoard(int boardSize){ 
    // Returns n*n dynamically alloted array.
    // This 2D array will be storing the state of the board.

    // Create an array of character pointers, each pointer will represent a row.
    char **board = (char**)malloc(sizeof(char**)*boardSize); 
    
    // Assign a row to each pointer in array.
    for(int i=0; i<boardSize; i++)
        board[i] = (char*)malloc(sizeof(char)*boardSize);

    // Return the freshly baked board.
    return board;
} 

void labelBoard(char** board, int boardSize){
    char currLabel = '0';

    for(int i=0; i<boardSize; i++)
        for(int j=0; j<boardSize; j++)
            board[i][j] = currLabel++;
}

void displayBoard(char** board, int boardSize){
    system("clear"); printf("\n\n");

    int unitSize;
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(j<boardSize-1)
                unitSize = printf(" %c |", board[i][j]);
            else
                unitSize = printf(" %c ", board[i][j]);
        }
        printf("\n");

        if(i < boardSize-1)
            for(int k=0; k<=unitSize*boardSize; k++)
                printf("-");
            
        printf("\n");
    }
    printf("\n");
}

char** fetchPlayerIds(){
    char** playerNames = (char**)malloc(sizeof(char**)*2);

    for(int i=0; i<2; i++){
        playerNames[i] = (char*)malloc(sizeof(char)*30);
        printf("Player %d > ", (i+1));
        scanf("\n");
        scanf("%[^\n]%*c", playerNames[i]);
    }

    return playerNames;
}

void choiceToCoordinates(int *x, int *y, int boardSize){
       scanf("\n");
       int choice; scanf("%d", &choice);

       *x = choice / boardSize;
       *y = choice % boardSize;
}

int checkWinCondition(char** board, int boardSize, int playerTurn){
    for(int i=0; i<boardSize; i++){
        char rowVal = board[i][0]; int rowCount;
        char colVal = board[0][i]; int colCount;
        for(int j=0; j<boardSize; j++){
            if(board[i][j] == rowVal)
                rowCount++;
            if(board[j][i] == colVal)
                colCount++;
        }
        if(rowCount==3 || colCount==3)
            return playerTurn;
    }
}

void runGame(char** board, int boardSize, char** playerIds){
    char weapon[] = {'X', 'O'};
    int playerTurn = 0, rounds = 0;
     
    while(1){
        playerTurn = (playerTurn) ?0 :1;
        /*
        It's called TERNARY OPERATOR (Signified by ?,: operators.), same as writing ... 

        if(playerTurn==1)
            playerTurn = 0;
        else
            playerTurn = 1;
        */

       displayBoard(board, boardSize); //Display current state.
       printf("%s, your turn > \n", playerIds[playerTurn]);
       
       if(rounds >= 9){
           printf("Draw, nice.\n");
           exit(0);
       }
       // Fetch user's move. Keep asking till a valid input is achieved.
       int X,Y;
       choiceToCoordinates(&X, &Y, boardSize);

       while(board[X][Y]=='X' || board[X][Y]=='O'){ //Check for range too.
           printf("It's occupied blindy. Go again, new choice? \n");
           choiceToCoordinates(&X, &Y, boardSize);
       } 
       board[X][Y] = weapon[playerTurn];
       
       // Check if someone has won already, continuing further won't make any sense now.
       int winner = checkWinCondition(board, boardSize, playerTurn);
       if(winner != -1){
           printf("%s wins, bow down yall. <3\n", playerIds[winner]);
           exit(0);
       }
       
       rounds++;
    }
}



int main(void){

    int boardSize = 3;
    printf("Creating board...\n\n");/**/
    char** board = createBoard(boardSize);
    labelBoard(board, boardSize);

    char** playerIds = fetchPlayerIds();
    runGame(board, boardSize, playerIds);
    free(board);


    return 0;
}