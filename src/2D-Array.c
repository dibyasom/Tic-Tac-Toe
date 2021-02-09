#include<stdio.h>
#include<stdlib.h>

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
    char currLabel = 'A';

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



int main(void){

    int boardSize = 3;
    printf("Creating board...\n\n");/**/
    char** board = createBoard(boardSize);
    labelBoard(board, boardSize);
    displayBoard(board, boardSize);

    char** playerIds = fetchPlayerIds();
    // runGame(board, boardSize);
    free(board);


    return 0;
}