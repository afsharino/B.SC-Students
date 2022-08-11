#include <stdio.h>
#include <string.h>

char string[100];

int main() {

    //printf("please enter your string: \n");
    gets(string);
    int length = strlen(string);

    printf("%c" , string[length-1]);
    for(int i = length-2 ; i>= 0 ; i--) {

        if(string[i] != ' '){

            printf(" %c" , string[i]);
        }
    }
}
