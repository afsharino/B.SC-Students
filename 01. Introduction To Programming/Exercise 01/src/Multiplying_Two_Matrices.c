#include <stdio.h>

int matrix1[1000][1000];
int matrix2[1000][1000];
int size;
int answer[1000][1000];

int main() {

    //printf("please enter size of matrix: ");
    scanf("%d" , &size);
    //printf("please enter elements of matrix1: \n");
    //"nested for loop" to get the first matrix's elements from the user.
    for(int i = 0 ; i < size ; i++) {

        for(int j = 0 ; j < size ;j++) {

            scanf("%d" , &matrix1[i][j]);
        }
        printf("\n");
    }

    //printf("please enter elements of matrix2: \n");
    //"nested for loop" to get the second matrix's elements from the user.
    for(int i = 0 ; i < size ; i++) {

        for(int j = 0 ; j < size ;j++) {

            scanf("%d" , &matrix2[i][j]);
        }
        printf("\n");
    }

    //Start multiplying two matrices by each other
    for(int i = 0 ; i < size ; i++) {

        for(int j = 0 ; j < size ; j++) {

            answer[i][j] = 0 ;
            for(int k = 0 ; k < size ; k++) {

                answer[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    //printf("the multi matrix is: \n");
    for(int i = 0 ; i < size ; i++) {

        for(int j = 0 ; j < size ; j++) {

            printf("%d\t", answer[i][j]);
        }
        printf("\n");
    }
}