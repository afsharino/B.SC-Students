#include <stdio.h>

int matrix[3][3];

int main() {
    //"nested for loop" for scan entries from the user.
    for(int i = 0 ; i < 3 ; i++) {

        for(int j = 0 ; j < 3 ;j++) {

            scanf("%d" , &matrix[i][j]);
        }
        printf("\n");
    }
    //"nested for loop" for print matrix :)
    for(int i = 0 ; i < 3 ; i++) {

        for(int j = 0 ; j < 3 ;j++) {

            printf("%d\t" , matrix[i][j]);
        }
        printf("\n");
    }
}
