
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <cctype>  // isdigit
#include <limits>  // numeric_limits
using namespace std;



string readLineTrimmed() {
    string s;
    getline(cin, s);
    // trim leading/trailing
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string readSingleToken() {
    string line = readLineTrimmed();
    while (line.size() == 0) {
       
        line = readLineTrimmed();
    }
   
    size_t pos = line.find_first_of(" \t");
    if (pos == string::npos) return line;
    return line.substr(0, pos);
}

int randBetween(int a, int b) {
    if (b < a) return a;
    int r = rand() % (b - a + 1) + a;
    return r;
}

//Tic-Tac-Toe Functions

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
    for (auto row1 = 0; row1 != b.size(); row1++)
    {
        for (auto col = 0; col != b[row1].size(); col++)
        {
            if(col == 0) cout << " ";
            cout << b[row1][col];
            if (col != 2) cout << " | ";
        }
        if(row1 != 2) cout << "\n---+---+---";
        cout << "\n";
    }
}

bool movePlace(string in, string ch, vector< vector<string>> &b)
{
    for (auto row1 = 0; row1 != b.size(); row1++)
    {
        for (auto col = 0; col != b[row1].size(); col++)
        {
            if (b[row1][col] == in)
            {
                if (b[row1][col] != "X" && b[row1][col] != "O" && !(b[row1][col].size()==1 && !isdigit(b[row1][col][0]))) {
                    
                }
                if (b[row1][col] != "X" && b[row1][col] != "O" && (b[row1][col].size()==1 && isdigit(b[row1][col][0]) || b[row1][col] != "X")) {
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
            // if still a digit placeholder -> not full
            if (b[row1][col].size() == 1 && isdigit(b[row1][col][0])) {
                return false;
            }
        }
    }
    return true;
}



struct Player {
    string name;
    string clas; // "Paladin" or "Alchemist"
    int maxHP;
    int hp;
    int atk;
    int def;
    int gold;
    string mark; // single char string
    int paladinCount; // how many paladin moves done
    int alchemistCount; // how many alchemist moves done
};

struct Foe {
    string id;
    string name;
    int maxHP;
    int hp;
    int atk;
    int def;
    string mark;
    string special; // simple string describing special
};



bool checkArchetype(string s){
    if(s == "Alchemist" || s == "alchemist" || s == "Paladin" || s == "paladin" || s == "Chronomage" || s == "chronomage"){
        return true;
    }else{
        cout << "Enter valid input!" << endl;
        return false;
    }
}

bool checkValidMark(string one, string two){
    if (one.length() != 1) {
        cout << "Mark must be one character!\n";
        return false;
    }
    if (isdigit(one[0])) {
        cout << "Mark cannot be a number!\n";
        return false;
    }
    if (one == two) {
        cout << "Marks must be different!\n";
        return false;
    }
    return true;
}


bool checkValidSwap(string M1, string M2, vector< vector<string>> b, int n1, int n2){
    if(n1 > 0 && n1 < 10 && n2 > 0 && n2 < 10){
        int r1 = (n1 - 1) / 3;
        int c1 = (n1 - 1) % 3;
        int r2 = (n2 - 1) / 3;
        int c2 = (n2 - 1) % 3;
        string a = b[r1][c1];
        string bb = b[r2][c2];
        if (a.size()==1 && isdigit(a[0])) return false;
        if (bb.size()==1 && isdigit(bb[0])) return false;
        bool ok = ( (a==M1 && bb==M2) || (a==M2 && bb==M1) );
        return ok;
    }else{
        return false;
    }
}


bool checkValidShift(string M1, string M2, vector< vector<string>> b, int n1, int n2){
    if(n1 > 0 && n1 < 10 && n2 > 0 && n2 < 10){
        int r1 = (n1 - 1) / 3;
        int c1 = (n1 - 1) % 3;
        int r2 = (n2 - 1) / 3;
        int c2 = (n2 - 1) % 3;
     
        if (!(b[r1][c1].size()==1 && (b[r1][c1][0]==M1[0] || b[r1][c1][0]==M2[0]) )) {
            cout << "Source must be a marked spot.\n";
            return false;
        }
       
        if (!(b[r2][c2].size()==1 && isdigit(b[r2][c2][0]))) {
            cout << "Destination must be empty (number).\n";
            return false;
        }
      
        if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1 && !(r1==r2 && c1==c2)) {
            return true;
        } else {
            cout << "Enter a valid adjacent place to shift!\n";
            return false;
        }
    } else {
        cout << "Enter valid spaces within table!\n";
        return false;
    }
}

// Swap and Shift

void swapValues(int n1, int n2, vector< vector<string>> &b, vector<string> r){
    int r1 = (n1 - 1) / 3;
    int c1 = (n1 - 1) % 3;
    int r2 = (n2 - 1) / 3;
    int c2 = (n2 - 1) % 3;
    string temp = b[r1][c1];
    b[r1][c1] = b[r2][c2];
    b[r2][c2] = temp;
}

void shiftValues(int n1, int n2, vector< vector<string>> &b, vector<string> r){
    int r1 = (n1 - 1) / 3;
    int c1 = (n1 - 1) % 3;
    int r2 = (n2 - 1) / 3;
    int c2 = (n2 - 1) % 3;
    b[r2][c2] = b[r1][c1];
 
    int val = r1*3 + c1 + 1;
    b[r1][c1] = string(1, char('0' + val));
}

void applyFoeSpecial(Foe &f, Player &p) {
    int chance = randBetween(1,100);
    
    if (chance > 35) return;
    if (f.special == "Stone Shield") {
        cout << f.name << " uses Stone Shield! Their defense increases temporarily by 3 for next hit.\n";
        f.def += 3;
    } else if (f.special == "Molten Burst") {
        int extra = max(1, f.atk / 2);
        p.hp -= extra;
        cout << f.name << " unleashes Molten Burst for " << extra << " extra damage!\n";
    } else if (f.special == "Tide Heal") {
        int heal = max(3, f.maxHP / 8);
        f.hp += heal;
        if (f.hp > f.maxHP) f.hp = f.maxHP;
        cout << f.name << " calls the tide and heals " << heal << " HP!\n";
    } else if (f.special == "Gale Push") {
        int small = max(1, f.atk / 4);
        p.hp -= small;
        cout << f.name << " uses Gale Push and pushes you for " << small << " damage!\n";
    } else if (f.special == "AvatarFlare") {
        int big = max(5, f.atk);
        p.hp -= big;
        cout << f.name << " uses AvatarFlare dealing " << big << " damage!\n";
    } else if (f.special == "AvatarHeal") {
        int hh = max(5, f.maxHP / 6);
        f.hp += hh;
        if (f.hp > f.maxHP) f.hp = f.maxHP;
        cout << f.name << " draws power and heals " << hh << " HP!\n";
    } else {
       
        int d = 2;
        p.hp -= d;
        cout << f.name << " does a strange thing and you lose " << d << " HP.\n";
    }
}

void foeRandomMove(Foe &f, vector< vector<string>> &b) {
    vector<int> freeCells;
    for (int i=1;i<=9;i++){
        int r = (i-1)/3;
        int c = (i-1)%3;
        if (b[r][c].size()==1 && isdigit(b[r][c][0])) freeCells.push_back(i);
    }
    if (freeCells.size() == 0) return;
    int pickIndex = randBetween(0, (int)freeCells.size()-1);
    int pick = freeCells[pickIndex];
    int rr = (pick-1)/3;
    int cc = (pick-1)%3;
    b[rr][cc] = f.mark;
}

//damage

int computeDamage(int attacker, int defender) {
    int d = attacker - defender;
    if (d < 0) d = 0;
    return d;
}

//match

int playMatch(Player &player, Foe &foe) {
    vector<vector<string>> b = { {"1","2","3"}, {"4","5","6"}, {"7","8","9"} };
    vector<string> r;
    string pMark = player.mark;
    string fMark = foe.mark;
    bool playerSwapAvailable = false;
    if (player.clas == "Alchemist" || player.clas == "alchemist") {
        if (player.alchemistCount >= 1) playerSwapAvailable = true;
    }
    int turn = randBetween(0,1);

    while (true) {
        if (turn == 0) {
            // player's turn
            printTable(r, b);
            cout << player.name << "'s turn. (HP " << player.hp << ")\n";
           
            if ((player.clas == "Paladin" || player.clas == "paladin") && player.paladinCount >= 1) {
                cout << "You may (r)egular move or (s)hift an existing mark. Choose r/s or press enter for regular: ";
                string choice = readSingleToken();
                if (choice == "s" || choice == "S") {
                    cout << "Enter src dst numbers separated by space: ";
                    string line = readLineTrimmed();
                    
                    int a=0,bn=0;
                    if (sscanf(line.c_str(), "%d %d", &a, &bn) == 2) {
                        if (checkValidShift(player.mark, foe.mark, b, a, bn)) {
                            shiftValues(a, bn, b, r);
                            cout << "Shifted.\n";
                            player.paladinCount++;
                            // check win
                            if (checkWin(b, player.mark)) { printTable(r,b); return 1; }
                            if (checkFull(b)) { printTable(r,b); return 0; }
                            turn = 1;
                            continue;
                        } else {
                            cout << "Invalid shift. Doing regular move.\n";
                        }
                    } else {
                        cout << "Bad input. Doing regular move.\n";
                    }
                }
            }
            // Alchemist swap possibility
            if ((player.clas == "Alchemist" || player.clas == "alchemist") && playerSwapAvailable) {
                cout << "You may (m)ove or (s)wap two marks. Choose m/s or press enter for move: ";
                string ch = readSingleToken();
                if (ch == "s" || ch == "S") {
                    cout << "Enter two numbers to swap (e.g. '2 7'): ";
                    string line = readLineTrimmed();
                    int a=0,bn=0;
                    if (sscanf(line.c_str(), "%d %d", &a, &bn) == 2) {
                        if (checkValidSwap(player.mark, foe.mark, b, a, bn)) {
                            swapValues(a, bn, b, r);
                            cout << "Swap performed.\n";
                            
                            player.alchemistCount++;
                            if (checkWin(b, player.mark)) { printTable(r,b); return 1; }
                            if (checkFull(b)) { printTable(r,b); return 0; }
                            turn = 1;
                            continue;
                        } else {
                            cout << "Invalid swap. Doing regular move.\n";
                        }
                    } else {
                        cout << "Bad input. Doing regular move.\n";
                    }
                }
            }

            // normal move
            while (true) {
                cout << "Enter your move (1-9): ";
                string tok = readSingleToken();
                if (tok.size() != 1 || !isdigit(tok[0])) {
                    cout << "Enter a single digit 1-9.\n";
                    continue;
                }
                bool rep = movePlace(tok, player.mark, b);
                if (!rep) break;
               
            }
            
            if (checkWin(b, player.mark)) {
                printTable(r,b);
                cout << player.name << " wins the match!\n";
                if (player.alchemistCount == 0 && (player.clas == "Alchemist" || player.clas == "alchemist")) {
                    player.alchemistCount++;
                }
                if (player.paladinCount == 0 && (player.clas == "Paladin" || player.clas == "paladin")) {
                    player.paladinCount++;
                }
                return 1;
            }
            if (checkFull(b)) {
                printTable(r,b);
                cout << "Match is a draw.\n";
                return 0;
            }
            
            if (player.paladinCount == 0 && (player.clas == "Paladin" || player.clas == "paladin")) {
                player.paladinCount++;
            }
            turn = 1;
        } else {
           
            foeRandomMove(foe, b);
            cout << foe.name << " plays.\n";
            if (checkWin(b, foe.mark)) {
                printTable(r,b);
                cout << foe.name << " wins the match!\n";
                return -1;
            }
            if (checkFull(b)) {
                printTable(r,b);
                cout << "Match is a draw.\n";
                return 0;
            }
            turn = 0;
        }
    }
}

//story, shop and event

void showStats(Player &p) {
    cout << p.name << " | HP: " << p.hp << "/" << p.maxHP << " | ATK: " << p.atk << " | DEF: " << p.def << " | Gold: " << p.gold << "\n";
}

void applyTempleTraining(Player &p, string type) {
    if (type == "earth") {
        cout << "You learn earth techniques. DEF increases by 4.\n";
        p.def += 4;
    } else if (type == "fire") {
        cout << "You learn fire techniques. ATK increases by 5.\n";
        p.atk += 5;
    } else if (type == "water") {
        cout << "You learn healing water techniques. MaxHP +25 and heal 25.\n";
        p.maxHP += 25;
        p.hp += 25;
        if (p.hp > p.maxHP) p.hp = p.maxHP;
    } else if (type == "air") {
        cout << "You learn air techniques. ATK +2, DEF +1.\n";
        p.atk += 2;
        p.def += 1;
    } else if (type == "avatar") {
        cout << "You have become the Avatar! All stats boosted.\n";
        p.maxHP += 50;
        p.hp += 50;
        p.atk += 10;
        p.def += 6;
        if (p.hp > p.maxHP) p.hp = p.maxHP;
    }
}

void showShop(Player &p) {
    cout << "\n--- Simple Shop ---\n";
    cout << "1) Small Potion (+20 HP) - 10 gold\n";
    cout << "2) Dagger (+3 ATK) - 15 gold\n";
    cout << "3) Bracer (+3 DEF) - 15 gold\n";
    cout << "0) Leave shop\n";
    while (true) {
        cout << "Choose item number: ";
        string tok = readSingleToken();
        if (tok.size()==0) continue;
        if (tok == "0") break;
        if (tok == "1") {
            if (p.gold >= 10) { p.gold -= 10; p.hp += 20; if (p.hp > p.maxHP) p.hp = p.maxHP; cout << "Used potion. HP +" << 20 << ".\n"; }
            else cout << "Not enough gold.\n";
        } else if (tok == "2") {
            if (p.gold >= 15) { p.gold -= 15; p.atk += 3; cout << "Bought dagger. ATK +3.\n"; }
            else cout << "Not enough gold.\n";
        } else if (tok == "3") {
            if (p.gold >= 15) { p.gold -= 15; p.def += 3; cout << "Bought bracer. DEF +3.\n"; }
            else cout << "Not enough gold.\n";
        } else {
            cout << "Invalid choice.\n";
        }
        showStats(p);
    }
}

void betweenEvent(Player &p, int idx) {
    cout << "\n--- Between Battles Event ---\n";
    if (idx == 0) {
        cout << "You find a soothing spring. Heal 15 HP.\n";
        p.hp += 15; if (p.hp > p.maxHP) p.hp = p.maxHP;
    } else if (idx == 1) {
        cout << "A small merchant offers goods.\n";
        showShop(p);
    } else if (idx == 2) {
        cout << "You discover a mural and must choose your path.\n";
        cout << "Left (quick path) gives 10 gold. Right (long path) gives +3 ATK and +3 DEF but costs 5 HP.\n";
        while (true) {
            cout << "Choose left or right (l/r): ";
            string ch = readSingleToken();
            if (ch == "l" || ch == "L") { p.gold += 10; cout << "You quickly pass. Gold +10.\n"; break; }
            if (ch == "r" || ch == "R") { p.atk += 3; p.def += 3; p.hp -= 5; if (p.hp < 1) p.hp = 1; cout << "You take the long road. ATK+3 DEF+3 HP-5.\n"; break; }
            cout << "Invalid.\n";
        }
    } else {
        cout << "You find some coins. Gold +20.\n";
        p.gold += 20;
    }
    showStats(p);
}



Foe makeFoe(string id, string name, int hp, int atk, int defn, string mark, string special) {
    Foe f;
    f.id = id; f.name = name; f.maxHP = hp; f.hp = hp; f.atk = atk; f.def = defn; f.mark = mark; f.special = special;
    return f;
}

void runCampaign() {

    Player player;
    cout << "Enter your character's name: ";
    player.name = readLineTrimmed();
    while (player.name.size() == 0) { cout << "Enter non-empty name: "; player.name = readLineTrimmed(); }

    cout << "Choose a class (Paladin or Alchemist): ";
    string cl;
    while (true) {
        cl = readLineTrimmed();
        if (cl == "Paladin" || cl == "paladin") { player.clas = "Paladin"; break; }
        if (cl == "Alchemist" || cl == "alchemist") { player.clas = "Alchemist"; break; }
        cout << "Invalid. Choose Paladin or Alchemist: ";
    }

    if (player.clas == "Paladin") { player.maxHP = 130; player.hp = 130; player.atk = 14; player.def = 12; }
    else { player.maxHP = 110; player.hp = 110; player.atk = 12; player.def = 9; }
    player.gold = 20;
    player.paladinCount = 0;
    player.alchemistCount = 0;

    cout << "Choose your single-character mark (non-digit): ";
    while (true) {
        string m = readSingleToken();
        if (m.size() == 1 && !isdigit(m[0])) { player.mark = m; break; }
        cout << "Invalid mark. Try again: ";
    }

    cout << "\nWelcome " << player.name << " the " << player.clas << "!\n";
    showStats(player);
    cout << "Your mark: " << player.mark << "\n";

    
    vector<Foe> foes;
    foes.push_back(makeFoe("earth_1", "Young Earth Bender", 40, 8, 4, "E", "Stone Shield"));
    foes.push_back(makeFoe("fire_1", "Fire Criminal", 50, 12, 3, "F", "Molten Burst"));
    foes.push_back(makeFoe("water_1", "Greedy Water Bender", 55, 10, 5, "W", "Tide Heal"));
    foes.push_back(makeFoe("air_1", "Air Trickster", 45, 9, 3, "A", "Gale Push"));
    // final
    foes.push_back(makeFoe("avatar", "The Corrupt Avatar", 120, 20, 8, "V", "AvatarFlare")); // has multiple later

    vector<string> temples;
    temples.push_back("You enter the Mossy Hollow Temple. Murals tell of the moles, the first earth benders.");
    temples.push_back("You arrive at Ashen Outpost. Charred murals honor dragons of old.");
    temples.push_back("You push through Moonlit Basin. Koi and moon spirits whisper of the tides.");
    temples.push_back("You climb to Windspire. Sky bison carvings watch the sky.");
    temples.push_back("You approach the Hall of Balance. The final test awaits.");

    int eventIndex = 0;

    for (int i = 0; i < (int)foes.size(); ++i) {
        cout << "\n--- Battle " << (i+1) << " ---\n";
        cout << "You encounter " << foes[i].name << "!\n";
        cout << temples[i] << "\n";
        cout << foes[i].name << " | HP: " << foes[i].hp << " ATK: " << foes[i].atk << " DEF: " << foes[i].def << "\n";
        
        if (foes[i].mark == player.mark) {
            if (player.mark != "O") foes[i].mark = "O"; else foes[i].mark = "X";
        }

      
        while (player.hp > 0 && foes[i].hp > 0) {
            // show status
            cout << "\nStatus:\n";
            showStats(player);
            cout << foes[i].name << " | HP: " << foes[i].hp << "/" << foes[i].maxHP << " ATK: " << foes[i].atk << " DEF: " << foes[i].def << "\n";

            cout << "Visit a quick vendor (y/n)? ";
            string v = readSingleToken();
            if (v == "y" || v == "Y") showShop(player);

            // play a match
            int res = playMatch(player, foes[i]);

            if (res == 1) {
                // player won match -> damage ememy
                int dmg = computeDamage(player.atk, foes[i].def);
                cout << "You won the match. You deal " << dmg << " damage to " << foes[i].name << ".\n";
                foes[i].hp -= dmg;
                // gold reward
                int goldGain = randBetween(5,15);
                player.gold += goldGain;
                cout << "You gained " << goldGain << " gold.\n";
            } else if (res == -1) {
                
                applyFoeSpecial(foes[i], player);
                int dmg = computeDamage(foes[i].atk, player.def);
                cout << foes[i].name << " won the match and deals " << dmg << " damage to you.\n";
                player.hp -= dmg;
            } else {
                cout << "A draw. No immediate damage.\n";
            }

            if (foes[i].hp <= 0) {
                cout << "You defeated " << foes[i].name << "!\n";
                int loot = randBetween(20,40);
                cout << "You collect " << loot << " gold from the fallen.\n";
                player.gold += loot;
                // go to temple training
                if (i == 0) applyTempleTraining(player, "earth");
                else if (i == 1) applyTempleTraining(player, "fire");
                else if (i == 2) applyTempleTraining(player, "water");
                else if (i == 3) applyTempleTraining(player, "air");
                break;
            }
            if (player.hp <= 0) {
                cout << "You have been defeated. Your campaign ends and will restart.\n";
                return;
            }
            
            cout << "Next match in this encounter starting...\n";
        }
        if (i < (int)foes.size() - 1) {
            betweenEvent(player, eventIndex % 4);
            eventIndex++;
            
            if (i == 1) {
                cout << "\nA sage offers you a choice: (a) learning scar (+2 ATK, -3 HP) or (b) prayer (+15 HP). Choose a/b: ";
                while (true) {
                    string c = readSingleToken();
                    if (c == "a" || c == "A") { player.atk += 2; player.hp -= 3; if (player.hp < 1) player.hp = 1; cout << "You accept the scar.\n"; break; }
                    if (c == "b" || c == "B") { player.hp += 15; if (player.hp > player.maxHP) player.hp = player.maxHP; cout << "You take prayer.\n"; break; }
                    cout << "Invalid. Choose a or b: ";
                }
            }
        } else {
          
            cout << "\nYou steel yourself for the final battle...\n";
            foes[i].special = "AvatarFlare";
        }
    }
    cout << "\nYou have cleared all battles and become the Avatar. Congratulations!\n";
    applyTempleTraining(player, "avatar");
    showStats(player);
}

//main

int main() {
    srand((unsigned int)time(NULL));
    cout << "Welcome to Battle Tic-Tac-Toe Campaign (simple style)\n";
    while (true) {
        runCampaign();
        cout << "\nPlay again? (y/n): ";
        string r = readSingleToken();
        if (!(r == "y" || r == "Y")) break;
    }
    cout << "Thanks for playing!\n";
    return 0;
}
