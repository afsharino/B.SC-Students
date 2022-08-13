#include <stdio.h>
char vote[10];
int counta = 0 ;
int countd = 0 ;
int countr = 0 ;

int main() {
    //printf("vote ten times:\n");
    for(int i = 0 ; i <10 ; i++) {

        scanf("%s" , &vote[i]);
    }

    for(int i = 0 ; i < 10 ; i++) {

        if(vote[i] == 'a') {

            counta = counta+1;
        }

        if(vote[i] == 'd') {

            countd = countd+1;
        }

        if(vote[i] == 'r') {

            countr = countr+1;
        }
    }

    printf("%d agree\n" , counta);
    printf("%d disagree\n" , countd);
    printf("%d recusant\n" , countr);

}