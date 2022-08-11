#include <stdio.h>
#include <string.h>

char string[100];
int length;


int main() {

    gets(string);
    length = strlen(string);

    for(int i = 0 ; i < length-1 ; i++) {

        if(string[i] == ' ') {
            string[i] = '*';
        }
    }
    printf(string);
}
