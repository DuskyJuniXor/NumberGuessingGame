#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	
    srand((unsigned)time(NULL));
    int num = rand() % 1000;

    int min = 0, max = 1000;

    int guess_num;

    while(1){
	printf("Please guess a number: ");
	scanf("%d", &guess_num);
	if(guess_num > num && guess_num <= max){
            printf("Your guess is bigger\n");
            max = guess_num;
	}
	if(guess_num < num && guess_num >= min){
            printf("Your guess is smaller\n");
            min = guess_num;
	}
	if(guess_num == num){
            printf("Congratulations! You've guessed it out!\n");
	    break;
	}
    }
    return 0;
}
