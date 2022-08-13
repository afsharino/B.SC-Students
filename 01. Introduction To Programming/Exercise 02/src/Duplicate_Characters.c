#include <stdio.h>
#include <string.h>

char string[100];
int length;
int count = 1;

int main() {

    //printf("please enter a String:\n");
    gets(string);
    length = strlen(string);

    for(int i = 0 ; i < length ; i++){

        count = 1;
        for(int j = i+1 ; j < length ; j++) {

            if(string[i]==string[j] && string[i] != ' ' ) {

                count++;
                string[j] = NULL;
            }
        }
        if(i == 0) {

            if(string[0] != NULL && string[0] != ' ') {

                printf("%c %d" , string[0] , count);
            }
        }
        else {

            if(string[i] != NULL && string[i] != ' ') {

                printf("\n%c %d" , string[i] , count);
            }
        }

    }

}