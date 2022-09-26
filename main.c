#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#pragma warning(disable : 4996)

int balance = 0;
int profit = 0;
int main() {
	printf("\033[35m----------------------------------------------\n");
	printf("      Welcome to the gambling game!\n");
	printf("              No refunds!.\n");
	printf("----------------------------------------------\n\033[37m");
	deposit(1);
}

int deposit(int a) {
	printf("\nHow much do you wish to deposit? (Our direct cut is 5 percent) : ");
	int dep = 0;
	scanf("%d", &dep);
	if(dep < 100 && a == 1) {
		printf("Minimum deposit is 100kr.\n");
		deposit(1);
	}
	else if (dep < 100) {
		printf("Minimum deposit is 100kr.\n");
		start();
	}
	else {
		balance += dep*0.95;
		profit -= dep;
		int depos = dep * 0.95;
		printf("\033[92mSuccessfully deposited %dkr\033[37m\n", depos);
		start();
	}
	return 0;
}

int withdraw() {
	printf("\nYour current balance is %dkr", balance);
	printf("\nHow much do you wish to withdraw? : ");
	int wit = 0;
	scanf("%d", &wit);
	if (wit>balance) {
		printf("\033[31mYou do not have enough money.\033[37m\n");
		start();
	}else if (wit < 100) {
		printf("\033[31mMinimum withdrawal is 100kr.\033[37m\n");
		withdraw();
	} else if (wit <= balance){
		balance -= wit;
		profit += wit;
		printf("\033[92mSuccessfully withdrew %dkr\033[37m\n", wit);
		start();
	}
	return 0;
}

int start() {
	printf("\033[92mYour current balance is %dkr.\033[37m\n", balance);
	printf("Deposit (d)\n");
	printf("Withdraw (w)\n");
	printf("Gamble (g)\n");
	printf("Exit (e)\n");
	char ansr;
	scanf(" %c", &ansr);
	if (ansr == 'e') {
		if (balance > 0) {
			printf("You still have %dkr you can withdraw. You will lose this money if you do not withdraw it.\n", balance);
			printf("Want to withdraw it? (y/n)");
			char ansrExit;
			scanf(" %c", &ansrExit);
			if (ansrExit == 'y') {
				withdraw();
				return 0;
			}
		}
		if (profit > 0) {
			printf("You gained %dkr\n", profit);
		}
		else if (profit < 0) {
			int temp = profit * -1;
			printf("You lost %dkr\n", temp);
		}
		else {
			printf("You didn't lose or make any money.\n");
		}
		printf("It's sad to see you go!\n\n\n\n");
		return 0;
	} else if (ansr == 'd') {
		deposit(0);
	}
	else if (ansr == 'w') {
		withdraw();
	}
	else if (ansr == 'g' || ansr == 'G')
	{
		printf("How much would you like to gamble on a coinflip? (Min=100kr ; Max=1500kr)");
		int gamble = 0;
		scanf("%d", &gamble);
		if (gamble > 1500) {
			printf("Gamble too big, reducing it to 1500kr.");
			gamble = 1500;
		}
		if (gamble > balance) {
			printf("You do not have enough money for that. Want to deposit more? (y/n) ");
			char ansr2;
			scanf(" %c", &ansr2);
			if (ansr2 == 'y') {
				deposit(0);
			}
			else
			{
				start();
			}
		}
		else if (gamble < 100) {
			printf("That is too low!");
			start();
		}
		else {
			printf("Heads (0) or Tails (1)? ");
			int answer;
			scanf("%d", &answer);
			srand(time(0));
			int random;
			int random2;
			random = rand() % 2;
			random2 = rand() % 4;
			printf("Tossing coin...\n");
			Sleep(1000);
			while (random2 > -1)
			{
				printf("...\n");
				Sleep(1000);
				random2 -= 1;
			}
			if (answer == 0 && random == 0) {
				int winnings = gamble * 0.9;
				printf("\033[92mIt was Heads! You won %dkr!\033[37m\n", winnings);
				balance += winnings;
			}
			else if (answer == 1 && random == 1) {
				int winnings = gamble * 0.9;
				printf("\033[92mIt was Tails! You won %dkr!\033[37m\n", winnings);
				balance += winnings;
			}
			else if (random == 0){
				printf("\033[31mIt was Heads. You lost %dkr.\033[37m\n", gamble);
				balance -= gamble;
			}
			else {
				printf("\033[31mIt was Tails. You lost %dkr.\033[37m\n", gamble);
				balance -= gamble;
			}
			start();
		}
	}
}