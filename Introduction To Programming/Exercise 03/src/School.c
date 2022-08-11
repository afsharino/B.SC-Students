#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {

    char studentName[20];
    int grade;
    float average;
    int teacherNumber;
};

struct Manager {

    char managerName[20];
    int id;
};

struct Teacher {

    char teacherName[20];
    int teacherNumber;
    int salary;
};


//prototype
void searchTeacher(struct Student s[] , int teacherNumber , int studentsNumber);

int studentsNumber;
int teachersNumber;
int teacherNumber;
int count = 0;

int main() {

    //printf("please enter number of the students:\n");
    scanf("%d" , &studentsNumber);

    //printf("please enter number of the teachers:\n");
    scanf("%d" , &teachersNumber);

    struct Manager m;
    struct Student s[20];
    struct Teacher t[5];

    //manager info
    //printf("please enter manager name:\n");
    while ((getchar()) != '\n');
    scanf("%[^\n]s" , m.managerName);
    //printf("please enter manager id:\n");
    scanf("%d" , &m.id);

    //teacher info
    for(int i = 0 ; i < teachersNumber ; i++) {

        //printf("please enter teacher name\n");
        while ((getchar()) != '\n');
        scanf("%[^\n]s" , t[i].teacherName);
        //printf("please enter teacher number\n");
        scanf("%d" , &t[i].teacherNumber);
        //printf("please enter salary\n");
        scanf("%d" , &t[i].salary);
    }

    //student info
    for(int i = 0 ; i < studentsNumber ; i++) {

        //printf("please enter student name\n");
        while ((getchar()) != '\n');
        scanf("%[^\n]s" , s[i].studentName);
        //printf("please enter student grade\n");
        scanf("%d" , &s[i].grade);
        //printf("please enter student average\n");
        scanf("%f" , &s[i].average);
        //printf("please enter teacher number\n");
        scanf("%d" , &s[i].teacherNumber);
    }

     //printf("please enter teacher number for searching");
     scanf("%d" , &teacherNumber);

     //calling function
     searchTeacher(s , teacherNumber , studentsNumber);


}

void searchTeacher(struct Student s[] , int teacherNumber, int studentsNumber) {

    for(int i = 0 ; i < studentsNumber ; i++) {

        if(teacherNumber == s[i].teacherNumber) {

            printf("%s\n" , s[i].studentName);
        }
        // this condition count that how many times teacher number does not match with any student.
        if(teacherNumber != s[i].teacherNumber) {

            count++;
        }
    }
    //check that is for all students teacher number does not match
    if(count == studentsNumber) {

        printf("No student.");
    }
}