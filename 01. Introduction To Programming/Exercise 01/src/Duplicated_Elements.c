#include <stdio.h>

int array[100];
int size;
int count =  0;

int main() {

    //get array size & its elements from the user
    scanf("%d",&size);
    for(int i = 0 ; i < size ; i++) {

            scanf("%d",&array[i]);
    }

    //Algorithm of count duplicate elements
    for(int i = 0 ; i < size ; i++) {

        for(int j = i + 1 ; j < size ; j++) {

            if(array[i] == array[j]) {

                count = count+1;
                break;
            }
        }
    }
    printf("%d" , count);
}