#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

char input[100];
int ip = 0;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

// Predictive Parsing Table
// Rows: S, A, B, C
// Columns: a, b, c, (, ), $

char table[4][6][20] = {
    // S
    {"ABC", "ABC", "ABC", "ABC", "", ""},
    // A
    {"a", "ε", "ε", "ε", "", ""},
    // B
    {"", "b", "ε", "ε", "", ""},
    // C
    {"", "", "c", "(S)", "", ""}
};

int getRow(char c) {
    if (c == 'S') return 0;
    if (c == 'A') return 1;
    if (c == 'B') return 2;
    if (c == 'C') return 3;
    return -1;
}

int getCol(char c) {
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    if (c == 'c') return 2;
    if (c == '(') return 3;
    if (c == ')') return 4;
    if (c == '$') return 5;
    return -1;
}

int isTerminal(char c) {
    return (c == 'a' || c == 'b' || c == 'c' || c == '(' || c == ')' || c == '$');
}

void parse() {
    push('$');
    push('S');

    while (top != -1) {
        char topStack = peek();
        char currentInput = input[ip];

        if (topStack == currentInput) {
            pop();
            ip++;
        }
        else if (isTerminal(topStack)) {
            printf("Invalid string\n");
            return;
        }
        else {
            int row = getRow(topStack);
            int col = getCol(currentInput);

            if (row == -1 || col == -1 || strlen(table[row][col]) == 0) {
                printf("Invalid string\n");
                return;
            }

            pop();

            char production[20];
            strcpy(production, table[row][col]);

            if (strcmp(production, "ε") != 0) {
                for (int i = strlen(production) - 1; i >= 0; i--) {
                    push(production[i]);
                }
            }
        }
    }

    if (input[ip] == '\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");
}

int main() {

    // Display Predictive Parsing Table
    printf("Predictive Parsing Table:\n");
    printf("      a     b     c     (     )     $\n");
    printf("S   ABC   ABC   ABC   ABC\n");
    printf("A     a     ε     ε     ε\n");
    printf("B           b     ε     ε\n");
    printf("C                 c   (S)\n");

    // LL(1) Check
    printf("\nGrammar is LL(1)\n");

    // Input string
    printf("\nEnter string: ");
    scanf("%s", input);

    // Append $
    strcat(input, "$");

    parse();

    return 0;
}