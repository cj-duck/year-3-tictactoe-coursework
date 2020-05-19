// Data Structures and Algorithms Tic-Tac-Toe Coursework
// Author: Christopher Johnson
// Matric #: 40275286
// Date of Last Modification: 26/03/19

// Including relevant libraries
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Decaring variables
char board[10] = {'-', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
void drawMenu();
void drawUI();
void game();
void gameComp();
void victoryScreen();
void resetBoard();
void init_stack(struct stack *);
void push_stack(struct stack *, int item);
int *pop_stack(struct stack *);

// Declaring stack that will be used to keep track of players' turns
struct stack
{
    int array[9];
    int top;
};

int main()
{
    // Draw Menu
    drawMenu();
}

// Drawing the main menu
void drawMenu()
{
    system("cls");
    printf("\n\n\tTic-Tac-Toe\n\n");
    printf(" Make selection using keyboard:\n\n");
    printf("  1 - Play Game\n");
    printf("  2 - Play against computer\n");
    printf("  3 - Quit\n\n");

    // Get user's menu choice
    char choice;
    choice = getch();
    switch (choice)
    {
    case '1':
        game();
        break;
    case '2':
        gameComp();
        break;
    case '3':
        printf("Exiting..\n");
        exit(0);
    default:
        printf("Invalid selection, please try again!\n");
        drawMenu();
    }
}

// Playing a game agaisnt another player
void game()
{
    int player = 1;
    int win = -1;
    int choice;
    char side;
    struct stack moves;
    int *lastmove = NULL;
    char lastsquare;

    init_stack(&moves);

    drawUI();

    while (win == -1)
    {
        if (player % 2 == 1)
        {
            player = 1;
            side = 'X';
        }
        else
        {
            player = 2;
            side = 'O';
        }

        printf("Player %d make a turn:\n", player);
        choice = getch();

        if (choice == 'q') // Exit to main menu
        {
            resetBoard();
            drawMenu();
        }
        if (choice == 'u') // Undo a move
        {
            lastmove = pop_stack(&moves);
            if (lastmove)
            {
                lastsquare = '0' + *lastmove;
                board[*lastmove] = lastsquare;
                drawUI();
            }
            else
            {
                printf("No more moves to undo\n");
                player--;
            }
        }
        else if (choice == '1' && board[1] == '1')
        {
            board[1] = side;
            push_stack(&moves, 1);
            drawUI();
        }
        else if (choice == '2' && board[2] == '2')
        {
            board[2] = side;
            push_stack(&moves, 2);
            drawUI();
        }
        else if (choice == '3' && board[3] == '3')
        {
            board[3] = side;
            push_stack(&moves, 3);
            drawUI();
        }
        else if (choice == '4' && board[4] == '4')
        {
            board[4] = side;
            push_stack(&moves, 4);
            drawUI();
        }
        else if (choice == '5' && board[5] == '5')
        {
            board[5] = side;
            push_stack(&moves, 5);
            drawUI();
        }
        else if (choice == '6' && board[6] == '6')
        {
            board[6] = side;
            push_stack(&moves, 6);
            drawUI();
        }
        else if (choice == '7' && board[7] == '7')
        {
            board[7] = side;
            push_stack(&moves, 7);
            drawUI();
        }
        else if (choice == '8' && board[8] == '8')
        {
            board[8] = side;
            push_stack(&moves, 8);
            drawUI();
        }
        else if (choice == '9' && board[9] == '9')
        {
            board[9] = side;
            push_stack(&moves, 9);
            drawUI();
        }
        else
        {
            printf("Invalid move ");
            player--;
        }
        win = checkForWin();

        player++;
    }

    drawUI();

    if (win == 1)
    {
        if (player == 2)
            player = 1;
        else
            player = 2;
        victoryScreen(player);
    }
    else if (win == 0)
        victoryScreen(0);
}

// Play a game agaisnt computer
void gameComp()
{
    int win = -1;
    int choice;
    int i;
    int movefound = 0;
    int player;
    int difficulty;
    int random;

    system("cls");
    printf("\n\n\tChoose your difficulty:\n\n");
    printf("    1 - Easy\n");
    printf("    2 - Hard\n\n");
    printf("    Hit any other key to return to the menu\n\n");

    difficulty = getch();
    if (difficulty == '1' || '2')
    {
        printf("Difficulty Selected\n");
    }
    else
    {
        drawMenu();
    }
    

    while (win == -1)
    {
        drawUI();

        printf("Enter number:\n");
        PLAYER:choice = getch();
        if (choice == 'q')
        {
            resetBoard();
            drawMenu();
        }
        else if (choice == '1' && board[1] == '1')
            board[1] = 'X';

        else if (choice == '2' && board[2] == '2')
            board[2] = 'X';

        else if (choice == '3' && board[3] == '3')
            board[3] = 'X';

        else if (choice == '4' && board[4] == '4')
            board[4] = 'X';

        else if (choice == '5' && board[5] == '5')
            board[5] = 'X';

        else if (choice == '6' && board[6] == '6')
            board[6] = 'X';

        else if (choice == '7' && board[7] == '7')
            board[7] = 'X';

        else if (choice == '8' && board[8] == '8')
            board[8] = 'X';

        else if (choice == '9' && board[9] == '9')
            board[9] = 'X';
        else
        {
            printf("Invalid move ");
            // goto was a quick fix before submission after discovering a break. Not usually good practice but worked in this case.
            goto PLAYER;
        }

        player = 1;
        win = checkForWin();

        if (win == -1)
        {
            player = 3;
            // If the user picks easy the program will pick a random available square
            if (difficulty == '1')
            {
                movefound = 0;
                for (i = 1; i < 10; i++)
                {
                    if ((movefound == 0) && (board[i] != 'O') && (board[i] != 'X'))
                    {
                        board[i] = 'O';
                        movefound = 1;
                    }
                }
            }
            // If the user picks hard the program will look for any cases were there are 2 out of 3 matching squares and add a 3rd either blocking the oponent from winning or winning itself
            else if (difficulty == '2')
            {
                movefound = 0;
                if (((board[2] == board[3]) || (board[4] == board[7]) || (board[5] == board[9])) && ((board[1] != 'O') && (board[1] != 'X')))
                {
                    board[1] = 'O';
                }
                else if (((board[3] == board[1]) || (board[5] == board[8])) && ((board[2] != 'O') && (board[2] != 'X')))
                {
                    board[2] = 'O';
                }
                else if (((board[1] == board[2]) || (board[6] == board[9]) || (board[7] == board[5])) && ((board[3] != 'O') && (board[3] != 'X')))
                {
                    board[3] = 'O';
                }
                else if (((board[1] == board[7]) || (board[5] == board[6])) && ((board[4] != 'O') && (board[4] != 'X')))
                {
                    board[4] = 'O';
                }
                else if (((board[1] == board[9]) || (board[7] == board[3]) || (board[2] == board[8]) || (board[4] == board[6])) && ((board[5] != 'O') && (board[5] != 'X')))
                {
                    board[5] = 'O';
                }
                else if (((board[3] == board[9]) || (board[4] == board[5])) && ((board[6] != 'O') && (board[6] != 'X')))
                {
                    board[6] = 'O';
                }
                else if (((board[1] == board[4]) || (board[8] == board[9]) || (board[5] == board[3])) && ((board[7] != 'O') && (board[7] != 'X')))
                {
                    board[7] = 'O';
                }
                else if (((board[7] == board[9]) || (board[2] == board[5])) && ((board[8] != 'O') && (board[8] != 'X')))
                {
                    board[8] = 'O';
                }
                else if (((board[7] == board[8]) || (board[3] == board[6]) || (board[1] == board[5])) && ((board[9] != 'O') && (board[9] != 'X')))
                {
                    board[9] = 'O';
                }
                else
                {
                    movefound = 0;
                    for (i = 1; i < 10; i++)
                    {
                        if ((movefound == 0) && (board[i] != 'O') && (board[i] != 'X'))
                        {
                            board[i] = 'O';
                            movefound = 1;
                        }
                    }
                }
            }
        }
        win = checkForWin();
    }

    drawUI();

    if (win == 1)
        if (player == 1)
            victoryScreen(1);
        else if (player == 3)
            victoryScreen(3);
        else if (win == 0)
            victoryScreen(0);
}

// Checks for each possible way to win
int checkForWin()
{
    if (board[1] == board[2] && board[2] == board[3])
        return 1;

    else if (board[4] == board[5] && board[5] == board[6])
        return 1;

    else if (board[7] == board[8] && board[8] == board[9])
        return 1;

    else if (board[1] == board[4] && board[4] == board[7])
        return 1;

    else if (board[2] == board[5] && board[5] == board[8])
        return 1;

    else if (board[3] == board[6] && board[6] == board[9])
        return 1;

    else if (board[1] == board[5] && board[5] == board[9])
        return 1;

    else if (board[3] == board[5] && board[5] == board[7])
        return 1;

    else if (board[1] != '1' && board[2] != '2' && board[3] != '3' && board[4] != '4' && board[5] != '5' && board[6] != '6' && board[7] != '7' && board[8] != '8' && board[9] != '9')
        return 0;
    else
        return -1;
}

// Drawing the game board
void drawUI()
{
    int halftab = 2;
    system("cls");
    printf("\n###############################################\n");
    printf("# 1-9 to take a turn | q to quit to main menu #\n");
    printf("# u to undo a move   |                        #\n");
    printf("###############################################\n");
    printf("\n\n\t Tic-Tac-Toe - Play Game\n\n");
    printf("       Player 1 (X)  -  Player 2 (O)\n\n\n");
    printf("\t          |     |     \n");
    printf("\t       %c  |  %c  |  %c \n", board[7], board[8], board[9]);
    printf("\t     _____|_____|_____\n");
    printf("\t          |     |     \n");
    printf("\t       %c  |  %c  |  %c \n", board[4], board[5], board[6]);
    printf("\t     _____|_____|_____\n");
    printf("\t          |     |     \n");
    printf("\t       %c  |  %c  |  %c \n", board[1], board[2], board[3]);
    printf("\t          |     |     \n\n\n");
}

// Displays end of game information
void victoryScreen(int player)
{
    printf("\t\t  WINNER!");
    if (player == 1 || player == 2)
        printf("\n\t       Player %d wins!", player);
    else if (player == 3)
        printf("\n\t       Computer Wins!");
    else if (player == 0)
        printf("\n\t       Draw!");
    printf("\n\n   Press any key to return to the main menu.\n");
    getch();
    resetBoard();
    drawMenu();
}

// Resets the game board ready for a new game
void resetBoard()
{
    board[1] = '1';
    board[2] = '2';
    board[3] = '3';
    board[4] = '4';
    board[5] = '5';
    board[6] = '6';
    board[7] = '7';
    board[8] = '8';
    board[9] = '9';
}

//
// Stack Methods Below
//

void init_stack(struct stack *s)
{
    s->top = -1;
}

void push_stack(struct stack *s, int item)
{
    if (s->top == 9 - 1)
    {
        return;
    }
    s->top++;
    s->array[s->top] = item;
}

int *pop_stack(struct stack *s)
{
    int *data;
    if (s->top == -1)
    {
        return NULL;
    }
    data = &s->array[s->top];
    s->top--;
    return data;
}