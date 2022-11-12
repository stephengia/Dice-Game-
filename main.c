#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define WON 1
#define LOSE 0

/* This function upper case a char array */
void upperCase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = toupper((str[i]));
        i++;
    }
}

/* This function randomly generates a number (simulates the dice) */
int rollDice()
{
    int dice = rand() % 6 + 1;
    return dice;
}
/* Print out the result menu*/
void diceTable()
{
    printf("==========================================================================================================\n");
    printf("%15s%15s%15s%15s%15s\n", "ROLL NUM", "DICE#1", "DICE#2", "TOTAL ROLL", "POINT MATCH");
    printf("==========================================================================================================\n");
}

int playGame()
{
    int computerTotal = 0;
    int userTotal = 0;
    int dice1 = 0;
    int dice2 = 0;
    int pointMatch = 0;
    int firstRoll= 0;

    do
    {
        dice1 = rollDice();
        dice2 = rollDice();
        userTotal = dice1 + dice2;
       
         computerTotal = rollDice() + rollDice();
         printf("==== YOU ROLLED DICE1: %d and DICE2: %d and TOTAL: %d\n",dice1,dice2,userTotal);
         printf("==== COMPUTER ROLLED TOTAL: %d\n",computerTotal);

        /*If user rolls to 7 or 11*/
        if (userTotal == 7 || userTotal == 11)
        {
            printf("Congratulation you rolled %d and WIN!!!\n", userTotal);
            return WON;
        }

        /*If user rolls to 2 3 12*/
        else if (userTotal == 2 || userTotal == 3 || userTotal == 12)
        {
            printf("Sorry you rolled %d and LOST!!!\n", userTotal);
            return LOSE;
        }
        
        /*If user rolls to point match*/
          else if (userTotal == pointMatch)
        {
            printf("Congratulation you rolled to ther point match %d and WIN!!!!\n", userTotal);
            return WON;
        }

        /*If computer rolls to 7 or 11*/
        else if (computerTotal == 7 || computerTotal == 11)
        {
            printf("Sorry Computer rolled %d and you LOST!!!\n", computerTotal);
            return LOSE;
        }

        /*If computer rolls to 2 3 12*/
        else if (computerTotal == 2 || computerTotal == 3 || computerTotal == 12)
        {
            printf("Congratulation Computer rolled %d and you WIN!!!!\n", computerTotal);
            return WON;
        }
      
        else if (computerTotal == pointMatch)
        {
            printf("Sorry Computer rolled to point match %d and you LOST!!!!\n", computerTotal);
            return LOSE;
        }
        /*If no one wins the round*/
        else
        {
            printf("You rolled %d and Computer rolled %d, begin again!\n", userTotal, computerTotal);
        }
        
        /*Set point match at the first round*/
         if (firstRoll == 0)
        {
            pointMatch = userTotal;
            firstRoll++;
        }
    } while (1);
}

/* Our main function as the entry point of the program */
int main()
{

    char option[20];
    int balance = 20;
    int betAmount = 0;
    int betOrNot = 0;
    int wonAmount = 0;
    int winOrNot = 0;
    int playAgain = 0;

    /*==============  MAIN MENU ==============*/
    do
    {
        printf("Please enter [y or Y] to play Dice or [n or N] to exit: ");
        scanf("%s", option);
        upperCase(option);
        if (!strcmp(option, "N"))
        {
            printf("Programmed by Gia Bao Stephen Tran...\n");
            return EXIT_SUCCESS;
        }
    } while (strcmp(option, "Y"));

    /* ==============  GAME STARTS HERE ==============*/
    do
    {
        /* If player want to bet */
        do
        {
            printf("Would you like to bet? [y/n]: ");
            scanf("%s", option);
            upperCase(option);
            betOrNot = strcmp(option, "Y") == 0 ? 1 : 0;
            if (balance <= 0 && betOrNot == 1)
            {
                printf("You are out of money, can not bet!!!\n");
                /*By making the first char null, strcmpr cannot compare anything*/
                option[0] = '\0';
            }

        } while (strcmp(option, "N") && strcmp(option, "Y"));

        /* In case users want to bet */
        if (betOrNot == 1)
        {
            /* This loop makes sure users enter the right amount of bet */
            do
            {
                printf("You have $%d, minimum bet is $5, you can make %d total bet(s): ", balance, balance / 5);
                scanf("%d", &betAmount);
                if (betAmount <= 0 || betAmount > balance / 5)
                {
                    printf("Bet amount must be within 0-%d\n", balance / 5);
                }
                fflush(stdin);

            } while (betAmount <= 0 || betAmount > balance / 5);

            printf("You bet $%d\n", betAmount * 5);
            winOrNot = playGame();
            if (winOrNot == 1)
            {
                printf("You have won $%d!\n", betAmount * 3 * 5);
                wonAmount += betAmount * 3 * 5;
                balance += wonAmount;
                printf("Your current balance is $%d\n", balance);
            }
            else
            {
                printf("You have lost $%d!\n", betAmount * 5);
                wonAmount -= betAmount * 5;
                balance += wonAmount;
                printf("Your current balance is $%d\n", balance);
            }
        }

        /* In case users do not want to bet */
        else
        {
            playGame();
        }

        /*Prompt user if they want to try playing again*/
        do
        {
            printf("Wanna try your luck again? [y/n]: ");
            scanf("%s", option);
            upperCase(option);
            playAgain = strcmp(option, "Y") == 0 ? 1 : 0;
        } while (strcmp(option, "N") && strcmp(option, "Y"));

    } while (playAgain == 1);
    printf("Programmed by Gia Bao Stephen Tran...\n");
}
