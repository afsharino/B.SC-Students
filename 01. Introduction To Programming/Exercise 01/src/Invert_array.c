#include <stdio.h>

int array[100];
int size;
int temporary = 0;

int main() {
    //printf("please enter size of array: ");
    scanf("%d" , &size);
    //printf("please enter elements of an array:\n");
    for(int i = 0 ; i < size ; i++) {

        scanf("%d" , &array[i]);
    }
    //start inverting
    for(int i = 0 ; i < size - 1 ; i++) {
            for(int j = 0 ; j < size - i - 1; j++) {

                temporary = array[j+1];
                array[j+1] = array[j];
                array[j] = temporary;
            }
    }
    //printf("the inverted array is:\n");
    for(int i = 0 ; i < size ; i++) {

        printf("%d\t" , array[i]);
    }
}