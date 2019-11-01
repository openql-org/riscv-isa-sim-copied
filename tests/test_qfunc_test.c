#include <stdio.h>
#include <stdlib.h>

int calc();
int main(int argc, char* argv[]) {
    // call qmeas
    int i = 0;
    int j = 0;
    for (i = 0; i < 10; i++) {
        j += 1;
    }
    printf("%d\n", calc());

    return j;
}
