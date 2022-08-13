#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int studentsNumber;


//structure for students information.
struct Student {

    char name[20];
    float grade;
    int id;
};

int main() {

    //printf("please enter number of students");
    scanf("%d" , &studentsNumber);
    struct Student student[studentsNumber];

    for(int i = 0 ; i < studentsNumber ; i++) {

        while ((getchar()) != '\n');
        //printf("please enter name\n");
        scanf("%[^\n]s", &student[i].name);
        //printf("please enter grade\n");
        scanf("%f", &student[i].grade);
        //printf("please enter id\n");
        scanf("%d", &student[i].id);
    }

    //***start calculating the average***

    float sum = 0;
    float average;
    for(int i = 0 ; i < studentsNumber ; i++) {

        sum = sum + student[i].grade;
    }
    average = sum / studentsNumber;
    printf("%.2f", ((signed long)(average * 100) * 0.01f));

    //calculating ended.***

    for (int i = 0; i < studentsNumber; i++) {

        if(student[i].grade > average) {

            printf("\n%s" , student[i].name);
        }
    }
}