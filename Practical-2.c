#include <stdio.h> // Includes Function like 'printf()' and 'scanf()'.
#include <string.h>

int main()
{
    // variable Declaration :

    int numSymbols, numStates; // Here 'numSymbols' is used for Number of input symbols, Like 'a' , 'b'. 'numStates' is used for number of states in DFA.
    int startState; // This variable is used for stroing the initial state of the DFA
    int numAccept; // This varibale is used to know the Number of accepting (final) states.
    int acceptStates[10]; // This array contains all the accepting (final) states, and the Maximum accepting (final) states are 10 (Also the Size of the Array).
    int transition[10][10]; // This 2D array contains the Transition Table, Rows -> states, Columns -> input symbols, Value -> next state.
    char symbols[10]; // This array contains all the input symmbols like 'a', 'b'. Maximum size is 10, means Max 10 Input symbol is allowed.
    char input[50]; //This array stores the input string entered by the user.

    int currentState, i, j; // The variable 'currentState' tracks where DFA is currently. The varibale 'i', 'j' are used as loop counters.
    int valid = 0; // This is a Flag variable and it is used for checking wheather the string is Valid or Invalid.

    // Taking Inputs:

    printf("Number of input symbols : "); // User enters how many symbols DFA has.
    scanf("%d", &numSymbols);

    printf("Input symbols : ");

    for (i = 0; i < numSymbols; i++)
    {
        scanf(" %c", &symbols[i]); // Reads each input symbol one by one. The space before '%c' avoids newline issues. for example : "a b".
    }

    printf("Enter number of states : "); // User enters number of DFA states.
    scanf("%d", &numStates);

    printf("Initial state : "); // Starting point of DFA.
    scanf("%d", &startState);

    printf("Number of accepting states : ");
    scanf("%d", &numAccept);

    printf("Accepting states : ");

    for (i = 0; i < numAccept; i++) // Stores accepting (final) states of DFA in an array.
    {
        scanf("%d", &acceptStates[i]);
    }

    printf("Transition table :\n"); // -> For each state    -> For each symbol  -> It will ask user : From state i on symbol x, go to which state?. For example : 1 to a -> 2, 1 to b -> 1

    for (i = 1; i <= numStates; i++)
    {
        for (j = 0; j < numSymbols; j++)
        {
            printf("%d to %c -> ", i, symbols[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    printf("\nInput string : "); // Reads the string to be checked.
    scanf("%s", input);

    currentState = startState; // DFA begins from the initial state.

    for (i = 0; input[i] != '\0'; i++) // Loop until end of string.
    {
        int found = 0;
        for (j = 0; j < numSymbols; j++) // Match input character with symbol list, If matched : -> Move DFA to next state , -> Mark symbol as found
        {
            if (input[i] == symbols[j])
            {
                currentState = transition[currentState][j];
                found = 1; // Used to check if input symbol exists in alphabet.
                break;
            }
        }
        if (!found) 
        {
            printf("Invalid String"); // If symbol is not part of alphabet. String is immediately invalid.
            return 0;
        }
    }

    for (i = 0; i < numAccept; i++) 
    {
        if (currentState == acceptStates[i]) // Checks wheather final state is an accepting state.
        {
            valid = 1;
            break;
        }
    }

    if (valid)
    {
        printf("Valid String");
    }

    else
    {
        printf("Invalid String");
    }

    return 0;
}