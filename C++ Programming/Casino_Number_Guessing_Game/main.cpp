#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Player {
    string name;
    int balance;
};

int getValidBet(Player player) {
    int bet;

    do {
        cout << player.name << ", enter your bet: ";
        cin >> bet;

        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n";
        } else if (bet > player.balance) {
            cout << "You cannot bet more than your balance.\n";
        }

    } while (bet <= 0 || bet > player.balance);

    return bet;
}

int getGuess(Player player) {
    int guess;

    do {
        cout << player.name << ", guess a number between 1 and 10: ";
        cin >> guess;

        if (guess < 1 || guess > 10) {
            cout << "Invalid guess. Choose between 1 and 10.\n";
        }

    } while (guess < 1 || guess > 10);

    return guess;
}

int main() {
    srand(time(0));

    Player p1, p2;

    cout << "===== Two Player Casino Number Guessing Game =====\n\n";

    cout << "Enter Player 1 name: ";
    cin >> p1.name;

    cout << "Enter Player 1 initial balance: ";
    cin >> p1.balance;

    cout << "\nEnter Player 2 name: ";
    cin >> p2.name;

    cout << "Enter Player 2 initial balance: ";
    cin >> p2.balance;

    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        if (p1.balance <= 0 || p2.balance <= 0) {
            break;
        }

        cout << "\n----------------------------------\n";
        cout << p1.name << " Balance: " << p1.balance << endl;
        cout << p2.name << " Balance: " << p2.balance << endl;
        cout << "----------------------------------\n";

        int bet1 = getValidBet(p1);
        int bet2 = getValidBet(p2);

        int guess1 = getGuess(p1);
        int guess2 = getGuess(p2);

        int winningNumber = rand() % 10 + 1;

        cout << "\nWinning number was: " << winningNumber << endl;

        bool p1Wins = guess1 == winningNumber;
        bool p2Wins = guess2 == winningNumber;

        if (p1Wins && p2Wins) {
            cout << "Both players guessed correctly! No money is lost.\n";
        } 
        else if (p1Wins) {
            cout << p1.name << " wins this round!\n";
            p1.balance += bet2;
            p2.balance -= bet2;
        } 
        else if (p2Wins) {
            cout << p2.name << " wins this round!\n";
            p2.balance += bet1;
            p1.balance -= bet1;
        } 
        else {
            cout << "No one guessed correctly. Both players lose their bets.\n";
            p1.balance -= bet1;
            p2.balance -= bet2;
        }

        cout << "\nUpdated Balances:\n";
        cout << p1.name << ": " << p1.balance << endl;
        cout << p2.name << ": " << p2.balance << endl;

        if (p1.balance <= 0 || p2.balance <= 0) {
            break;
        }

        cout << "\nDo you want to play another round? (y/n): ";
        cin >> choice;
    }

    cout << "\n===== Game Over =====\n";

    if (p1.balance <= 0) {
        cout << p1.name << " has run out of money.\n";
        cout << p2.name << " wins the game!\n";
    } 
    else if (p2.balance <= 0) {
        cout << p2.name << " has run out of money.\n";
        cout << p1.name << " wins the game!\n";
    } 
    else {
        cout << "Players chose to walk away.\n";
    }

    cout << "\nFinal Balances:\n";
    cout << p1.name << ": " << p1.balance << endl;
    cout << p2.name << ": " << p2.balance << endl;

    return 0;
}