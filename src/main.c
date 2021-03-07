#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <string.h>

void printBoard();
void printBorder();

char board[9] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};

char turn = 'O';

int getBoardPosition(int in) {
    switch(in) {
        case '7':
            return 0;
            break;
        case '8':
            return 1;
            break;
        case '9':
            return 2;
            break;
        case '4':
            return 3;
            break;
        case '5':
            return 4;
            break;
        case '6':
            return 5;
            break;
        case '1':
            return 6;
            break;
        case '2':
            return 7;
            break;
        case '3':
            return 8;
            break;
 
    }
}

void handleBoard(int in) {
    int pos = getBoardPosition(in);
    if(board[pos] == ' ') {
        board[pos] = turn;
    }
}

void printBoard() {
    int row = 0;
    int col = 0;
    for (int i = 0; i<9; i++) {
        mvaddch(row*3, 30+col*20, board[i]);
        col++;
        if(i == 2 || i == 5) {
            row++;
            col = 0;
        }
    }
    printBorder();
}

void printBorder() {
    for (int i = 25; i<80; i++) {
        mvaddch(1, i, '_');
        mvaddch(4, i, '_');
    }
    for (int row = 0; row<7; row++) {
        mvaddch(row, 40, '|');
        mvaddch(row, 60, '|');
    }
}

int allContain(int turn, int one, int two, int three) {
    return turn == board[one] && turn == board[two] && turn == board[three];
}

int isWon(int turn) {
    // Check for horizontal match
    if(allContain(turn, 0,1,2) || allContain(turn, 3,4,5) || allContain(turn, 6,7,8)) {
        return 1;
    }
    //Check for vertical match
    if(allContain(turn, 0,3,6) || allContain(turn, 1,4,7) || allContain(turn, 2,5,8)) {
        return 1;
    }
    // Check for diagonal match
    if(allContain(turn, 0,4,8) || allContain(turn, 2,4,6)) {
        return 1;
    }
    return 0;
}

int findWinner() {
    if(isWon('X')) {
        return 'X';
    } else if(isWon('O')) {
        return 'O';
    } else {
        return ' ';
    }
}

int isOver() {
    int countEmpty = 0;
    for(int i = 0;i<9; i++) {
        if(board[i] == ' ') {
            countEmpty++;
        }
    }
    return !countEmpty;
}

void printWinner(int winner) {
    char out[6];
    out[0] = winner;
    out[1] = '\0';
    strcat(out, " won!");

    mvaddstr(0,0,out);
}

int main() {
    WINDOW * mainwin;

    
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(EXIT_FAILURE);
    }


    /*  Display "Hello, world!" in the centre of the
	screen, call refresh() to show our changes, and
	sleep() for a few seconds to get the full screen effect  */
/*  Print message  */

    noecho();
    keypad(mainwin, TRUE);

    printBoard();
    while(1) {
        int winner;
        winner = findWinner();
        if(winner != ' ') {
            erase();
            printWinner(winner);
            refresh();
            continue;
        } 
        int ch = getch();
        if(ch == 'q') {
            break;
        }
        handleBoard(ch);
        if(isOver()) {
            break;
        }
        printBoard();
        turn = turn == 'O' ? 'X': 'O';
        refresh();
    }

    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}