#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------------------------------------------------------------------
// Setting up types and constants.  This section doesn't need to be changed.
//-----------------------------------------------------------------------------

// A board object contains the entire current state of a game. It contains the
// cells, the player whose turn it is, and the number of moves made in total.
// The name 'Board' is a synonym for the type 'struct board'.
struct board {
    char cells[3][3];
    char player;
    int moves;

};
typedef struct board Board;

// A row/column position in the board.
// The name 'Position' is a synonym for the type 'struct position'.
struct position { int row, col; };
typedef struct position Position;

// Constants for player X, player O, and blank.
enum { X = 'X', O = 'O', B = ' ' };

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.  Change these.
//-----------------------------------------------------------------------------

// DONE: finish this function
// Initialize a blank board for a new game, with the given player to move first.
void newGame(Board *b, char player) {
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++) {
      b->cells[i][j] = B;
    };
  b->player = X;
  b->moves  = 0;
  }
}

// TODO: finish this function
// Prepare to make a move by converting a string such as "a2" to a row and
// column.  Return false if the string is invalid, or the cell isn't blank.
bool position(Board *b, char text[3], Position *p) {

//Checking text only one letter and one number
  if (strlen(text) > 2) return false;

//Sorting if row and column in spec
  char rowch = text[0], colch = text[1];
  if ((rowch < 'a') || (rowch > 'c')) return false;
  if ((colch < '1') || (colch > '3')) return false;

//Sorting if cell is blank
  p->row = text[0] - 'a';
  p->col = text[1] - '1';
  if(b->cells[p->row][p->col] != B ) return false;

//If nothing returns false, then must be true
  return true;
}

// TODO: finish this function
// Make a move at the given position, assuming that it is valid.
void move(Board *b, Position *p) {
  b->cells[p->row][p->col] = b->player;
    if (b->player == X) b->player = O;
    else b->player = X;
  b->moves++;
  }

// TODO: finish this function
// Check whether x, y, z form a winning line.
bool line(char x, char y, char z) {
    return (x==y) && (x==z) && (z != B);
}

// TODO: finish this function
// Check whether or not the player who has just moved has won.
bool won(Board *b) {
//Each if statement is one of 8 possible winning moves
  if (line (b->cells[0][0], b->cells[0][1], b->cells[0][2])) return true;
  if (line (b->cells[1][0], b->cells[1][1], b->cells[1][2])) return true;
  if (line (b->cells[2][0], b->cells[2][1], b->cells[2][2])) return true;
  if (line (b->cells[0][0], b->cells[1][0], b->cells[2][0])) return true;
  if (line (b->cells[0][1], b->cells[1][1], b->cells[2][1])) return true;
  if (line (b->cells[0][2], b->cells[1][2], b->cells[2][2])) return true;
  if (line (b->cells[0][0], b->cells[1][1], b->cells[2][2])) return true;
  if (line (b->cells[0][2], b->cells[1][1], b->cells[2][0])) return true;
//If no winning moves played, then no winner
  else return false;

}

// TODO: finish this function
// Check whether the game is drawn
bool drawn(Board *b) {
  //End game after 9 moves
  return (b->moves >= 9);
}

// TODO: finish this function
//Display the board.
void display(Board *b) {

  printf("   1   2   3\n\n");
  printf("a  %c | %c | %c\n", b->cells[0][0], b->cells[0][1], b->cells[0][2]);
  printf("  -----------\n");
  printf("b  %c | %c | %c\n", b->cells[1][0], b->cells[1][1], b->cells[1][2]);
  printf("  -----------\n");
  printf("c  %c | %c | %c \n", b->cells[2][0], b->cells[2][1], b->cells[2][2]);

}

//This is asking the user to input a valid moves
void ask(Board *b, Position *p){
    char line[100];
    bool ok = false;
    while ( ! ok ) {
        printf("\n");
        printf("It is %c's turn\n", b->player);
        printf("Please type in a letter and number, eg b3\n");
        fgets (line, 100, stdin);
        line[strcspn(line, "\r\n")] = '\0';
        ok = position(b, line, p);
    }
}

// TODO: finish this function
// Play the game interactively between two human players who take turns.
void play(char player) {
  Board bdata;
  Board *b = &bdata;
  Position pdata;
  Position *p = &pdata;
  newGame(b,p);
  bool done = false;
  display(b);
  while (! done) {
      ask(b, p);
      move(b, p);
      display(b);
      done = won(b) || drawn(b);
  }
 }

