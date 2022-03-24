// file: hello.c
// Compile with:
// $ gcc hello.c -o hello

#include <stdio.h>  // for printf
#include <math.h>   // for sin()

int main() {
    int a = 12 + 4;
    printf("The ans is %d.\n", a); // %d for int

    double b = sin(0.4);
    printf("The ans is %f.\n", b); // %f for double
}

