
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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

bool checkArchetype(string s){
    if(s == "Alchemist" || s == "alchemist" || s == "Paladin" || s == "paladin" || s == "Chronomage" || s == "chronomage"){
        return true;
    }else{
        cout << "Enter valid input!" << endl;
        return false;
    }
}

bool checkValidMark(string one, string two){
    if (one.length() == 1 && one != two)
    {
        return true;
    }else{
        cout << "Enter valid input!" << endl;
        return false;
    }
}
bool checkValidSwap(string M1, string M2, vector< vector<string>> b, int n1, int n2){
    if(n1 > 0 && n1 < 10 && n2 > 0 && n2 < 10){
        int r1 = (n1 - 1) / 3;
        int c1 = (n1 - 1) % 3;
        int r2 = (n2 - 1) / 3;
        int c2 = (n2 - 1) % 3;
        
        bool M1Check = (b[r1][c1] == M1 || b[r2][c2] == M1);
        bool M2Check = (b[r1][c1] == M2 || b[r2][c2] == M2);
        return (M1Check && M2Check);
    }else{
        return false;
    }
    
}

void swapValues(int n1, int n2, vector< vector<string>> &b, vector<string> r){
    int r1 = (n1 - 1) / 3;
    int c1 = (n1 - 1) % 3;
    int r2 = (n2 - 1) / 3;
    int c2 = (n2 - 1) % 3;
    
    string temp = b[r1][c1];
    b[r1][c1] = b[r2][c2];
    b[r2][c2] = temp;
    //printTable(r, b);
}

bool checkValidShift(string M1, string M2, vector< vector<string>> b, int n1, int n2){
    if(n1 > 0 && n1 < 10 && n2 > 0 && n2 < 10){
        
        int r1 = (n1 - 1) / 3;
        int c1 = (n1 - 1) % 3;
        int r2 = (n2 - 1) / 3;
        int c2 = (n2 - 1) % 3;
        if((b[r1][c1] == M1 || b[r1][c1] == M2) && (b[r2][c2] != M1 && b[r2][c2] != M2))
        {
            if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1 && !(r1 == r2 && c1 == c2)){
                return true;
            }else{
                cout << "Enter a valid adjacent place to shift!";
                return false;
            }
        }else{
            if((b[r1][c1] == M1 || b[r1][c1] == M2)) cout << "true";
            cout << "Enter a valid marked spot and an unoccupied space to shift it to!";
            return false;
        }
        
        return true;
    }else{
        cout << "Enter valid spaces within table!";
        return false;
    }
    
}

void shiftValues(int n1, int n2, vector< vector<string>> &b, vector<string> r){
    int r1 = (n1 - 1) / 3;
    int c1 = (n1 - 1) % 3;
    int r2 = (n2 - 1) / 3;
    int c2 = (n2 - 1) % 3;
    b[r2][c2] = b[r1][c1];
    
    vector< vector<string>> blank = { {  "1",  "2",  "3"},
        {  "4",  "5",  "6"},
        {  "7",  "8",  "9"} };;
    
    for (auto row1 = 0; row1 != b.size(); row1++) {
        for (auto col = 0; col != b[row1].size(); col++) {
            if(row1 == r1 && col == c1){
                b[r1][c1] = blank[row1][col];
            }
        }
    }
    
}

