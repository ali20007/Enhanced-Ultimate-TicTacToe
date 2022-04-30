#include <iostream>
#include <sstream>
#include <chrono>
#include <unistd.h>
using namespace std;

bool computerturn = false;
bool computerisplaying = false;
enum Piece {TTTS_BLANK, TTTS_O, TTTS_X};//"Enum" means the variable must have one of the given values only -- gives the status of each cell
enum Status {NONE, TIE, O, X};// gives the status of the game (i.e who won),NONE (still can play)

class TicTacToeBoard
{
public:
    TicTacToeBoard();
    void initBoard();
    int Move(int cell, Piece _turn);
    Status update();
    Status getStatus();
    Piece _board[3][3];

private:
    Status _gameStatus;
};


TicTacToeBoard::TicTacToeBoard()
{
    initBoard();
    _gameStatus = NONE;
}

void TicTacToeBoard::initBoard()//initiating the small board and giving cell blank status
{
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
            _board[x][y] = TTTS_BLANK;
}

Status TicTacToeBoard::getStatus()//to check the status of the game
{
    return _gameStatus;
}

int TicTacToeBoard::Move(int cell, Piece _turn)//the next move to be performed
{
    /* player grid is displayed from 1
     * so 1 must be subtracted for the
     * correct index */
    cell = cell - 1;
    if(_board[cell/3][cell%3] == TTTS_BLANK) {
        _board[cell/3][cell%3] = _turn;//turn will be given according to x or o
        return 1;
    }
    return 0;  // cell occupied
}

Status TicTacToeBoard::update()//the function to check winning conditions
{
    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_board[i][j] == TTTS_BLANK)
                tie = false;//checks if the board is full, if yes then it is a tie

    if(tie) {
        _gameStatus = TIE;
        return TIE;
    }

    /* DIAGONALS */
    /* top-left to bottom-right */
    if(_board[0][0] != TTTS_BLANK &&
       _board[0][0] == _board[1][1] &&
       _board[1][1] == _board[2][2]) {
        _gameStatus = _board[0][0] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }

    /* top-right to bottom-left */
    if(_board[0][2] != TTTS_BLANK &&
       _board[0][2] == _board[1][1] &&
       _board[1][1] == _board[2][0]) {
        _gameStatus = _board[0][2] == TTTS_X ? X : O;
        return _gameStatus; // return winner
    }

    /* COLUMNS */
    for(int column = 0; column < 3; column++)
    {
        if(_board[0][column] == _board[1][column]
                && _board[0][column] != TTTS_BLANK
                && _board[1][column] == _board[2][column]) {
            _gameStatus = _board[0][column] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }

    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        if(_board[row][0] != TTTS_BLANK
            && _board[row][0] == _board[row][1]
            && _board[row][1] == _board[row][2]) {
            _gameStatus = _board[row][0] == TTTS_X ? X : O;
            return _gameStatus; // return winner
        }
    }

    return NONE; // no one has won yet
}


//The start of the full board declaration
class UltimateTicTacToe
{
public:
    UltimateTicTacToe();
    void displayBoards();
    char getTurn();
    void Move(int cell);
    int getBoardNo();
    void setBoardNo(int board_no);
    bool boardFinished();
    void selectNewBoard();
    Status update();
    int get_int(int,int,string);
private:
    int cu_board_no;
    void initStatuses();
    void setTurn();

       // current # tictactoe board
    Piece _turn;     // hold current player
    TicTacToeBoard _boards[3][3];
    Status _boardStatuses[3][3];  // store the status of each tictictoe game
};
int UltimateTicTacToe:: get_int(int minn,int maxx, string prompt)// A function used as test case for all inputs, returns the correct desired integer
{
    int ret_integer;
    string str_number;

    while(true) {

        cout << prompt;
        getline(cin, str_number); //get string input
        stringstream convert(str_number); //turns the string into a stream

        //checks for complete conversion to integer and checks for minimum value
        if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= minn && ret_integer <=maxx) return ret_integer;

        cin.clear(); //just in case an error occurs with cin (eof(), etc)
        cerr << "Input must be between " << minn << " and "<< maxx << "\n";
    }
}

UltimateTicTacToe::UltimateTicTacToe()
{
    _turn = TTTS_X;
    initStatuses();
}

void UltimateTicTacToe::initStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
            _boardStatuses[x][y] = NONE;
}

char UltimateTicTacToe::getTurn()//to check for the last entered turn
{
    return _turn == TTTS_X ? 'X' : 'O';
}

void UltimateTicTacToe::setTurn()//to apply the next turn according to the above function
{
    _turn = _turn == TTTS_X ? TTTS_O : TTTS_X;
}

int UltimateTicTacToe::getBoardNo()//to check for the last board's place entered
{
    return cu_board_no;
}

void UltimateTicTacToe::setBoardNo(int board_no)//to set or apply the next board's place according to the above function
{
    cu_board_no = board_no;
}

bool UltimateTicTacToe::boardFinished() //to check if board finished
{
        if(_boardStatuses[cu_board_no/3][cu_board_no%3] != NONE)
            return true;
        return false;
}

void UltimateTicTacToe::selectNewBoard()
{
    cout << "The game on the next board is finished, " << getTurn() << " select next board: ";
    if (computerisplaying == true)
        cu_board_no = rand()%9;
    else
        cu_board_no = get_int(1,9,"");
    cu_board_no -= 1;
    if(boardFinished())
        selectNewBoard();
}

