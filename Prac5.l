%option noyywrap

%{
#include <stdio.h>
#include <string.h>

int lineNumber = 1;
int emptyLines = 0;

int tokenIndex = 0;
int errorIndex = 0;
int symbolIndex = 0;

char tokenList[500][100];
char errorList[100][100];
char symbolTable[100][50];

void resetAll();
int isKeyword(char *);
int isSymbolPresent(char *);
void addSymbol(char *);
void addToken(char *);
void addError(char *);
%}

KEYWORD     int|float|char|double|long|short|void|return|if|else|while|for|do|break|continue|struct
ID          [a-zA-Z_][a-zA-Z0-9_]*
NUMBER      [0-9]+(\.[0-9]+)?
CHARCONST   \'[^\']\'
STRING      \"([^\\\"]|\\.)*\"
OPERATOR    \+|\-|\*|\/|=|==|!=|<=|>=|<|>|&&|\|\|
PUNCT       [\(\)\{\}\[\];,]

%%

"//".*                          ;
"/*"([^*]|\*+[^*/])*\*+"/"     ;

{KEYWORD} {
    char temp[100];
    sprintf(temp, "Keyword: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

{ID} {
    if (!isKeyword(yytext)) {
        char temp[100];
        sprintf(temp, "Identifier: %s", yytext);
        addToken(temp);
        addSymbol(yytext);
    }
    emptyLines = 0;
}

{NUMBER} {
    char temp[100];
    sprintf(temp, "Constant: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

{CHARCONST} {
    char temp[100];
    sprintf(temp, "Constant: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

{STRING} {
    char temp[100];
    sprintf(temp, "String: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

{OPERATOR} {
    char temp[100];
    sprintf(temp, "Operator: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

{PUNCT} {
    char temp[100];
    sprintf(temp, "Punctuation: %s", yytext);
    addToken(temp);
    emptyLines = 0;
}

[0-9]+[a-zA-Z]+ {
    char temp[100];
    sprintf(temp, "Line %d : %s invalid lexeme", lineNumber, yytext);
    addError(temp);
    emptyLines = 0;
}

\n {
    lineNumber++;
    emptyLines++;

    if (emptyLines == 3) {
        int i;

        printf("\n\nTOKENS:\n\n");
        for (i = 0; i < tokenIndex; i++)
            printf("%s\n", tokenList[i]);

        printf("\nLEXICAL ERRORS:\n");
        for (i = 0; i < errorIndex; i++)
            printf("%s\n", errorList[i]);

        printf("\nSYMBOL TABLE ENTRIES:\n");
        for (i = 0; i < symbolIndex; i++)
            printf("%d) %s\n", i + 1, symbolTable[i]);

        printf("\n\nEnter next C program (press ENTER 3 times to finish):\n\n");

        resetAll();
    }
}

[ \t]+ ;
. {
    char temp[100];
    sprintf(temp, "Line %d : %s invalid lexeme", lineNumber, yytext);
    addError(temp);
    emptyLines = 0;
}

%%

/* -------- Helper Functions -------- */

void resetAll()
{
    lineNumber = 1;
    emptyLines = 0;
    tokenIndex = errorIndex = symbolIndex = 0;
}

int isKeyword(char *word)
{
    const char *kw[] = {
        "int","float","char","double","long","short","void","return",
        "if","else","while","for","do","break","continue","struct"
    };
    int i;
    for (i = 0; i < 14; i++)
        if (strcmp(word, kw[i]) == 0)
            return 1;
    return 0;
}

int isSymbolPresent(char *sym)
{
    int i;
    for (i = 0; i < symbolIndex; i++)
        if (strcmp(symbolTable[i], sym) == 0)
            return 1;
    return 0;
}

void addSymbol(char *sym)
{
    if (!isSymbolPresent(sym))
        strcpy(symbolTable[symbolIndex++], sym);
}

void addToken(char *tok)
{
    strcpy(tokenList[tokenIndex++], tok);
}

void addError(char *err)
{
    strcpy(errorList[errorIndex++], err);
}

int main()
{
    printf("Enter C program (press ENTER 3 times to generate output):\n\n");
    yylex();
    return 0;
}