//-----------------------------------------------------------------------------
// Testing and running: nothing after this point needs to be changed.
//-----------------------------------------------------------------------------

// Constants representing types.
enum type { CHAR, INT, BOOL };

// Check that two ints, chars or bools are equal
int eq(enum type t, int x, int y) {
    static int n = 0;
    n++;
    if (x != y) {
        if (t==CHAR) fprintf(stderr, "Test %d gives %c not %c\n", n, x, y);
        if (t==INT) fprintf(stderr, "Test %d gives %d not %d\n", n, x, y);
        if (t==BOOL && x) fprintf(stderr, "Test %d gives true not false\n", n);
        if (t==BOOL && y) fprintf(stderr, "Test %d gives false not true\n", n);
        exit(1);
    }
    return n;
}

// More specific versions of the eq function
int eqc(char x, char y) { return eq(CHAR, x, y); }
int eqi(int x, int y) { return eq(INT, x, y); }
int eqb(bool x, bool y) { return eq(BOOL, x, y); }

void test() {
    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;

    // Tests 1 to 5 (new board)
    newGame(board, X);
    eqc(board->cells[0][0], B);
    eqc(board->cells[1][2], B);
    eqc(board->cells[2][1], B);
    eqc(board->player, X);
    eqc(board->moves, 0);

    // Tests 6 to 14 (valid positions)
    eqb(position(board, "a1", pos), true);
    eqi(pos->row, 0);
    eqi(pos->col, 0);
    eqb(position(board, "b3", pos), true);
    eqi(pos->row, 1);
    eqi(pos->col, 2);
    eqb(position(board, "c1", pos), true);
    eqi(pos->row, 2);
    eqi(pos->col, 0);

    // Tests 15 to 22 (invalid positions, and occupied squares)
    eqb(position(board, "d2", pos), false);
    eqb(position(board, "b0", pos), false);
    eqb(position(board, "b4", pos), false);
    eqb(position(board, "2b", pos), false);
    eqb(position(board, "b2x", pos), false);
    eqb(position(board, "b", pos), false);
    eqb(position(board, "", pos), false);
    *board = (Board) {{{B,B,B},{B,B,B},{B,X,B}},O,1};
    eqb(position(board, "c2", pos), false);

    // Tests 23 to 28 (moves)
    newGame(board, 'X');
    position(board, "b2", pos);
    move(board, pos);
    eqc(board->cells[1][1], X);
    eqc(board->player, O);
    eqc(board->moves, 1);
    position(board, "a3", pos);
    move(board, pos);
    eqc(board->cells[0][2], O);
    eqc(board->player, X);
    eqc(board->moves, 2);

    // Tests 29 to 36 (winning lines)
    eqb(line(X, X, X), true);
    eqb(line(O, O, O), true);
    eqb(line(X, O, O), false);
    eqb(line(O, X, O), false);
    eqb(line(O, O, X), false);
    eqb(line(B, B, B), false);
    eqb(line(X, B, B), false);
    eqb(line(O, O, B), false);

    // Tests 37-44 (won function, winning lines)
    *board = (Board) {{{X,X,X},{B,O,B},{B,O,B}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{X,X,X},{B,O,B}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{B,O,B},{X,X,X}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{O,B,B},{O,X,B},{O,B,X}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{B,O,B},{X,O,B},{B,O,X}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{B,B,O},{X,B,O},{B,B,O}},X,5};
    eqb(won(board), true);
    *board = (Board) {{{X,B,O},{B,X,O},{B,B,X}},O,5};
    eqb(won(board), true);
    *board = (Board) {{{X,B,O},{B,O,X},{O,B,B}},X,5};
    eqb(won(board), true);

    // Tests 45-48 (won function, no winning line)
    *board = (Board) {{{B,B,B},{B,B,B},{B,B,B}},X,0};
    eqb(won(board), false);
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(won(board), false);
    *board = (Board) {{{X,O,X},{X,O,O},{O,X,O}},X,9};
    eqb(won(board), false);
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(won(board), false);

    // Tests 49-50 (drawn function)
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(drawn(board), false);
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(drawn(board), true);

    //checking display
    Board bcheck = {{{B,B,B},{B,B,B},{B,B,B}},X,-1};
    Board *check = &bcheck;
    display(check);

    printf("Tests passed: %d\n", eqi(0, 0) - 1);
}

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(args[1][0]);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(args[2][0]);
    else {
        fprintf(stderr, "Use: ./oxo  OR  ./oxo X  OR  ./oxo O\n");
        exit(1);
    }

    return 0;
}
