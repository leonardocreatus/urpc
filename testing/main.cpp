#include <iostream>

void sum1(int& x){
    printf("sum1: %p\n", &x);
    x *= 10;
}

void sum2(int x){
    printf("sum2: %p\n", &x);
    x *= 10;
}


int main(int argc, char** argv){
    int n = 5;
    printf("main: %p\n", &n);
    sum2(n);

    sum1(n);
}