
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
    if(n1 && n2 > 0 && n1 && n2 < 10){
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

void playerTurn(string playerName, string mark, string archetype, vector<vector<string>>& b, vector<string>& r, bool& winFlag, bool& goFlag, string enemyMark)
{
    string input, rOrS;
    bool repeat = true;
    int num1, num2;

    cout << "\n" << playerName << " (" << archetype << ") Move!\n";

    if (archetype == "Alchemist" || archetype == "alchemist") {
        static int count = 0;
        if (count >= 2) {
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

            }
        } else {
            cout << "Enter your move: ";
            cin >> input;
            do {
                repeat = move(input, mark, b);
                if (repeat) cin >> input;
            } while (repeat);
            count++;
        }
    }

    else if (archetype == "Paladin" || archetype == "paladin") {
       
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
    int num1;
    int num2;
    int count = 0;
    
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
        
        
        //mark = markk[0];
        cout << "Player 1, your mark is : " << markP1 << endl;
        
       
      
        do{
            cout << "Enter your desired mark (single character) Player 2: ";
            getline(cin, markP2);
           
        }while(!checkValidMark(markP2, markP1));
        
        //mark = markk[0];
        cout << "Player 2, your mark is : " << markP2 << endl;
        
        
        do{
            cout << "Player 1 -- Choose an archetype: Paladin, Alchemist or Chronomage" << endl;
            getline(cin, archetypeP1);
        }while(!checkArchetype(archetypeP1));
        cout << "Player 1 -- You chose " << archetypeP1 << endl;
        
        do{
            cout << "Player 2 -- Choose an archetype: Paladin, Alchemist or Chronomage" << endl;
            getline(cin, archetypeP2);
        }while(!checkArchetype(archetypeP2));
        cout << "Player 2 -- You chose " << archetypeP2 << endl;
        
        if(archetypeP1 == "Alchemist" || archetypeP1 == "alchemist"){
            cout << "An alchemist is a potions master with arcane knowledge of transfiguration! \nEvery move you can either make a regular tic-tac-toe move or swap two marks on the board\n";
            
            b = { {  "1",  "2",  "3"},
                {  "4",  "5",  "6"},
                {  "7",  "8",  "9"} };
           
            do
            {
            
           printTable(r, b);
                playerTurn("Player 1", markP1, archetypeP1, b, r, winU, go, markP2);
//            cout << "\nPlayer 1 Move!\t";
//                bool rOrSCheck = false;
//                if (count >= 2){
//                    do{
//                        cout << "Would you like to make a regular move or swap? (r/s)";
//                        cin >> rOrS;
//                        if (rOrS == "R" || rOrS == "r" || rOrS == "S" || rOrS == "s"){
//                            rOrSCheck = true;
//                        }else {
//                        cout << "INVALID!";
//                        
//                        }
//                    }while(!rOrSCheck);
//                    if (rOrS == "R" || rOrS == "r"){
//                        cout << "Enter your move!";
//                        cin >> input;
//                        repeatU = true;
//                        do
//                        {
//                            repeatU = move(input, markP1, b);
//                            if (repeatU) cin >> input;
//                           
//                        }while (repeatU);
//                        
//                        //printTable(r, b);
//                        winU = checkWin(b, markP1);
//                        if (winU)
//                        {
//                            cout << "Player 1 wins!\n";
//                            go = false;
//                            printTable(r, b);
//                            break;
//                        }else{
//                            
//                            go = true;
//                        }
//                        
//                        if (checkFull(b)) {
//                            cout << "It's a draw!\n";
//                            break;
//                        }
//                    }else if(rOrS == "S" || rOrS == "s"){
//                        
//                        do{
//                            cout << "Enter the two you want to swap, separated by spaces please!";
//                            cin >> num1 >> num2;
//                           
//                        } while(!checkValidSwap(markP1, markP2, b, num1, num2));
//                        swapValues(num1, num2, b, r);
//                        winU = checkWin(b, markP1);
//                        if (winU)
//                        {
//                            cout << "Player 1 wins!\n";
//                            go = false;
//                            printTable(r, b);
//                            break;
//                        }else{
//                            
//                            go = true;
//                        }
//                        
//                        if (checkFull(b)) {
//                            cout << "It's a draw!\n";
//                            break;
//                        }
//                        
//                    }
//                }else{
//                    cout << "Enter your move!";
//                    cin >> input;
//                    repeatU = true;
//                    do
//                    {
//                        repeatU = move(input, markP1, b);
//                        if (repeatU) cin >> input;
//                       
//                    }while (repeatU);
//                    
//                    printTable(r, b);
//                    count ++;
//                    winU = checkWin(b, markP1);
//                    if (winU)
//                    {
//                        cout << "Player 1 wins!\n";
//                        go = false;
//                        printTable(r, b);
//                        break;
//                    }else{
//                        go = true;
//                    }
//                    
//                    if (checkFull(b)) {
//                        cout << "It's a draw!\n";
//                        break;
//                    }
//                    
//                }
                
             
                if (go)
                {
                   printTable(r, b);
                    playerTurn("Player 2", markP2, archetypeP2, b, r, winC, go, markP2);
//                    cout << "\nPlayer 2 Move!\n";
//                    
//                    if (count >= 2){
//                        rOrSCheck = false;
//                        
//                            do{
//                                cout << "Would you like to make a regular move or swap? (r/s)";
//                                cin >> rOrS;
//                                if (rOrS == "R" || rOrS == "r" || rOrS == "S" || rOrS == "s"){
//                                    rOrSCheck = true;
//                                }else {
//                                    cout << "INVALID!";
//                                    
//                                }
//                            }while(!rOrSCheck);
//                            
//                            if (rOrS == "R" || rOrS == "r"){
//                                cout << "Enter your move!";
//                                cin >> input2;
//                                repeatC = true;
//                                do
//                                {
//                                    repeatC = move(input2, markP2, b);
//                                    if (repeatC) cin >> input2;
//                                    
//                                }while (repeatC);
//                                
//                                //printTable(r, b);
//                                winC = checkWin(b, markP2);
//                                if (winC)
//                                {
//                                    cout << "Player 2 wins!\n";
//                                    go = false;
//                                    printTable(r, b);
//                                    break;
//                                }else{
//                                    
//                                    go = true;
//                                }
//                                
//                                if (checkFull(b)) {
//                                    cout << "It's a draw!\n";
//                                    break;
//                                }
//                                
//                            }else if(rOrS == "S" || rOrS == "s"){
//                                
//                                do{
//                                    cout << "Enter the two you want to swap, separated by spaces please!";
//                                    cin >> num1 >> num2;
//                                    
//                                } while(!checkValidSwap(markP1, markP2, b, num1, num2));
//                                swapValues(num1, num2, b, r);
//                                winC = checkWin(b, markP2);
//                                if (winC)
//                                {
//                                    cout << "Player 2 wins!\n";
//                                    go = false;
//                                    printTable(r, b);
//                                    break;
//                                }else{
//                                    go = true;
//                                }
//                                
//                                if (checkFull(b)) {
//                                    cout << "It's a draw!\n";
//                                    break;
//                                }
//                                
//                            }
//                        }else{
//                            cout << "Enter your move!";
//                            cin >> input2;
//                            repeatC = true;
//                            do
//                            {
//                                repeatC = move(input2, markP2, b);
//                                if (repeatC) cin >> input2;
//                                
//                            }while (repeatC);
//                            
//                            //printTable(r, b);
//                            count ++;
//                            winC = checkWin(b, markP2);
//                            if (winC)
//                            {
//                                cout << "Player 2 wins!\n";
//                                go = false;
//                                printTable(r, b);
//                                break;
//                            }else{
//                                go = true;
//                            }
//                            
//                            if (checkFull(b)) {
//                                cout << "It's a draw!\n";
//                                break;
//                            }
//                            
//                        }
                        
                    }
                
            } while (go);
            
            
        }
        
        //REGULAR
    }else if(rOrB == 'r' || rOrB == 'R') {
        choose = false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            }else{
                again = false;
            }
        }while(again);
    }//while choose
    }// if else for battle or regular
        cout << "Thank you for playing TicTacToe!";
    
}
