#include <stdio.h>
#include <string.h>

char string[100];
char temporary[100];
int length;


int main() {

    gets(string);
    length = strlen(string);
    //bubble sort
    for(int i = 0 ; i < length ; i++) {

        for(int j = 0 ; j < length-i-1 ; j++) {

            if(string[j] > string[j+1]) {

                temporary[j] = string[j];
                string[j] = string[j+1];
                string[j+1] = temporary[j];
            }
        }
    }
    for(int i = 0 ; i < length ; i++) {

        printf("%c",string[i]);
    }
}