void UltimateTicTacToe::Move(int cell)
{
    cout << "Board no: " << cu_board_no+1 << endl;  // convert x index to 2x

    if(_boards[cu_board_no/3][cu_board_no%3].Move(cell, _turn)) {
        // minus 1 for zero indexing and convert 2x index to x
        cu_board_no = cell - 1;
    } else {
        if (computerturn == true)
            cell = rand()%9;
        // chosen cell is already occupied
        else{
        cout << "Position already occupied. Try again." << endl;
        cout << "type New cell: ";
        cell = get_int(1,9,"");}
        Move(cell);  // call the function again with new parameters
    }
}

void UltimateTicTacToe::displayBoards()
{
    system("cls");//to keep the board from disappearing every time we make a move
    /*
     * shape of data (3, 3, 3, 3)
     * To print to a terminal correctly ,we need to print row n of each board first.
     * [0, 1, 2] [9, 10, 11] -> row
     * [3, 4, 5] [12, 13, 14] -> row
     * see: https://gist.github.com/c-rhodes/12ee674cbf0a9c86cbcb
     */
    cout << endl << endl;
    for(int w = 0; w < 3; w++) {
        for(int x = 0; x < 3; x++) {
            cout << "\t";
            for(int y = 0; y < 3; y++) {
                for(int z = 0; z < 3; z++) {
                    Piece player = _boards[w][y]._board[x][z];
                    char playerStr;
                    if(player == TTTS_O)
                        playerStr = 'O';
                    else if(player == TTTS_X)
                        playerStr = 'X';
                    else
                        playerStr = '_';
                    cout << playerStr << " ";
                }
                cout << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl << endl;
}

Status UltimateTicTacToe::update() //to check conditions of win for big board
{
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            _boardStatuses[x][y] = _boards[x][y].update();
        }
    }

    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_boardStatuses[i][j] == NONE)
                tie = false;

    if(tie)
        return TIE;

    /* DIAGONALS */
    /* top-left to bottom-right */
    if(_boardStatuses[0][0] != NONE &&
       _boardStatuses[0][0] == _boardStatuses[1][1] &&
       _boardStatuses[1][1] == _boardStatuses[2][2])
        return getTurn() == 'X' ? X : O;

    /* top-right to bottom-left */
    if(_boardStatuses[0][2] != NONE &&
       _boardStatuses[0][2] == _boardStatuses[1][1] &&
       _boardStatuses[1][1] == _boardStatuses[2][0])
        return getTurn() == 'X' ? X : O;

    bool match;
    /* COLUMNS */
    for(int row = 0; row < 3; row++)
    {
        match = true;
        for(int column = 0; column < 3 - 1; column++)
        {
            if(_boardStatuses[column][row] == NONE || _boardStatuses[column][row] != _boardStatuses[column+1][row])
            {
                match = false;
                break;
            }
        }
        if(match)
            return getTurn() == 'X' ? X : O;
    }
    match = true; // match is false set it true for next check
    /* END COLUMNS */

    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        match = true;
        for(int column = 0; column < 3 - 1; column++)
        {
            if(_boardStatuses[row][column] == NONE || _boardStatuses[row][column] != _boardStatuses[row][column+1])
            {
                match = false;
                break;
            }
        }
        if(match)
            return getTurn() == 'X' ? X : O;
    }
    /* END ROWS */

    setTurn(); // change player
    return NONE;
}

int get_int(int minn,int maxx, string prompt)// A function used as test case for all inputs, returns the correct desired integer
{
    int ret_integer;
    string str_number;

    while(true) {
        cout << prompt;
        getline(cin, str_number); //get input as a string until we press enter
        stringstream convert(str_number); //A built in function in the stringstream class that turns the numeric string into an integer number
        //checks for complete conversion to integer and checks for minimum value:
        if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= minn && ret_integer <=maxx)
            return ret_integer;
        cin.clear(); //just in case an error occurs with cin (eof(), etc)
        cerr << "Input must be an integer between " << minn << " and "<< maxx << "\n";//cerr is the built-in error function that displays the error message immediately
    }
}


int main()
{
    auto start = chrono::steady_clock::now();//The time calculating function which is used here because the longest function to take time is the update function
    UltimateTicTacToe board;
    board.displayBoards();//Display the 9 boards and their cells
    cout<<"Choose Playing Mode: 1)Player vs Computer   2)Player vs Player ";
    int mode = get_int(1,2,"");
    if (mode == 1)
        computerisplaying = true;
    cout<<endl;
    cout << "Enter the board number to start with: ";
    int board_no = get_int(1,9,"");
    board.setBoardNo(board_no-1); // minus 1 for zero-based indexing in arrays
    int cell;
    bool playing = true;
    int round = 1;//a variable to indicate the round when the computer is playing
    while(playing)
    {
        cout << "Player " << board.getTurn() << " select cell" << endl;
        cout << "cell: ";
        if(mode==2)
            cell = get_int(1,9,"");
        else
        while(1)
        {
            if(round%2==0)//the odd rounds are for the computer and even rounds for the player
                {cell = rand()%9;//used for making the computer play in a random cell
                computerturn = true;}
            else
                cell = get_int(1,9,"");
            round++;
            break;

        }
    board.Move(cell);
    board.displayBoards();
    int status = board.update();
    computerturn = false;

    switch(status)
        {
            case X:
                cout << "X player has won!" << endl;
                playing = false;
                break;
            case O:
                cout << "O player has won!" << endl;
                playing = false;
                break;
            case TIE:
                cout << "Game over. Tie" << endl;
                playing = false;
                break;
            default:
                break;
        }
    if(board.boardFinished())
        board.selectNewBoard();
    }
auto end = chrono::steady_clock::now();
    cout << "Elapsed time in nanoseconds: "<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()<< " ns" << endl;
}
