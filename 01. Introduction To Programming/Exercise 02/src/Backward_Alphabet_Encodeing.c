#include <stdio.h>
#include <string.h>

char message[100];
char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int length;

int main(){
    //scan the string
    gets(message);
    length = strlen(message);
    //in this part we convert uppercase chars to lowercase by the decimal value of ascii table.
    for(int i = 0 ; i < length ; i++) {

        if(message[i] > 64 && message[i] < 91) {

            message[i] = message[i] + 32 ;
        }
    }

    //to replace each char with its orresponding backward alphabet
    for(int i = 0 ; i < length ; i++) {

        for(int j = 0 ; j < 26 ; j++) {

            if(message[i] == alphabet[j]) {

                message[i] = alphabet[26-(j+1)];
                break;
            }

        }
    }

    printf("%s", message);
}
