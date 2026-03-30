#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

// Function to check operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to apply operation
int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
    }
    return 0;
}

// Function to remove spaces
void removeSpaces(char *str) {
    int i, j = 0;
    char temp[MAX];

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '\n')
            temp[j++] = str[i];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

// Perform constant folding
void constantFold(char *expr) {
    char output[MAX] = "";
    int i = 0;

    while (i < strlen(expr)) {

        // If digit → check full number
        if (isdigit(expr[i])) {
            int num1 = 0;

            while (isdigit(expr[i])) {
                num1 = num1 * 10 + (expr[i] - '0');
                i++;
            }

            // Check if next is operator and next-next is number
            if (isOperator(expr[i]) && isdigit(expr[i + 1])) {
                char op = expr[i++];
                int num2 = 0;

                while (isdigit(expr[i])) {
                    num2 = num2 * 10 + (expr[i] - '0');
                    i++;
                }

                int result = applyOp(num1, num2, op);

                char temp[20];
                sprintf(temp, "%d", result);
                strcat(output, temp);
            } else {
                char temp[20];
                sprintf(temp, "%d", num1);
                strcat(output, temp);
            }
        }

        // If variable
        else if (isalpha(expr[i])) {
            strncat(output, &expr[i], 1);
            i++;
        }

        // If operator
        else if (isOperator(expr[i])) {
            strncat(output, &expr[i], 1);
            i++;
        }

        // Parenthesis
        else {
            strncat(output, &expr[i], 1);
            i++;
        }
    }

    printf("Optimized Expression: %s\n", output);
}

int main() {
    char expr[MAX];

    printf("Enter expression: ");
    fgets(expr, sizeof(expr), stdin);

    removeSpaces(expr);

    constantFold(expr);

    return 0;
}