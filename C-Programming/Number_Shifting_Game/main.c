#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void createMatrix(int arr[][4], int size) {
    int numbers[15], i, j;
    for (i = 0; i < size * size - 1; i++) {
        numbers[i] = i + 1;
    }

    srand(time(NULL));
    for (i = size * size - 2; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    int k = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            arr[i][j] = (k < size * size - 1) ? numbers[k++] : 0;
        }
    }
}

void showMatrix(int arr[][4], int size) {
    int i, j;
    printf("-----------------\n");
    for (i = 0; i < size; i++) {
        printf("| ");
        for (j = 0; j < size; j++) {
            if (arr[i][j] != 0) printf("%-2d | ", arr[i][j]);
            else printf("   | ");
        }
        printf("\n");
    }
    printf("-----------------\n");
}

int winner(int arr[][4], int size) {
    int i, j, k = 1;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++, k++) {
            if (arr[i][j] != k && k != size * size) return 0;
        }
    }
    return 1;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int readEnteredKey() {
    char c = getch();
    if (c == -32) c = getch();
    return c;
}

int shiftUp(int arr[][4], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j] == 0) break;
        }
        if (j < size) break;
    }
    if (i == size - 1) return 0;
    swap(&arr[i][j], &arr[i + 1][j]);
    return 1;
}

int shiftDown(int arr[][4], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j] == 0) break;
        }
        if (j < size) break;
    }
    if (i == 0) return 0;
    swap(&arr[i][j], &arr[i - 1][j]);
    return 1;
}

int shiftRight(int arr[][4], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j] == 0) break;
        }
        if (j < size) break;
    }
    if (j == 0) return 0;
    swap(&arr[i][j], &arr[i][j - 1]);
    return 1;
}

int shiftLeft(int arr[][4], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j] == 0) break;
        }
        if (j < size) break;
    }
    if (j == size - 1) return 0;
    swap(&arr[i][j], &arr[i][j + 1]);
    return 1;
}

void gameRule(int size) {
    printf("                 RULE OF THIS GAME                 \n");
    printf("\n1. Use arrow keys to move the numbers.\n");
    printf("2. Arrange numbers from 1 to %d in order to win.\n\n", size * size - 1);
    printf("   Winning state:\n");
    printf("-----------------\n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            printf("| %-2d ", (i - 1) * size + j);
        }
        printf("|\n");
    }
    printf("-----------------\n\n");
    printf("Press any key to start...\n");
    readEnteredKey();
}

int main() {
    int arr[4][4];
    char name[20];
    int size;

    printf("Enter Your Name: ");
    scanf("%s", name);

    printf("Choose matrix size (3 for 3x3, 4 for 4x4): ");
    scanf("%d", &size);

    if (size < 3 || size > 4) {
        printf("Invalid size! Choose either 3 or 4.\n");
        return 0;
    }

    while (1) {
        createMatrix(arr, size);
        gameRule(size);

        while (!winner(arr, size)) {
            system("cls");
            printf("\n%s, here is your puzzle:\n\n", name);
            showMatrix(arr, size);

            int key = readEnteredKey();
            switch (key) {
                case 69: case 101: // E or e
                    printf("\nThanks for playing!\n");
                    exit(0);
                case 72: // Arrow up
                    shiftUp(arr, size);
                    break;
                case 80: // Arrow down
                    shiftDown(arr, size);
                    break;
                case 77: // Arrow right
                    shiftRight(arr, size);
                    break;
                case 75: // Arrow left
                    shiftLeft(arr, size);
                    break;
                default:
                    printf("\nInvalid move!\n");
            }
        }

        printf("\nCongratulations, You Won!\n");
        printf("Play again? (y/n): ");
        fflush(stdin);
        char check = getchar();
        if (check != 'y' && check != 'Y') break;
    }
    return 0;
}
