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
    char currLabel = 'a';

    for(int i=0; i<boardSize; i++)
        for(int j=0; j<boardSize; j++)
            board[i][j] = currLabel++;
}

void displayBoard(char** board, int boardSize){
    int unitSize;
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++)
            unitSize = printf("| %c |", board[i][j]);
        printf("\n");
        for(int k=0; k<=unitSize*boardSize; k++)
            printf("-");
        printf("\n");
    }
}

int main(void){

    int boardSize = 4;
    printf("Creating board.\n");/**/
    char** board = createBoard(boardSize);

    labelBoard(board, boardSize);
    displayBoard(board, boardSize);
    free(board);
    return 0;
}