%option noyywrap

%{
#include <stdio.h>

int charactersCount = 0;
int wordsCount = 0;
int linesCount = 0;
int enterCount = 0;
%}

%%
\n {
        enterCount++;
        charactersCount++;
        linesCount++;

        if (enterCount == 3)
        {
            int actualLines = linesCount - 3;
            if (actualLines < 1)
                actualLines = 1;

            printf("\nCharacters : %d\n", charactersCount - 3);
            printf("Words : %d\n", wordsCount);
            printf("Line : %d\n\n", actualLines);

            charactersCount = 0;
            wordsCount = 0;
            linesCount = 0;
            enterCount = 0;

            printf("Enter text again (Press ENTER 3 times to finish):\n");
        }
    }

[ \t]+ {
            charactersCount += yyleng;
            enterCount = 0;
        }

[A-Za-z0-9]+ {
                wordsCount++;
                charactersCount += yyleng;
                enterCount = 0;
             }

. {
        charactersCount++;
        enterCount = 0;
  }
%%

int main()
{
    printf("Enter text (Press ENTER 3 times to finish):\n");
    yylex();
    return 0;
}
