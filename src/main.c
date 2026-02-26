#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[256];
    
    printf(" evalx v0.1 ('q' to quit) \n");

    while (1) {
        printf("  > ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "q") == 0) break;

        printf("You typed: %s\n", buffer);
    }
    return 0;
}
