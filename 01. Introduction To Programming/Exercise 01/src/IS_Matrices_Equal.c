#include <stdio.h>

int rows1 , rows2;
int columns1 , columns2;
int matrix1[100][100];
int matrix2[100][100];
int count = 0;

int main() {

    //printf("Input Rows and Columns of the 1st matrix :\n");
    scanf("%d" , &rows1 );
    scanf("%d" , &columns1);

    //printf("Input Rows and Columns of the 2nd matrix :\n");
    scanf("%d" , &rows2 );
    scanf("%d" , &columns2);

    //printf("Input elements in the first matrix :\n");
    for(int i = 0 ; i < rows1 ; i++) {

        for(int j = 0 ; j < columns1 ; j++) {

            scanf("%d" , &matrix1[i][j]);
        }
        printf("\n");
    }

    //printf("Input elements in the second matrix :\n");
    for(int i = 0 ; i < rows2 ; i++) {

        for(int j = 0 ; j < columns2 ; j++) {

            scanf("%d" , &matrix2[i][j]);
        }
        printf("\n");
    }


    if (rows1 == rows2 && columns1 == columns2) {

        for(int i = 0 ; i < rows1 ; i++) {

            for(int j = 0 ; j < columns1 ; j++) {

                if(matrix1[i][j] == matrix2[i][j]) {
                    count++;
                    continue;
                }
                else {
                    printf("Not equal");
                    break;
                }
            }
        }
        if(count == rows1*columns1){

            printf("Equal");
        }
        }

    else {
        printf("Not equal");
    }

}