#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100][20];
int top = -1;

int tempCount = 1;

// Push to operand stack
void push(char *val) {
    strcpy(stack[++top], val);
}

// Pop from operand stack
char* pop() {
    return stack[top--];
}

// Remove spaces from input
void removeSpaces(char *str) {
    int i, j = 0;
    char temp[100];

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Generate quadruple
void generate(char op, char *op1, char *op2) {
    char temp[20];
    sprintf(temp, "t%d", tempCount++);

    printf("%-10c %-10s %-10s %-10s\n", op, op1, op2, temp);

    push(temp);
}

// Process operator
void processOperator(char op) {
    char op2[20], op1[20];
    strcpy(op2, pop());
    strcpy(op1, pop());

    generate(op, op1, op2);
}

int main() {
    char input[100];
    char operators[100];
    int optop = -1;

    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);

    removeSpaces(input);

    printf("\nQuadruple Table:\n");
    printf("%-10s %-10s %-10s %-10s\n", "Operator", "Operand1", "Operand2", "Result");

    for (int i = 0; i < strlen(input); i++) {

        // If digit (handle multi-digit numbers)
        if (isdigit(input[i])) {
            char num[20] = "";
            int j = i;

            while (isdigit(input[j])) {
                strncat(num, &input[j], 1);
                j++;
            }

            push(num);
            i = j - 1;
        }

        // If '('
        else if (input[i] == '(') {
            operators[++optop] = input[i];
        }

        // If ')'
        else if (input[i] == ')') {
            while (optop != -1 && operators[optop] != '(') {
                processOperator(operators[optop--]);
            }
            optop--; // remove '('
        }

        // If operator
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            while (optop != -1 && precedence(operators[optop]) >= precedence(input[i])) {
                processOperator(operators[optop--]);
            }
            operators[++optop] = input[i];
        }
    }

    // Process remaining operators
    while (optop != -1) {
        processOperator(operators[optop--]);
    }

    return 0;
}