#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

int parseS();
int parseL();
int parseLdash();

void skipSpaces() {
    while (input[pos] == ' ')
        pos++;
}

int parseS() {
    skipSpaces();

    if (input[pos] == 'a') {
        pos++;
        return 1;
    }
    else if (input[pos] == '(') {
        pos++;

        if (!parseL())
            return 0;

        skipSpaces();

        if (input[pos] == ')') {
            pos++;
            return 1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

int parseL() {
    if (!parseS())
        return 0;

    return parseLdash();
}

int parseLdash() {
    skipSpaces();

    if (input[pos] == ',') {
        pos++;

        if (!parseS())
            return 0;

        return parseLdash();
    }
    return 1;
}

int main() {
    printf("Enter string: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline
    input[strcspn(input, "\n")] = '\0';

    pos = 0;

    if (parseS() && input[pos] == '\0')
        printf("Valid string");
    else
        printf("Invalid string");

    return 0;
}