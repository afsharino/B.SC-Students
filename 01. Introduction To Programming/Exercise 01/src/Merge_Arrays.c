#include <stdio.h>

int array1[100] , arraySize1;
int array2[100] , arraySize2;
int mergedArray[100] , mergedArraysize;
int temporary;
int i , j;

int main() {

    //get first array size & its elements
   // printf("Input the number of elements in the first array:");
    scanf("%d" , &arraySize1);
   // printf("Input elements in the array:\n");
    for(int i = 0 ; i < arraySize1 ; i++) {

        scanf("%d" , &array1[i]);
    }

    //get second array size & its elements
   // printf("Input the number of elements in the second array:");
    scanf("%d" , &arraySize2);
    //printf("Input elements in the array:\n");
    for(int i = 0 ; i < arraySize2 ; i++) {

        scanf("%d" , &array2[i]);
    }
    //start merging two array wit each other
    for(int i = 0 ; i < arraySize1 ; i++) {

        mergedArray[i] = array1[i];
    }
    mergedArraysize = arraySize1 + arraySize2;

    for( i = 0 , j = arraySize1 ; i < arraySize2 && j < mergedArraysize ; i++ , j++) {

        mergedArray[j] = array2[i];
    }


    //"bubble sort" for sorting array in an ascending way
    for(i = 0 ; i < mergedArraysize ; i++) {

        for(j = 0 ; j < mergedArraysize - i - 1 ; j++ ) {

            if(mergedArray[j] > mergedArray[j+1]) {

                temporary = mergedArray[j];
                mergedArray[j] = mergedArray[j+1];
                mergedArray[j+1] = temporary;
            }
        }
    }
    printf("%d" , mergedArray[0]);
    for( i = 1 ; i < mergedArraysize ; i++) {

        printf(",%d" , mergedArray[i]);

    }

}