#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#define MAXLEN 30

void filling(int n, int m, char **lstpw, char pw[66]);
void add_req_symbs(int n,int m, char** lstpw, char symbs[MAXLEN], const char nums[10], const char alph[52]);
void add_to_file(int n, int m, char **lstpw);

int main() {
    srand( (unsigned)time( NULL ) ); /*using it to make rand() generate different subsequence*/
    int n,i,j,m,ran1,ran2,ran3;
    char q;
    char alph[]= {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                  'n','o','p','q','r','s','t','u','v','w','x','y','z'}; /*define english alphabet*/
    char pw[66];/*initialize char array of all password symbols*/
    char symbs[MAXLEN]; /*initialize char array of special symbols*/
    char** lstpw=NULL;/*initialize char array of list of passwords*/
    char nums[]={'1','2','3','4','5','6','7','8','9','0'};/*initialize char array of numbers*/
    printf("Welcome to the pw_creator! I will generate a list of strong passwords for you!\n");
    printf("Tap 'q' to exit or space to continue..\n");
    scanf("%c", &q);
    if(q=='q'){
        exit(0);
    }
    if(!isspace(q)){
        puts("Unrecognized symbol!");
        getch();
        exit(0);
    }
    fflush(stdin);
    printf("->enter string of special symbols you want to use in your password(NOT letter or number!):");
    fgets(symbs, MAXLEN, stdin); /*getting special symbs string*/
    symbs[strlen(symbs)-1]='\0';
    fflush(stdin); /*flush*/
    printf("->enter your passwords size(from 8 to 15):");
    scanf("%i",&n);
    if(n>15||n<8){ /*checking pw length for correct size*/
        system("@cls||clear");
        printf("-->Incorrect password size!");
        getch();
        exit(0);
    }
    printf("->last one: enter the number of passwords:");
    scanf("%i", &m);
    printf("Just the second...\n");
    for (i=0; i< 66;i++){
        pw[i]=0+rand()%66+'0';
    }
    for (i = 0; i < strlen(symbs); ++i) {
        pw[i]=symbs[i];/*filling pw array of symbs*/
    }
    for(i= strlen(symbs),j=0;j< strlen(alph);i++,j++){
        pw[i]=alph[j];/*filling pw array of alphabet symbols*/
    }for(i= strlen(symbs)+strlen(alph),j=0;j< strlen(nums);i++,j++){
        pw[i]=nums[j];/*filling pw array of number symbols*/
    }
    lstpw = (char**) malloc(m*sizeof (char*));
    for(i=0;i<m;i++){
        lstpw[i]=(char *) malloc(n*sizeof (char)); /*allocate memory for list of passwords*/
    }
    if(lstpw==NULL){
        printf("-->Memory error!");
        system("@cls||clear");
        getch();
        exit(0);
    }

    add_req_symbs(n,m,lstpw,symbs,nums,alph);
    filling(n,m,lstpw, pw);
    add_to_file(n,m, lstpw);
    free(lstpw);
    system("@cls||clear");
    printf("We've done! File with your passwords is in the same directory with an pw_creator.exe!\n Tap enter to exit....");
    getch();
    return 0;
}


/*fun to add in password required symbols*/
void add_req_symbs(int n,int m, char** lstpw, char symbs[MAXLEN], const char nums[10], const char alph[52]){
    srand( (unsigned)time( NULL ) ); /*using it to make rand() generate different subsequence*/
    int i,j,ran1,ran2,ran3,ran4;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            lstpw[i][j]='\n';/*making all the symbols = '\n' to prevent line breaks in the password later in line 68*/
        }
    }
    for (i = 0; i < m; ++i) {
        ran1 =0+rand()%n;
        ran3=ran1;
        ran2 = 0+rand()% strlen(symbs);
        lstpw[i][ran1] = symbs[ran2]; /*fill random cells of the array with random characters from the alphabet, numbers and special characters*/
    }
    for (i = 0; i < m; ++i) {
        ran1 =0+rand()%n;
        ran4=ran1;
        ran2 = 0+rand()% 26;
        lstpw[i][ran1] = alph[ran2];
    }
    for (i = 0; i < m; ++i) {
        ran1 =0+rand()%n;
        ran2 = 0+rand()% 10;
        if(ran1==ran3||ran1==ran4){
            ran1=ran1+rand()%n;
        }
        lstpw[i][ran1] = nums[ran2];
    }
}

/*function for filling list of our passwords*/
void filling(int n, int m, char** lstpw, char pw[66]){
    srand( (unsigned)time( NULL ) ); /*using it to make rand() generate different subsequence*/
    int i,j,ran3;
    ran3=0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if(lstpw[i][j]=='\n'){
                ran3=0+rand()% 66;/*checking for '\n' value in cell and fill that cell with random value from pw array*/
                lstpw[i][j] = pw[ran3];
            }

        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (isspace(lstpw[i][j])) lstpw[i][j] = '_';
            if (lstpw[i][j] == ' ') lstpw[i][j] = '_';
        }
    }
}

/*function that puts our array in file*/
void add_to_file(int n, int m, char **lstpw){
    FILE  *file;
    int i,j;
    file = fopen("passwords.txt", "r"); /*open a file*/
    if(file==NULL) {
        file = fopen("passwords.txt", "w"); /*if file is not exist, create a file for writing from 0 byte*/
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                fprintf(file, "%c", lstpw[i][j]);/*printing result into a file*/
            }
            fputs("\n", file);
        }
    }else{
        file = fopen("passwords.txt", "a"); /*if file exists, open it and write our passwords in the end of file*/
        for (i = 0; i < m; ++i) {
            for(j=0;j<n;++j){
                fprintf(file, "%c", lstpw[i][j]);/*printing result into a file*/
            }
            fputs("\n", file);
        }
    }
    fclose(file);
}
