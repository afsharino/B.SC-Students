#include <stdio.h>

signed int matrix[3][3];
int determinan;

//function to calculate determinan
void determinanFunc(signed int matrix[3][3]) {

    //The algorithm is: expansion based on the first line.
    determinan = ( ( (matrix[0][0]) * ( ( (matrix[1][1]) * (matrix[2][2]) ) - ( (matrix[1][2]) * (matrix[2][1]) ) ) ) -

                   ( (matrix[0][1]) * ( ( (matrix[1][0]) * (matrix[2][2]) ) - ( (matrix[1][2]) * (matrix[2][0]) ) ) ) +

                   ( (matrix[0][2]) * ( ( (matrix[1][0]) * (matrix[2][1]) ) - ( (matrix[1][1]) * (matrix[2][0]) ) ) )

                 );
    printf("%d" , determinan);


}
int main() {

    //"nested for loop" for scan entries from user.
    for(int i = 0 ; i < 3 ; i++) {

        for(int j = 0 ; j < 3 ;j++) {

            scanf("%d" , &matrix[i][j]);
        }
        printf("\n");
    }
    //calling function
    determinanFunc(matrix);

}
