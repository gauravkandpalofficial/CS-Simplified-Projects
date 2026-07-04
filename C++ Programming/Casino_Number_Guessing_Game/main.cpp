#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const int STARTING_BALANCE = 1000;
const int MIN_NUMBER = 1;
const int MAX_NUMBER = 10;
const string USER_FILE = "players.txt";

struct Player {
    string username;
    string password;
    int balance;
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& message) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

vector<Player> loadPlayers() {
    vector<Player> players;
    ifstream file(USER_FILE);

    Player player;
    while (file >> player.username >> player.password >> player.balance) {
        players.push_back(player);
    }

    return players;
}

void savePlayers(const vector<Player>& players) {
    ofstream file(USER_FILE);

    for (const Player& player : players) {
        file << player.username << " " << player.password << " " << player.balance << '\n';
    }
}

int findPlayerIndex(const vector<Player>& players, const string& username) {
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        if (players[i].username == username) {
            return i;
        }
    }

    return -1;
}

int registerPlayer(vector<Player>& players) {
    string username;
    string password;

    cout << "\n--- Register ---\n";

    while (true) {
        cout << "Create username: ";
        cin >> username;

        if (findPlayerIndex(players, username) != -1) {
            cout << "Username already exists. Try another username.\n";
        } else {
            break;
        }
    }

    cout << "Create password: ";
    cin >> password;

    Player newPlayer;
    newPlayer.username = username;
    newPlayer.password = password;
    newPlayer.balance = STARTING_BALANCE;

    players.push_back(newPlayer);
    savePlayers(players);

      cout << "Registration successful! Rs." << STARTING_BALANCE
         << " has been added to your wallet.\n";

    return static_cast<int>(players.size()) - 1;
}

int loginPlayer(const vector<Player>& players) {
    string username;
    string password;

    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    int index = findPlayerIndex(players, username);

    if (index == -1 || players[index].password != password) {
        cout << "Invalid username or password.\n";
        return -1;
    }

    cout << "Login successful. Welcome, " << players[index].username << "!\n";
    return index;
}

int chooseAccount(vector<Player>& players, const string& playerLabel) {
    while (true) {
        cout << "\n" << playerLabel << " Account Menu\n";
        cout << "1. Register\n";
        cout << "2. Login\n";

        int choice = readInt("Enter your choice: ");

        if (choice == 1) {
            return registerPlayer(players);
        } else if (choice == 2) {
            int index = loginPlayer(players);
            if (index != -1) {
                return index;
            }
        } else {
            cout << "Invalid choice. Please select 1 or 2.\n";
        }
    }
}

int getCommonBet(const Player& p1, const Player& p2) {
    int maxBet = min(p1.balance, p2.balance);

    while (true) {
        cout << "\nBoth players must bet the same amount.\n";
        cout << "Maximum possible bet: Rs." << maxBet << '\n';

        int bet = readInt("Enter common bet amount: Rs.");

        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n";
        } else if (bet > maxBet) {
            cout << "Both players must have enough money for this bet.\n";
        } else {
            return bet;
        }
    }
}

int getGuess(const Player& player) {
    while (true) {
        int guess = readInt(player.username + ", guess a number from 1 to 10: ");

        if (guess < MIN_NUMBER || guess > MAX_NUMBER) {
            cout << "Invalid guess. Number must be between "
                 << MIN_NUMBER << " and " << MAX_NUMBER << ".\n";
        } else {
            return guess;
        }
    }
}

void showBalances(const Player& p1, const Player& p2) {
    cout << "\nCurrent Wallet Balance\n";
    cout << p1.username << ": Rs." << p1.balance << '\n';
    cout << p2.username << ": Rs." << p2.balance << '\n';
}

void playGame(vector<Player>& players, int p1Index, int p2Index) {
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        Player& p1 = players[p1Index];
        Player& p2 = players[p2Index];

        if (p1.balance <= 0 || p2.balance <= 0) {
            break;
        }

        showBalances(p1, p2);

        int bet = getCommonBet(p1, p2);
        int guess1 = getGuess(p1);
        int guess2 = getGuess(p2);
        int winningNumber = rand() % MAX_NUMBER + MIN_NUMBER;

        cout << "\nWinning number: " << winningNumber << '\n';

        bool p1Wins = guess1 == winningNumber;
        bool p2Wins = guess2 == winningNumber;

        if (p1Wins && p2Wins) {
            cout << "Both players guessed correctly. No money is transferred.\n";
        } else if (p1Wins) {
            p1.balance += bet;
            p2.balance -= bet;
            cout << p1.username << " wins Rs." << bet << " from "
                 << p2.username << "!\n";
        } else if (p2Wins) {
            p2.balance += bet;
            p1.balance -= bet;
            cout << p2.username << " wins Rs." << bet << " from "
                 << p1.username << "!\n";
        } else {
            p1.balance -= bet;
            p2.balance -= bet;
            cout << "No one guessed correctly. Both players lose Rs."
                 << bet << " to the casino.\n";
        }

        savePlayers(players);
        showBalances(p1, p2);

        if (p1.balance <= 0 || p2.balance <= 0) {
            break;
        }

        cout << "\nDo you want to play another round? (y/n): ";
        cin >> choice;
        clearInput();
    }

    cout << "\n===== Game Over =====\n";

    Player& p1 = players[p1Index];
    Player& p2 = players[p2Index];

    if (p1.balance <= 0 && p2.balance <= 0) {
        cout << "Both players have run out of money.\n";
    } else if (p1.balance <= 0) {
        cout << p1.username << " has run out of money.\n";
        cout << p2.username << " wins the game!\n";
    } else if (p2.balance <= 0) {
        cout << p2.username << " has run out of money.\n";
        cout << p1.username << " wins the game!\n";
    } else {
        cout << "Players chose to walk away.\n";
    }

    savePlayers(players);
    showBalances(p1, p2);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Player> players = loadPlayers();

    cout << "============================================\n";
    cout << "   Two Player Casino Number Guessing Game\n";
    cout << "============================================\n";
    cout << "Every new user gets Rs." << STARTING_BALANCE << " in their wallet.\n";

    int p1Index = chooseAccount(players, "Player 1");
    int p2Index;

    while (true) {
        p2Index = chooseAccount(players, "Player 2");

        if (p2Index == p1Index) {
            cout << "Player 2 cannot use the same account as Player 1.\n";
        } else {
            break;
        }
    }

    if (players[p1Index].balance <= 0 || players[p2Index].balance <= 0) {
        cout << "\nBoth players must have money in their wallet to start the game.\n";
        return 0;
    }

    playGame(players, p1Index, p2Index);

    return 0;
}