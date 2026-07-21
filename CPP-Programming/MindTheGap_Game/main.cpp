#include <algorithm>
#include <chrono>
#include <cctype>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std;

mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));

void clearScreen() {
    // `cls` works in Command Prompt, PowerShell, and most IDE console windows.
    // It is more reliable than ANSI escape codes on Windows.
#ifdef _WIN32
    system("cls");
#else
    cout << "\x1B[2J\x1B[H";
#endif
}

void waitForEnter(const string& prompt) {
    cout << prompt;
    string unused;
    getline(cin, unused);
}

template <typename T>
vector<T> randomItems(vector<T> pool, int count) {
    shuffle(pool.begin(), pool.end(), rng);
    pool.resize(count);
    return pool;
}

template <typename T>
string join(const vector<T>& items) {
    string result;
    for (size_t i = 0; i < items.size(); ++i) {
        if (i != 0) result += ' ';
        result += items[i];
    }
    return result;
}

string normalize(string text) {
    string result;
    for (unsigned char ch : text) {
        if (!isspace(ch)) result += static_cast<char>(toupper(ch));
    }
    return result;
}

bool levelOneQuestion(int question) {
    vector<string> numbers = randomItems(vector<string>{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}, 5);
    vector<int> positions{0, 1, 2, 3, 4};
    shuffle(positions.begin(), positions.end(), rng);
    positions.resize(2);
    sort(positions.begin(), positions.end());

    clearScreen();
    cout << "LEVEL 1 - Question " << question << "/15\n\nRemember these five numbers:\n\n"
         << join(numbers) << "\n";
    waitForEnter("\nPress Enter when you are ready to hide two numbers... ");
    clearScreen();

    vector<string> answer;
    cout << "\nWhich two numbers disappeared?\n\n";
    for (int i = 0; i < 5; ++i) {
        if (find(positions.begin(), positions.end(), i) != positions.end()) {
            cout << "_ ";
            answer.push_back(numbers[i]);
        } else {
            cout << numbers[i] << ' ';
        }
    }
    cout << "\n\nEnter the hidden numbers in their displayed order (example: 3 7): ";
    string response;
    getline(cin, response);
    return normalize(response) == normalize(join(answer));
}

bool levelTwoQuestion(int question) {
    vector<string> letters = randomItems(vector<string>{"A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}, 5);
    vector<int> shownPositions{0, 1, 2, 3, 4};
    shuffle(shownPositions.begin(), shownPositions.end(), rng);
    shownPositions.resize(2);
    sort(shownPositions.begin(), shownPositions.end());

    clearScreen();
    cout << "LEVEL 2 - Question " << question << "/12\n\nRemember these characters:\n\n"
         << join(letters) << "\n";
    waitForEnter("\nPress Enter to leave only two characters visible... ");
    clearScreen();

    vector<string> answer;
    cout << "\nEnter the two characters that remain:\n\n";
    for (int i = 0; i < 5; ++i) {
        if (find(shownPositions.begin(), shownPositions.end(), i) != shownPositions.end()) {
            cout << letters[i] << ' ';
            answer.push_back(letters[i]);
        } else {
            cout << "_ ";
        }
    }
    cout << "\n\nEnter them in their displayed order (example: A K): ";
    string response;
    getline(cin, response);
    return normalize(response) == normalize(join(answer));
}

bool levelThreeQuestion(int question) {
    vector<string> pool{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                             "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    vector<string> items = randomItems(pool, 6);
    uniform_int_distribution<int> choosePosition(0, 5);
    int keptPosition = choosePosition(rng);

    clearScreen();
    cout << "LEVEL 3 - Question " << question << "/8\n\nRemember this mixed sequence:\n\n"
         << join(items) << "\n";
    waitForEnter("\nPress Enter to leave only one item visible... ");
    clearScreen();

    cout << "\nThe remaining item is: ";
    for (int i = 0; i < 6; ++i) {
        cout << (i == keptPosition ? items[i] : "_") << ' ';
    }
    cout << "\n\nType the item that remains: ";
    string response;
    getline(cin, response);
    return normalize(response) == normalize(items[keptPosition]);
}

int main() {
    clearScreen();
    cout << "=================================\n"
         << "        MIND THE GAP \n"
         << "=================================\n\n";
    cout << "What is your name? ";
    string playerName;
    getline(cin, playerName);
    if (playerName.empty()) playerName = "Player";

    clearScreen();
    cout << "Welcome, " << playerName << "!\n\n"
         << "HOW TO PLAY\n"
         << "1. Look carefully at the sequence shown on the screen.\n"
         << "2. Press Enter when you are ready. The screen will clear.\n"
         << "3. Type the requested hidden or remaining items in their displayed order.\n"
         << "4. Every correct answer earns 10 points.\n\n"
         << "LEVELS\n"
         << "Level 1: 15 number questions. Score 100 points (10 correct) to unlock Level 2.\n"
         << "Level 2: 12 character questions. Score 100 points (10 correct) to unlock Level 3.\n"
         << "Level 3: 8 mixed number and character questions.\n\n";
    waitForEnter("Press Enter to start Level 1... ");

    int score1 = 0;
    for (int i = 1; i <= 15; ++i) {
        if (levelOneQuestion(i)) { score1 += 10; cout << "Correct! +10 points"; }
        else cout << "Not quite.";
        cout << "  Level 1 score: " << score1 << " points\n";
        waitForEnter("Press Enter for the next question... ");
    }
    clearScreen();
    cout << "LEVEL 1 COMPLETE, " << playerName << "!\n"
         << "Your Level 1 score: " << score1 << " points.\n";
    if (score1 < 100) {
        cout << "You need 100 points to unlock Level 2. Better luck next time!\n";
        return 0;
    }
    cout << "Great job! Level 2 is unlocked.\n";
    waitForEnter("Press Enter to begin Level 2... ");

    int score2 = 0;
    for (int i = 1; i <= 12; ++i) {
        if (levelTwoQuestion(i)) { score2 += 10; cout << "Correct! +10 points"; }
        else cout << "Not quite.";
        cout << "  Level 2 score: " << score2 << " points\n";
        waitForEnter("Press Enter for the next question... ");
    }
    clearScreen();
    cout << "LEVEL 2 COMPLETE, " << playerName << "!\n"
         << "Your Level 2 score: " << score2 << " points.\n";
    if (score2 < 100) {
        cout << "You need 100 points to unlock Level 3. Better luck next time!\n";
        return 0;
    }
    cout << "Excellent! Level 3 is unlocked.\n";
    waitForEnter("Press Enter to begin Level 3... ");

    int score3 = 0;
    for (int i = 1; i <= 8; ++i) {
        if (levelThreeQuestion(i)) { score3 += 10; cout << "Correct! +10 points"; }
        else cout << "Not quite.";
        cout << "  Level 3 score: " << score3 << " points\n";
        waitForEnter("Press Enter for the next question... ");
    }
    clearScreen();
    cout << "=================================\n"
         << "          GAME COMPLETE\n"
         << "=================================\n\n"
         << "Well played, " << playerName << "!\n"
         << "Level 1 score: " << score1 << " points\n"
         << "Level 2 score: " << score2 << " points\n"
         << "Level 3 score: " << score3 << " points\n"
         << "Total score: " << score1 + score2 + score3 << " points\n";
}
