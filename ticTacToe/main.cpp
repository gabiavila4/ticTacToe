
#include <iostream>
#include <vector>
#include <string>

using namespace std;
bool checkWin(vector<vector<string>>& board, string XorO) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == XorO) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == XorO) return true;
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == XorO) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == XorO) return true;

    return false;
}
void printTable(vector<string> r, vector< vector<string>> b){
    //auto automatically gets the correct type for your loop variable
    for (auto row1 = 0; row1 != b.size(); row1++)
    {
        for (auto col = 0; col != b[row1].size(); col++)
        {
            if(col == 0)
            {
            cout << " ";
            }
            cout << b[row1][col];
            if (col != 2)
            {
                cout << " | ";
            }
        }
        if(row1 != 2)
        {
        cout << "\n---+---+---";
        }
        cout << "\n";
    }
}

bool move(string in, string ch, vector< vector<string>> &b)
{
    for (auto row1 = 0; row1 != b.size(); row1++)
    {
        for (auto col = 0; col != b[row1].size(); col++)
        {
            if (b[row1][col] == in)
            {

                if (b[row1][col] != "X" && b[row1][col] != "O") {
                b[row1][col] = ch;
                return false;
                } else {
                cout << "Taken! Try again: ";
                return true;
                }
            }
        }
    }
    cout << "Invalid input! Try again: ";
    return true;
}

bool checkFull(vector< vector<string>> &b)
{
    for (auto row1 = 0; row1 != b.size(); row1++) {
        for (auto col = 0; col != b[row1].size(); col++) {
            if (b[row1][col] != "X" && b[row1][col] != "O") {
            return false; // Found an empty spot
                
            }
        }
    }
    return true;
}

int main(void){


typedef vector<string> v1D;
typedef vector<v1D> v2D;
v1D r;

v2D b = { {  "1",  "2",  "3"},
          {  "4",  "5",  "6"},
          {  "7",  "8",  "9"} };
bool go = true;
bool repeatU = true;
bool repeatC = true;
bool winU;
bool winC;
bool again = false;
string input;
string input2;
    
do
{
    b = { {  "1",  "2",  "3"},
          {  "4",  "5",  "6"},
          {  "7",  "8",  "9"} };
    do
    {
        //print table
        printTable(r, b);
        //repeatU = true;
        cout << "\nPlayer 1 Move!\t";
        cin >> input;
        
        repeatU = true;
        do
        {

            repeatU = move(input, "X", b);
            if (repeatU) cin >> input;
            

        }while (repeatU);
        
        printTable(r, b);
        winU = checkWin(b, "X");
        if (winU)
        {
            cout << "Player 1 wins!\n";
            go = false;
            printTable(r, b);
            break;
        }else{
            
            go = true;
        }
        

        if (checkFull(b)) {
            cout << "It's a draw!\n";
            break;
        }
        
        
        
        if (go)
        {
            cout << "\nPlayer 2 Move!\n";
            cin >> input2;
            repeatC = true;
            do
            {
                

            repeatC = move(input2, "O", b);
            if (repeatC) cin >> input2;
                
            } while (repeatC);
            winC = checkWin(b, "O");
            
            if (winC)
            {
                cout << "Player 2 wins!\n";
                go = false;
                
                printTable(r, b);
                break;
            }
        }
    } while (go);
    
    //check to play again
    char reply;
    cout << "Again? (y/n)";
    cin >> reply;
    if (reply == 'Y' || reply == 'y')
    {
        again = true;
    }
}while(again);
   

cout << "Thank you for playing TicTacToe!";

}
