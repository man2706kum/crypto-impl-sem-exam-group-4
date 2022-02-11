#include<stdio.h>

void swap (int x1, int x2, int n) {
    int t[2];
    t[0] = x1;
    t[1] = x2;

    x1 = t[n];
    x2 = t[n^1];

    printf("n:%d, x1: %d, x2: %d\n", n, x1, x2);
}

int main() {

    swap(10, 20, 1);
}