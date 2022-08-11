#include <stdio.h>

int array[100];
int even[100];
int odd[100];
int size;
int k = 0 , l = 0;


int main() {

    //printf("please enter size of the array: ");
    scanf("%d" , &size);

    //printf("please enter elements:\n");
    for(int i = 0 ; i < size ; i++) {

        scanf("%d" , &array[i]);
    }

    for(int i = 0 ; i < size ; i++) {

        if(array[i] % 2 == 0) {

                even[k] = array[i];
                k++;
        }

        if(array[i] % 2 != 0) {

            odd[l] = array[i];
            l++;
        }
    }
    //printf("the even array is: \n");
    for(int i = 0 ; i < k ; i++) {

        printf("%d\t" , even[i]);
    }

    printf("\n");
    //printf("the odd array is: \n");
    for(int i = 0 ; i < l ; i++) {

        printf("%d\t" , odd[i]);
    }
}
