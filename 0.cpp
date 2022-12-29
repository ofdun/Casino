#include <iostream>
#include <stdlib.h>
#include <limits>
#include <random>
#include <vector>
#include <time.h>
#include <windows.h>

using namespace std;

// SLOT MACHINE
bool flag = false;
int lines;
const int MAX_LINES = 3;
int balance = 0;
string ending;
bool welcomeToCasino = true;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int deposit(int blnc)
{
    int new_balance;
    int more_money;
    if (flag == true)
    {
        cout << "\nERROR! Enter the valid number!\n";
    }
    cout << "\nHow much money would You like to deposit? (Your current balance is: $" + to_string(blnc) + ") $";
    cin >> more_money;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    new_balance = blnc + more_money;
    flag = true;
    return new_balance;
}

int selectNumberOfLines(int balance)
{
    int lines;
    cout << "\nEnter the number of lines You would like to play(1-" + to_string(MAX_LINES) + ")? ";
    cin >> lines;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (lines < 1 or lines > MAX_LINES)
    {
        cout << "\nERROR! Enter the valid number of lines(1-" + to_string(MAX_LINES) + ")\n ";
        return selectNumberOfLines(balance);
    }
    else
    {
        if (balance < lines)
        {
            int answer;
            cout << "\nERROR! You can not afford it!\n";
            cout << "\nWould You like to select less lines(0/1)? ";
            cin >> answer;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (answer == 0)
            {
                cout << "\nKill yourself right now! Do it bastard!\n";
                return 0;
            }
            else
            {
                if (answer == 1)
                {
                    return selectNumberOfLines(balance);
                }
                else
                {
                    cout << "\nYou are so fucking dumb you should kill yourself right now\n";
                    deposit(balance);
                    return 0;
                }
            }
        }
        else
        {
            return lines;
        }
    }
}

int selectBetToEachLine(int lines, int balance)
{
    cout << "\nHow much would You like to bet on each line? (Your current balance is $" + to_string(balance) + ") $";
    int bet = 0;
    cin >> bet;
    if (bet * lines > balance)
    {
        cout << "\nYou don't have enough money!" << endl;
        flag = false;
        return 0;
    }
    else
    {
        return bet;
    }
}

int getRandomLetter()
{
    srand(time(NULL));
    int randomNumber = rand() % 4;
    return randomNumber;
    // cout << randomNumber;
    // return to_string(randomNumber);
}

string getChars()
{
    string line = "";
    vector<string> letters;
    letters.resize(4);

    int index = 0;
    for (int j = 65; j < 69; j++)
    {
        char c = j;
        letters[index] = c;
        index++;
    }

    // vector<string> randomRow;
    // randomRow.resize(3);

    for (int i = 0; i < 3; i++)
    {
        int randomNumber = getRandomLetter();
        Sleep(500);
        line = line + letters[randomNumber];
    }

    return line;
}

int throwRow(int lines, int bet)
{
    string line = getChars();
    if (line[0] == line[1] and line[1] == line[2])
    {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\t\t" + line + "\tWIN - $" + to_string(bet * 3) << endl;
        return 1;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\t\t" + line + "\tLOST - $" + to_string(bet) << endl;
        return 0;
    }
}

int changeBalance(int bet, int win)
{
    if (win == 0)
        balance = balance - bet;
    else
        balance = balance + (bet * 2);
}

int main()
{
    if (welcomeToCasino == true)
    {
        SetConsoleTextAttribute(hConsole, 11);
        Sleep(300);
        cout << "\nWelcome to my own Casino! ( originally designed by ofdun )\n";
        welcomeToCasino = false;
        SetConsoleTextAttribute(hConsole, 7);
    }
    while (true)
    {
        while (balance <= 0)
        {
            balance = deposit(0);
        }
        lines = selectNumberOfLines(balance);
        // cout << "lines - " + to_string(lines) << ", balance - $" + to_string(balance);
        int bet = selectBetToEachLine(lines, balance);
        if (bet == 0)
        {
            cout << "\nDeposite more money you bastardo!\n";
            flag = false;
            balance = deposit(balance);
            return main();
        }
        else
        {
            int win;
            cout << "\n\t\tROWS:" << endl;
            if (lines == 1)
            {
                win = throwRow(lines, bet);
                changeBalance(bet, win);
            }
            if (lines == 2)
            {
                for (int i = 1; i < 3; i++)
                {
                    win = throwRow(lines, bet);
                    changeBalance(bet, win);
                }
            }
            if (lines == 3)
            {
                for (int i = 1; i < 4; i++)
                {
                    win = throwRow(lines, bet);
                    changeBalance(bet, win);
                }
            }
            SetConsoleTextAttribute(hConsole, 0);
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\nYour balance is $" + to_string(balance) << endl;
        cout << "\nPress Q if You want to quit Kwazino" << endl;
        cin >> ending;
        if (ending == "q" or ending == "Q")
        {
            return 0;
        }
        cout << "\nDo you want to deposite more money? (Y/N) " << endl;
        string response;
        cin >> response;
        if (response == "Y" or response == "y")
        {
            flag = false;
            balance = deposit(balance);
            return main();
        }
        else
        {
            return main();
        }
    }
}