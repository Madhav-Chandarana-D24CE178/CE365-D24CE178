%option noyywrap

%{
#include <stdio.h>
#include <string.h>

int lowercaseLettersCount;
int uppercaseLettersCount;
int digitsCount;
int symbolsCount;
int passwordLength;

void resetCounters()
{
    lowercaseLettersCount = 0;
    uppercaseLettersCount = 0;
    digitsCount = 0;
    symbolsCount = 0;
    passwordLength = 0;
}
%}

%%
[a-z]      { lowercaseLettersCount++; passwordLength++; }
[A-Z]      { uppercaseLettersCount++; passwordLength++; }
[0-9]      { digitsCount++; passwordLength++; }
[*;#$@]    { symbolsCount++; passwordLength++; }
\n         { return 1; }
.          { passwordLength++; }
%%

int main()
{
    while (1)
    {
        resetCounters();

        printf("\nEnter password: ");
        fflush(stdout);

        if (yylex() == 0)
            break;

        if (passwordLength >= 9 && passwordLength <= 15 &&
            lowercaseLettersCount >= 1 &&
            uppercaseLettersCount >= 1 &&
            digitsCount >= 1 &&
            symbolsCount >= 1)
        {
            printf("Valid password\n");
        }
        else
        {
            printf("Invalid password\n");
        }
    }

    return 0;
}
