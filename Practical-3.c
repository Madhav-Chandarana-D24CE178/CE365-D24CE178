#include <stdio.h> // Include Functions like 'fopen()', 'fgetc()', 'printf()'.
#include <ctype.h> // Provides Character Checking functions : 1. isalpha() -> letter    2. isdigit() -> digit   3. isalnum() -> letter or digit     4. isspace() -> space, tab, newline.
#include <string.h> // Used for Strings Operations like 'strcmp()', 'strcpy()', 'strlen()'.

char symbols[50][20]; // This 2D array contains Symbol Table. It can store : -> 50 identifiers      -> Each identifier up to 20 characters. 
int symCount = 0; // Keeps count of how many identifiers are sotred.

void addSymbol(char word[]) // This function adds and identifiers to the symbol table. Only adds it if it does not already exist. 
{
    for (int i = 0; i < symCount; i++) // Loops through the symbol table.
    {
        if (strcmp(symbols[i], word) == 0) // The function 'strcmp()' chcecks if word already exist.
        {
            return; // If found then return (do not duplicate)
        }
    }
    strcpy(symbols[symCount++], word); // The function 'strcpy()' Copies word into symbol table and increments symCount
}

int main() 
{
    FILE *fp; // Created File pointer to read "input.c".
    char ch, buffer[50]; // The variable 'ch' reads one character at a time. 'buffer' stores identifiers or numbers temporarily.
    int i = 0, line = 1; // 'i' is an index for buffer. 'line' keeps track of line number.
    int errorLine = -1; // Stores line number of lexical error. -1 means no error found yet.
    char errorLexeme[20]; // Stores invalid token like '7H'.

    fp = fopen("input.c", "r"); // Opens "input.c" in read mode.

    if (fp == NULL) // If file does not exist then stop the Program.
    {
        printf("File not found");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) // If File exist then Reads character by character at a time until reached the EOF (End Of File).
    {

        if (ch == '\n') // Everytime newline occurs then increase line number.
        {
            line++; 
        }

        if (isspace(ch)) // Ignores spaces, tabs, newlines.
        {
            continue;
        }

        if (ch == '/') // '/' may start a comment.
        {
            char next = fgetc(fp);

            if (next == '/') 
            {
                while (fgetc(fp) != '\n'); // Skips everything until newline.
                line++;
            }

            else if (next == '*') 
            {
                char a, b;
                a = fgetc(fp);
                b = fgetc(fp);

                while (!(a == '*' && b == '/')) // Reads character until '*/' is found.
                {
                    a = b;
                    b = fgetc(fp);
                }
            }

            else 
            {
                ungetc(next, fp); // Pushes character back into file.
            }
        }

        else if (isalpha(ch)) // Identifier must start with a letter.
        {
            buffer[i++] = ch;

            while (isalnum(ch = fgetc(fp))) // Keep reading letters / digits.
            {
                buffer[i++] = ch; // Store first letter.
            }

            buffer[i] = '\0'; // End the String.
            i = 0; // Reset buffer index.
            ungetc(ch, fp); // Push back non-identifier character.
            addSymbol(buffer); // Add identifier to symbol table.
        }

        else if (isdigit(ch)) // Number starts with digit.
        {
            buffer[i++] = ch;

            while (isalnum(ch = fgetc(fp))) // Keep reading letters / digits.
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0'; // End the String.
            i = 0; // Reset buffer index.
            ungetc(ch, fp); // Push back non-identifier character.

            if (isalpha(buffer[strlen(buffer) - 1])) // If number ends with letter -> Invalid. For Example : '7H', '12abc'.
            {
                errorLine = line;
                strcpy(errorLexeme, buffer);
            }
        }
    }

    fclose(fp);

    printf("LEXICAL ERRORS\n");
    if (errorLine != -1)
    {
        printf("Line %d : %s invalid lexeme\n\n", errorLine, errorLexeme); // Prints error if found.
    }

    else
    {
        printf("None\n\n"); // No errors found.
    }

    printf("SYMBOL TABLE ENTRIES\n");

    for (int j = 0; j < symCount; j++) // Prints all identifiers.
    {
        printf("%d) %s\n", j + 1, symbols[j]);
    }

    return 0;
}
