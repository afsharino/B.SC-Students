#include <stdio.h>

int decimalNumber;
int binary[1000];

//function to convert decimal to binary
void decimaltobinary(int decimalNumber){

    int i = 0;
    do {
        binary[i] = decimalNumber % 2;
        decimalNumber = decimalNumber / 2;
        i++;
    }while(decimalNumber != 0 );

    for(int j = i-1 ; j >= 0 ; j--) {

        printf("%d" ,binary[j]);
    }
}

int main() {

    //get decimal number from the user
    scanf("%d" , &decimalNumber);
    //calling function
    decimaltobinary(decimalNumber);

}