void playerTurn(string playerName, string mark, string archetype, vector<vector<string>>& b, vector<string>& r, bool& winFlag, bool& goFlag, string enemyMark, int& countA, int& countP)
{
    string input, rOrS;
    bool repeat = true;
    int num1, num2;

    cout << "\n" << playerName << " (" << archetype << ") Move!\n";

    if (archetype == "Alchemist" || archetype == "alchemist") {
        //static int count = 0;
        if (countA == 0) {cout << "An alchemist is a potions master with arcane knowledge of transfiguration! \nEvery move you can either make a regular tic-tac-toe move or swap two marks on the board\n";}
        
        if (countA >= 2) {
            bool rOrSCheck = false;
            do {
                cout << "Regular move or swap? (r/s): ";
                cin >> rOrS;
                if (rOrS == "r" || rOrS == "R" || rOrS == "s" || rOrS == "S")
                    rOrSCheck = true;
            } while (!rOrSCheck);

            if (rOrS == "r" || rOrS == "R") {
                cout << "Enter your move: ";
                cin >> input;
                do {
                    repeat = move(input, mark, b);
                    if (repeat) cin >> input;
                } while (repeat);
            } else {
                do {
                    cout << "Enter two numbers to swap: ";
                    cin >> num1 >> num2;
                } while (!checkValidSwap(mark, enemyMark, b, num1, num2));
                swapValues(num1, num2, b, r);
                winFlag = checkWin(b, mark);
                if (winFlag) {
                    cout << playerName << " wins!\n";
                    goFlag = false;
                } else if (checkFull(b)) {
                    cout << "It's a draw!\n";
                    goFlag = false;
                }
                if(checkWin(b, enemyMark)){
                    cout << "You made your opponent win!";
                    goFlag = false;
                }

            }
        } else {
            cout << "Enter your move: ";
            cin >> input;
            do {
                repeat = move(input, mark, b);
                if (repeat) cin >> input;
            } while (repeat);
            countA++;
        }
    }

    else if (archetype == "Paladin" || archetype == "paladin") {
        cout << "The Paladin is a stalwart guard that can force others around the battlefield! \nEvery move you can either make a regular tic-tac-toe move or shift one existing mark to an adjacent square.\n";
        //static int countP = 0;
        if (countP >=1){
            bool rOrShCheck = false;
            do {
                cout << "Regular move or shift? (r/s): ";
                cin >> rOrS;
                if (rOrS == "r" || rOrS == "R" || rOrS == "s" || rOrS == "S")
                    rOrShCheck = true;
            } while (!rOrShCheck);
            
            if (rOrS == "r" || rOrS == "R") {
                cout << "Enter your move: ";
                cin >> input;
                do {
                    repeat = move(input, mark, b);
                    if (repeat) cin >> input;
                } while (repeat);
            } else {
                
                do {
                    cout << "Enter the box number of what you want to shift and then where you want to shift it to, separated by spaces: ";
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> num1 >> num2;
                } while (!checkValidShift(mark, enemyMark, b, num1, num2));
                shiftValues(num1, num2, b, r);
                winFlag = checkWin(b, mark);
                if (winFlag) {
                    cout << playerName << " wins!\n";
                    goFlag = false;
                } else if (checkFull(b)) {
                    cout << "It's a draw!\n";
                    goFlag = false;
                }
                if(checkWin(b, enemyMark)){
                    cout << "You made your opponent win!";
                    goFlag = false;
                }
            }
        }else{
            cout << "Enter your move: ";
            cin >> input;
            do {
                repeat = move(input, mark, b);
                if (repeat) cin >> input;
            } while (repeat);
            countP++;
        }
       
    }
    
   // printTable(r, b);
    winFlag = checkWin(b, mark);
    if (winFlag) {
        cout << playerName << " wins!\n";
        goFlag = false;
    } else if (checkFull(b)) {
        cout << "It's a draw!\n";
        goFlag = false;
    }
}

// MAIN
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
    char rOrB;
    string rOrS;
    string markP1;
    string markP2;
    bool choose = true;
    string archetypeP1;
    string archetypeP2;
    int countA = 0, countP = 0;
    
    do{//tester
        
    while (choose){
        
cout << "Regular or Battle Tic Tac Toe ? Enter r or b: \n";
cin >> rOrB;
    
    if (rOrB == 'b' || rOrB == 'B')
    {
        choose = false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
        do{
            cout << "Enter your desired mark (single character) Player 1: ";
            getline(cin, markP1);
           
        }while(!checkValidMark(markP1, " "));
        
        cout << "Player 1, your mark is : " << markP1 << endl;
        
        do{
            cout << "Enter your desired mark (single character) Player 2: ";
            getline(cin, markP2);
           
        }while(!checkValidMark(markP2, markP1));
       
        cout << "Player 2, your mark is : " << markP2 << endl;
       
        do{
            cout << "Player 1 -- Choose an archetype: Paladin Or Alchemist" << endl;
            getline(cin, archetypeP1);
        }while(!checkArchetype(archetypeP1));
        cout << "Player 1 -- You chose " << archetypeP1 << endl;
        
        do{
            cout << "Player 2 -- Choose an archetype: Paladin Or Alchemist" << endl;
            getline(cin, archetypeP2);
        }while(!checkArchetype(archetypeP2));
        cout << "Player 2 -- You chose " << archetypeP2 << endl;
        
            b = { {  "1",  "2",  "3"},
                {  "4",  "5",  "6"},
                {  "7",  "8",  "9"} };
           
            do
            {
            
                printTable(r, b);
                playerTurn("Player 1", markP1, archetypeP1, b, r, winU, go, markP2, countA, countP);

                if (go)
                {
                printTable(r, b);
                playerTurn("Player 2", markP2, archetypeP2, b, r, winC, go, markP2, countA, countP);

                        
                    }
                
            } while (go);
            
            
        
        
        //REGULAR
    }else if(rOrB == 'r' || rOrB == 'R') {
        choose = false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        do
//        {
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
            
//            //check to play again
//            char reply;
//            cout << "Again? (y/n)";
//            cin >> reply;
//            if (reply == 'Y' || reply == 'y')
//            {
//                again = true;
//            }else{
//                again = false;
//            }
//        }while(again);
    }//while choose
    }// if else for battle or regular
        
        //check to play again
        string reply;
        bool yOrnCheck = false;
        do {
            cout << "Again? (y/n): ";
            cin >> reply;
            if (reply == "y" || reply == "Y" || reply == "n" || reply == "N")
                yOrnCheck = true;
        } while (!yOrnCheck);
        
        if (reply == "Y" || reply == "y")
        {
            again = true;
            choose = true;
        }else{
            again = false;
        }

        
    }while(again);
        cout << "Thank you for playing TicTacToe!";
    
}
