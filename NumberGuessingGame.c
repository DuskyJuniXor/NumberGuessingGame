#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char id[50], pwd[21], pwdr[21], text[50];

void menu();
void regist();
void game();
void login();
void clean_stdin();

void clean_stdin(){
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void menu(){
    printf("**Welcome to play Number Guessing Game!**\n");
    printf("login/register and play: press 1\n");
    printf("exit: press 0\n");
    int a = 0;
    scanf("%d", &a);
    clean_stdin();
    if(a){
        printf("-login: press 1\n");
        printf("-register: press 0\n");
        int b;
        scanf("%d", &b);
        clean_stdin();
        if(b) login();
        else regist();
    }else exit(EXIT_FAILURE);
}

void login(){
    printf("login:\n");
    printf("ID: ");
    fgets(id, sizeof(id) - 1, stdin);
    id[strlen(id) - 1] = '\0';
    printf("PWD: ");
    fgets(pwd, sizeof(pwd) - 1, stdin);
    pwd[strlen(pwd) - 1] = '\0';
    strcat(id, pwd);
    strcat(id, "\n");

    int ok = 0;
    FILE *fp = fopen("user.txt", "r");
    if(fp == NULL){
        printf("Failed to open user.txt\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        memset(text, 0, sizeof(text));
        fgets(text, sizeof(text) - 1, fp);
        if(strcmp(id, text) == 0){
            ok = 1;
            break;
        }
    }

    if(ok){
        printf("login succeeded!\n");
    }else{
        printf("login failed\n");
        menu();
    }
    fclose(fp);
}

void regist(){
    printf("register:");
    FILE *fp = fopen("user.txt", "a");
    if(fp == NULL){
        printf("Failed to open user.txt\n");
        exit(EXIT_FAILURE);
    }else{
        id:
        printf("ID(within 20 characters): ");
        fgets(id, sizeof(id) - 1, stdin);
        id[strlen(id) - 1] = '\0';

        if(strlen(id) > 20){
            printf("Illegal id: the length of id must be within 20\n");
            goto id;
        }

        password:
        printf("password(within 20 characters): ");
        fgets(pwd, sizeof(pwd) - 1, stdin);
	pwd[strlen(pwd) - 1] = '\0';
        if(strlen(pwd) > 20){
            printf("Illegal password: the length of password must be within 20\n");
            goto password;
        }

        printf("Repeat password:" );
        fgets(pwdr, sizeof(pwdr) - 1, stdin);
	pwdr[strlen(pwdr) - 1] = '\0';
        if(strcmp(pwd, pwdr) == 0){
            printf("Registed successfully!\n");
            strcat(id, pwd);
            strcat(id, "\n");
            fputs(id, fp);
            
            login();
        }else{
            printf("Error: passwords didn't correspond with each other\n");
            goto password;
        }
    }
}

void game(){

    struct timeval start_time;
    struct timeval end_time;

    srand((unsigned)time(NULL));
    int num = rand() % 1000;

    int min = 0, max = 1000;

    int guess_num, i = 0;

    gettimeofday(&start_time, NULL);
    while(1){
        guess_num = 0;
        printf("Please guess a number: ");
        i++;
        scanf("%d", &guess_num);
        if(guess_num > num && guess_num <= max){
            printf("Your guess is bigger\n");
            max = guess_num;
            printf("range: %d - %d\n", min, max);
        }
        if(guess_num < num && guess_num >= min){
            printf("Your guess is smaller\n");
            min = guess_num;
            printf("range: %d - %d\n", min, max);
        }
        if(guess_num == num){
            gettimeofday(&end_time, NULL);
            printf("Congratulations! You've guessed it out after %d trials and %f seconds!\n", i, (double)(end_time.tv_sec-start_time.tv_sec));
            break;
        }
    }
}

int main(){
    int a;

    menu();

    choice:
    printf("1 Play\n");
    printf("0 Exit\n");
    scanf("%d", &a);
    switch (a){
        case 1:
        game();
        break;
        
        case 0:
        break;
        
        default:
        printf("Invalid choice.\nPlease choose again:\n");
        goto choice;
        break;
    }
    return 0;
}
>>>>>>> dev
