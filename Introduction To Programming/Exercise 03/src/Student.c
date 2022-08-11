#include <stdio.h>
#include <string.h>

int studentsNumber;

struct Student {

    int age;
    int id;
    char name[20];
    char gender[20];
};

//prototypes
int duplicatID(struct Student student[] , int studentsNumber);
float Avg(struct Student student[] , int studentsNumber);

int count = 0 ;

int main (){

    //printf("please enter number of students\n");
    scanf("%d" , &studentsNumber);
    struct Student student[100];

    for(int i = 0 ; i < studentsNumber ; i++) {

        //printf("please enter your age\n");
        scanf("%d" , &student[i].age);
        //printf("please enter your id\n");
        scanf("%d" , &student[i].id);
        //printf("please enter your name\n");
        while ((getchar()) != '\n');
        scanf("%[^\n]s" , student[i].name);
        //printf("please enter your gender\n");
        scanf("%s" , student[i].gender);
    }

    //check if the id is duplicate or not.
    int duplicateid = duplicatID(student,studentsNumber);
    if(duplicateid == 1) {

        printf("Duplicate ID.");
    }
    else {

        printf("%.2f", ((signed long)(Avg(student , studentsNumber) * 100) * 0.01f));

    }
}

//function to check if the id is duplicate or not.
int duplicatID(struct Student student[] , int studentsNumber) {

    for(int i = 0 ; i < studentsNumber ; i++) {

        for(int j = i+1 ; j < studentsNumber ; j++) {

            if(student[i].id == student[j].id) {

                count++;
            }
        }
    }
    if(count == 0) {

        return (-1);
    }
    else  {

        return (1);
    }
}

//function for calculating average...
float Avg(struct Student student[] ,int studentsNumber) {

    float sum = 0 ;
    float avg;

    for(int i = 0 ; i < studentsNumber ; i++) {

        sum += student[i].age;
    }

    avg = sum / studentsNumber;
    return avg;
}
