// Authored by Dibyasom Puhan. I lub doggos.

#include <bits/stdc++.h>

using namespace std;

void displayBoard(char **, int);
void choiceToCoordinates(int *, int *, int);
int checkWinCondition(char **, int, int);

char **createBoard(int boardSize)
{
    // Returns n*n dynamically alloted array.
    // This 2D array will be storing the state of the board.

    // Create an array of character pointers, each pointer will represent a row.
    char **board = new char *[boardSize];

    // Assign a row to each pointer in array.
    for (int i = 0; i < boardSize; i++)
        board[i] = new char[boardSize];

    // Return the freshly baked board.
    return board;
}

void labelBoard(char **board, int boardSize)
{
    char currLabel = '0';

    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            board[i][j] = currLabel++;
}

void displayBoard(char **board, int boardSize)
{
    system("clear");
    printf("\n\n");

    int unitSize;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (j < boardSize - 1)
                unitSize = printf(" %c |", board[i][j]);
            else
                unitSize = printf(" %c ", board[i][j]);
        }
        printf("\n");

        if (i < boardSize - 1)
            for (int k = 0; k <= unitSize * boardSize; k++)
                printf("-");

        printf("\n");
    }
    printf("\n");
}

char **fetchPlayerIds()
{
    char **playerNames = new char *[2];

    for (int i = 0; i < 2; i++)
    {
        playerNames[i] = new char[30];
        cout << "Player " << (i + 1) << " > ";
        cin >> playerNames[i];
    }

    return playerNames;
}

void choiceToCoordinates(int *x, int *y, int boardSize)
{
    scanf("\n");
    int choice;
    scanf("%d", &choice);

    *x = choice / boardSize;
    *y = choice % boardSize;
}

// Called after every valid entry, checks the win condition.
int checkWinCondition(char **board, int boardSize, int playerTurn)
{
    for (int i = 0; i < boardSize; i++)
    {
        char rowVal = board[i][0];
        int rowMatch = 0;
        char colVal = board[0][i];
        int colMatch = 0;
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == rowVal)
                rowMatch++;
            if (board[j][i] == colVal)
                colMatch++;
        }
        if (rowMatch == boardSize || colMatch == boardSize)
            return playerTurn;
    }
    char leftD = board[0][0];
    int leftDcount = 1;
    char rightD = board[boardSize - 1][boardSize - 1];
    int rightDcount = 1;
    for (int i = 1; i < boardSize; i++)
    {
        if (board[i][i] == leftD)
            leftDcount++;
        if (board[boardSize - 1 - i][i] == rightD)
            rightDcount++;
    }
    if (leftDcount == boardSize || rightDcount == boardSize)
        return playerTurn;
    return -1;
}

void runGame(char **board, int boardSize, char **playerIds)
{
    char weapon[] = {'X', 'O'};
    int playerTurn = 0, rounds = 0;

    displayBoard(board, boardSize); //Display current state.

    while (rounds < 9)
    {
        playerTurn = (playerTurn + 1) % 2;

        int X, Y;
        printf("%s, your turn > \n", playerIds[playerTurn]);
        choiceToCoordinates(&X, &Y, boardSize);
        //    Keep asking till a valid input is achieved.
        while (board[X][Y] == 'X' || board[X][Y] == 'O')
        { //Check for range too.
            printf("It's occupied blindy. Go again, new choice? \n");
            choiceToCoordinates(&X, &Y, boardSize);
        }
        board[X][Y] = weapon[playerTurn]; // Update board.
        displayBoard(board, boardSize);   //Display current state.

        // Check if someone has won already, continuing further won't make any sense now.
        int winner = checkWinCondition(board, boardSize, playerTurn);
        if (winner != -1)
        {
            printf("%s wins, bow down yall. <3\n", playerIds[winner]);
            exit(0);
        }

        rounds++;
    }
}

int main(void)
{

    printf("\n\n\tWelcome to GTA-VI\t<Fake Rockstar Logo <3\n\n");
    int boardSize;
    printf("Boardsize: ");
    scanf("%d", &boardSize);
    printf("Creating board...\n\n"); /**/
    char **board = createBoard(boardSize);
    labelBoard(board, boardSize);

    char **playerIds = fetchPlayerIds();
    runGame(board, boardSize, playerIds);
    free(board); // Clear all reserved memory and avoid possible memory leaks.

    return 0;
}