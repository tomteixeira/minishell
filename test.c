#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char buffer[1024];
    ssize_t bytesRead;

    printf("Enter input: ");
    bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));

    if (bytesRead == 0) {
        printf("Ctrl-D (EOF) received. Exiting.\n");
        exit(0);
    } else if (bytesRead < 0) {
        perror("Error reading input");
        exit(1);
    } else {
        // Process the input
        printf("You entered: %s", buffer);
    }

    return 0;
}
