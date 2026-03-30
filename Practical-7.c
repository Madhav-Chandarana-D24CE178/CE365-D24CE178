#include <stdio.h>
#include <string.h>

void printSet(char *name, char set[][10], int size) {
    printf("%s = {", name);
    for (int i = 0; i < size; i++) {
        printf("%s", set[i]);
        if (i != size - 1) printf(", ");
    }
    printf("}\n");
}

int main() {

    // FIRST sets
    char firstS[][10] = {"a", "b", "(", "c"};
    char firstA[][10] = {"a", "ε"};
    char firstB[][10] = {"b", "ε"};
    char firstC[][10] = {"(", "c"};
    char firstD[][10] = {"a", "(", "c"};

    // FOLLOW sets
    char followS[][10] = {")", "$"};
    char followA[][10] = {"b", "(", "c"};
    char followB[][10] = {"(", "c"};
    char followC[][10] = {")", "$"};
    char followD[][10] = {")", "$"};

    printf("FIRST Sets:\n");
    printSet("First(S)", firstS, 4);
    printSet("First(A)", firstA, 2);
    printSet("First(B)", firstB, 2);
    printSet("First(C)", firstC, 2);
    printSet("First(D)", firstD, 3);

    printf("\nFOLLOW Sets:\n");
    printSet("Follow(S)", followS, 2);
    printSet("Follow(A)", followA, 3);
    printSet("Follow(B)", followB, 2);
    printSet("Follow(C)", followC, 2);
    printSet("Follow(D)", followD, 2);

    return 0;
}