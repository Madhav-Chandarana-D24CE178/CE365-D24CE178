// Course : CE365 Compiler Construction. ID : D24CE178
#include <stdio.h>
#include <string.h>

int main()
{
    // variable Declarations:

    char s[100]; // Declaring a String.
    int i = 0;

    // Taking Input :

    scanf("%s", s); // Taking Input for the String.

    while (s[i] == 'a') // Checking if the there is 'a' in the String or not, if it was there then we have to skip all the 'a'.
	{
        i++;
    }

    if (s[i] == 'b' && s[i + 1] == 'b' && s[i + 2] == '\0') // Checking if the 2nd last and last character is 'b' or not, if it is 'b' then it is a Valid string.
	{
        printf("Valid String");
    }
	
	else // If the 2nd last or Last character is not a character 'b' then the String is Invalid.
	{
        printf("Invalid String");
    }

    return 0;
}