#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* filename = "prog1.cfg";
    char buffer[256];
    FILE* fp = fopen(filename, "r");
    if (fp) {
        while ((fgets(buffer, 256, fp)) != NULL)
        printf("%s", buffer);
    fclose(fp);
}
}