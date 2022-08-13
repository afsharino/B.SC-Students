#include <stdio.h>

signed int number;

//recursive function to return fibo numbs.
int fibo(int number) {

    if(number == 0) {

        return 0;
    }

    if(number == 1) {

        return 1;
    }

    return fibo(number-1) + fibo(number-2);
}

int main() {

    //printf("please enter a nonnegative number: ");
    scanf("%d" , &number);

    printf("%d" , fibo(1));
    for(int i = 2 ; i < number+1 ; i++) {

        printf(",%d" , fibo(i));
    }
}