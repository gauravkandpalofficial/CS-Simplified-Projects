#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define EASY_COUNT 15
#define MEDIUM_COUNT 10
#define HARD_COUNT 5
#define MAX_HINTS 5

typedef struct {
    char scrambled[30];
    char answer[30];
    char hint[150];
} Word;

void toLowerCase(char text[]) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

void removeNewline(char text[]) {
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
}

int playLevel(Word words[], int count, char levelName[], int *hintsLeft) {
    int i, levelScore = 0;
    char input[50];

    printf("\n====================================\n");
    printf("%s\n", levelName);
    printf("====================================\n");

    for (i = 0; i < count; i++) {
        printf("\nQuestion %d of %d\n", i + 1, count);
        printf("Scrambled word: %s\n", words[i].scrambled);
        printf("Hints left: %d\n", *hintsLeft);

        while (1) {
            printf("Enter answer or type 'hint': ");
            fgets(input, sizeof(input), stdin);
            removeNewline(input);
            toLowerCase(input);

            if (strcmp(input, "hint") == 0) {
                if (*hintsLeft > 0) {
                    printf("Hint: %s\n", words[i].hint);
                    (*hintsLeft)--;
                    printf("Hints left: %d\n", *hintsLeft);
                } else {
                    printf("No hints left!\n");
                }
            } else {
                if (strcmp(input, words[i].answer) == 0) {
                    printf("Correct answer!\n");
                    levelScore += 10;
                } else {
                    printf("Wrong answer! Correct answer is: %s\n", words[i].answer);
                }
                break;
            }
        }
    }

    printf("\n%s completed!\n", levelName);
    printf("Level score: %d out of %d\n", levelScore, count * 10);

    return levelScore;
}

int main() {
    Word easy[EASY_COUNT] = {
        {"elppa", "apple", "A red or green fruit that keeps doctors away."},
        {"koob", "book", "You read this to gain knowledge or enjoy stories."},
        {"tac", "cat", "A small pet animal that says meow."},
        {"god", "dog", "A loyal pet animal that barks."},
        {"nep", "pen", "You use this to write on paper."},
        {"nus", "sun", "It gives us light during the day."},
        {"llab", "ball", "A round object used in many games."},
        {"hsif", "fish", "An animal that lives in water."},
        {"eert", "tree", "It has roots, branches, and leaves."},
        {"rac", "car", "A vehicle used for travelling on roads."},
        {"klim", "milk", "A white drink that comes from cows."},
        {"rihc", "chair", "You sit on this."},
        {"elbat", "table", "You keep things on it while studying or eating."},
        {"retaw", "water", "A liquid that humans need to live."},
        {"drib", "bird", "An animal with wings that can usually fly."}
    };

    Word medium[MEDIUM_COUNT] = {
        {"retupmoc", "computer", "An electronic machine used for processing data."},
        {"litsopah", "hospital", "A place where sick people are treated."},
        {"rehcaet", "teacher", "A person who helps students learn."},
        {"yrarbil", "library", "A place where many books are kept."},
        {"nomle", "lemon", "A sour yellow fruit."},
        {"ragden", "garden", "A place where flowers and plants grow."},
        {"tekcirc", "cricket", "A popular bat-and-ball game."},
        {"locosh", "school", "A place where students study."},
        {"nekcihc", "chicken", "A bird often raised on farms."},
        {"tekram", "market", "A place where people buy and sell goods."}
    };

    Word hard[HARD_COUNT] = {
        {"margorp", "program", "A set of instructions written for a computer."},
        {"ecneics", "science", "The study of nature, experiments, and facts."},
        {"yrotsih", "history", "The study of past events."},
        {"noitacude", "education", "The process of gaining knowledge and skills."},
        {"ygolonhcet", "technology", "The use of science to create useful machines and systems."}
    };

    char playerName[50], choice;
    int hintsLeft, totalScore, maximumScore;
    int easyScore, mediumScore, hardScore;
    int easyCorrect, mediumCorrect;

    do {
        hintsLeft = MAX_HINTS;
        totalScore = 0;
        maximumScore = (EASY_COUNT + MEDIUM_COUNT + HARD_COUNT) * 10;

        printf("\n\n====================================\n");
        printf("        WORD SCRAMBLE GAME\n");
        printf("====================================\n");
        printf("\nEnter your name: ");
        fgets(playerName, sizeof(playerName), stdin);
        removeNewline(playerName);

        printf("\nWelcome, %s!\n", playerName);
        printf("Rules:\n");
        printf("1. Arrange the scrambled word correctly.\n");
        printf("2. Type 'hint' if you need help.\n");
        printf("3. You have only %d hints for the whole game.\n", MAX_HINTS);
        printf("4. Each correct answer gives 10 points.\n");
        printf("5. You need at least 10 correct answers in Level 1 to unlock Level 2.\n");
        printf("6. You need at least 5 correct answers in Level 2 to unlock Level 3.\n");

        easyScore = playLevel(easy, EASY_COUNT, "LEVEL 1 - EASY", &hintsLeft);
        totalScore += easyScore;
        easyCorrect = easyScore / 10;

        if (easyCorrect >= 10) {
            printf("\nCongratulations! You unlocked Level 2.\n");
            mediumScore = playLevel(medium, MEDIUM_COUNT, "LEVEL 2 - MEDIUM", &hintsLeft);
            totalScore += mediumScore;
            mediumCorrect = mediumScore / 10;

            if (mediumCorrect >= 5) {
                printf("\nCongratulations! You unlocked Level 3.\n");
                hardScore = playLevel(hard, HARD_COUNT, "LEVEL 3 - HARD", &hintsLeft);
                totalScore += hardScore;
            } else {
                printf("\nYou answered only %d question(s) correctly in Level 2.\n", mediumCorrect);
                printf("You need at least 5 correct answers to unlock Level 3.\n");
                printf("Level 3 is locked. Game ends here.\n");
            }
        } else {
            printf("\nYou answered only %d question(s) correctly in Level 1.\n", easyCorrect);
            printf("You need at least 10 correct answers to unlock Level 2.\n");
            printf("Level 2 and Level 3 are locked. Game ends here.\n");
        }

        printf("\n====================================\n");
        printf("             GAME OVER\n");
        printf("====================================\n");
        printf("Player name: %s\n", playerName);
        printf("Final score: %d out of %d\n", totalScore, maximumScore);
        printf("Hints unused: %d\n", hintsLeft);

        if (totalScore >= 250) {
            printf("Performance: Excellent!\n");
        } else if (totalScore >= 180) {
            printf("Performance: Very good!\n");
        } else if (totalScore >= 100) {
            printf("Performance: Good try!\n");
        } else {
            printf("Performance: Keep practicing!\n");
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        choice = (char)tolower((unsigned char)choice);

    } while (choice == 'y');

    printf("\nThank you for playing!\n");

    return 0;
}