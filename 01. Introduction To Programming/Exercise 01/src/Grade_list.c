#include <stdio.h>
#include <math.h>

float grades[100];
float biggerthanaverage[100];
int numberOfgrades;
float average;
int sum;
int k = 0;

int main() {

    //printf("please enter number of grades: ");
    scanf("%d" , &numberOfgrades);

    //printf("please enter grades:\n");
    for(int i = 0 ; i < numberOfgrades ; i++) {

        scanf("%f" , &grades[i]);
    }

    //printf("students grades are:\n");

    if(fmod(grades[0]*100 , 10) == 0) {

            printf("%0.1f" , grades[0]);
        }
        else {
            printf("%0.2f" , grades[0]);
        }
    for(int i = 1 ; i < numberOfgrades ; i++) {

        if(fmod((grades[i]*100) ,10) == 0) {

            printf(",%0.1f" , grades[i]);
        }
        else {
            printf(",%0.2f" , grades[i]);
        }

    }
    printf("\n");

    //sum & calculate average
    for(int i = 0 ; i < numberOfgrades ; i++) {

        sum += grades[i];
    }

    average = sum / numberOfgrades;

    //find grades which are bigger than average
    for(int i = 0 ; i < numberOfgrades ; i++) {

        if(grades[i] > average) {

                biggerthanaverage[k] += grades[i];
                k++;
        }
    }
    //print grades which are bigger than average

    if(fmod((biggerthanaverage[0]*100) , 10) == 0) {

            printf("%0.1f" , biggerthanaverage[0]);
    }
    else {
            printf("%0.2f" , biggerthanaverage[0]);
    }

    for(int i = 1 ; i < k ; i++) {

        if(fmod((biggerthanaverage[i]*100) , 10) == 0) {

            printf(",%0.1f" , biggerthanaverage[i]);
        }
        else {
            printf(",%0.2f" , biggerthanaverage[i]);
        }
    }
}