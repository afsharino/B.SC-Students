#include <stdio.h>
#include <string.h>

char string[100];
int wordCounter = 0;
int length;

int main() {

    gets(string);
    length = strlen(string);

    for(int i = 0 ; i < length ; i++) {

        if(string[i] == ' ' && string[i+1] != ' ') {

            wordCounter++;
        }
    }

    printf("%d",(wordCounter+1));

}