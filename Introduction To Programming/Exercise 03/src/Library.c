#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct librarary {

    int isbn;
    char bookName[20];
    char author[20];
    int printYear;
};

//prototypes
int searchPrintyear(struct librarary books[] , int booksNumber , char searchterm[]);
int searchBookname(struct librarary books[] , int booksNumber , char searchterm[]);
int datatypeFounder(char searchterm[]);

int booksNumber;
char searchterm[20] = "";
char stringSearchterm[20];
int integerSearchterm;
int searchbookanswer;
int searchprintyearanswer;
int datatype;

int main() {

    //printf("please enter number of the books:");
    scanf("%d" , &booksNumber);
    struct librarary books[100];

    for(int i = 0 ; i < booksNumber ; i++) {

        //printf("please enter ISBN\n");
        scanf("%d" , &books[i].isbn);
        //printf("please enter book name\n");
        while ((getchar()) != '\n');
        scanf("%[^\n]s" , &books[i].bookName);
        //printf("please enter author name\n");
        while ((getchar()) != '\n');
        scanf("%[^\n]s" , &books[i].author);
        //printf("please enter print year\n");
        scanf("%d" , &books[i].printYear);
    }

    //printf("please enter search term\n");
    while ((getchar()) != '\n');
    scanf("%[^\n]S" , searchterm);

    datatype = datatypeFounder(searchterm);

    switch(datatype) {

    case 2:

        searchbookanswer = searchBookname(books , booksNumber ,searchterm);
        if(searchbookanswer == (-1)) {

            printf("Not found.");
        }
        else {

                printf("%d" , books[searchbookanswer].isbn);
                printf("\n%s" , books[searchbookanswer].bookName);
                printf("\n%s" , books[searchbookanswer].author);
                printf("\n%d" , books[searchbookanswer].printYear);
        }

        break;
    case 1:

        searchprintyearanswer = searchPrintyear(books , booksNumber , searchterm);
        if(searchprintyearanswer == (-1) ) {

            printf("Not found.");
        }
         else {

            printf("%d" , books[searchprintyearanswer].isbn);
            printf("\n%s" , books[searchprintyearanswer].bookName);
            printf("\n%s" , books[searchprintyearanswer].author);
            printf("\n%d" , books[searchprintyearanswer].printYear);
        }

        break;

    }
}
int searchPrintyear(struct librarary books[] , int booksNumber , char searchterm[]) {

    for(int i = 0 ; i < booksNumber ; i++) {

        if(books[i].printYear == atoi(searchterm)) {

            return (i);
        }
    }
    return (-1);

}

int searchBookname(struct librarary books[] , int booksNumber , char searchterm[]) {

    for(int i = 0 ; i < booksNumber ; i++) {

        if(strcmp(searchterm, books[i].bookName) == 0) {

            return (i);
        }
    }
    return (-1);
}

int datatypeFounder(char searchterm[] ) {

    char stringSearchterm[20] = "";
    double temp;
    int intinput;
    double value = 1e-12;
    int naghi;

    if(sscanf(searchterm , "%1f" , &temp) == 1) {

        intinput = (int) temp;
        if(fabs(temp - intinput) / temp >= value) {

            return 1;
        }
    }

    if(sscanf(searchterm , "%s" , stringSearchterm) == 1) {

        return 2;
    }
}