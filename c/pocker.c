#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// prototyping

void printGreeting();
int getBet();

char getRank(int rank);
char getSuit(int suit);

void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand
(
    int cardRank[], int cardSuit[],
    int finalRank[], int finalSuit[],
    int ranksInHand[], int suitsInHand[]
);

int analyzeHand(int ranksHand[], int suitsHand[]);

int main(void)
{
    int bet;
    int bank = 100;
    int cardRank[5];
    int cardSuit[5];

    int finalRank[5];
    int finalSuit[5];

    int ranksInHand[13];
    int suitsInHand[4];

    int winnings;
    time_t t;
    char suit, rank, stillPlay;

    int i;

    printGreeting();
    do
    {
        bet = getBet();
        srand(time(&t));
        getFirstHand(cardRank, cardSuit);
        printf("Your five cards: \n");

        for (i = 0; i < 5; i += 1)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }

        for (i = 0; i < 4; i += 1)
        {
            suitsInHand[i] = 0;
        }

        for (i = 0; i < 13; i += 1)
        {
            ranksInHand[i] = 0;
        }

        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksInHand, suitsInHand);
        printf("Your final five cards: \n");
        for (i = 0; i < 5; i += 1)
        {
            suit = getSuit(finalSuit[i]);
            rank = getRank(finalRank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }

        winnings = analyzeHand(ranksInHand, suitsInHand);
        printf("You won %d!\n", bet*winnings);
        bank = bank - bet + (bet*winnings);
        printf("\nYour bank is now %d.\n", bank);
        printf("\nDo you want play again? ");
        scanf(" %c", &stillPlay);
    } while (toupper(stillPlay) == 'Y');
    return;
}

void printGreeting()
{
    printf("*****************************************************************\n");
    printf("\n\nWelcome! Wilkommen! Bonjure!\n\n");
    printf("\tHome of Pocker\n\n");
    printf("*****************************************************************\n");
    printf("Here are some funny rules:\n");
    printf("You have 100 baks in your pocket and you start by making a bet from 1 to 5 baks.");
    printf("\nYou are dealt 5 cards, and you then choose wich cards to keep or discard.\n");
    printf("You want to make the best possible hand.\n");
    printf("\nHere is the table for winnings (assuming a bet of 1 baks):");
    printf("\nPair\t\t\t\t1 baks");
    printf("\nTwo Pairs\t\t\t2 baks");
    printf("\nThree of a kind\t\t\t3 baks");
    printf("\nStraight\t\t\t4 baks");
    printf("\nFlush\t\t\t\t5 baks");
    printf("\nFull House\t\t\t8 baks");
    printf("\nFour of a Kind\t\t\t10 baks");
    printf("\nStraight Flush\t\t\t20 baks");
    printf("\n\nHave fun!\n\n");
}

void getFirstHand(int cardRank[], int cardSuit[])
{
    int i, j;
    int cardDup;

    for (i = 0; i < 5; i += 1)
    {
        cardDup = 0;
        do
        {
            cardRank[i] = (rand() % 13);
            cardSuit[i] = (rand() % 4);

            for (j = 0; j < i; j += 1)
            {
                if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j]))
                {
                    cardDup = 1;
                }
            }
        } while (cardDup == 1);
    }
}

char getSuit(int suit)
{
    switch (suit)
    {
        case 0:
            return('c');
        case 1:
            return('d');
        case 2:
            return('h');
        case 3:
            return('s');
    }
}

char getRank(int rank)
{
    switch (rank)
    {
        case 0:
            return('A');
        case 1:
            return('2');
        case 2:
            return('3');
        case 3:
            return('4');
        case 4:
            return('5');
        case 5:
            return('6');
        case 6:
            return('7');
        case 7:
            return('8');
        case 8:
            return('9');
        case 9:
            return('T');
        case 10:
            return('J');
        case 11:
            return('Q');
        case 12:
            return('K');
    }
}

int getBet()
{
    int bet;
    do
    {
        printf("How much do you want to bet? (Enter a number 1 to 5, or 0 to quit the game): ");
        scanf(" %d", &bet);
        if (bet >= 1 && bet <= 5)
        {
            return(bet);
        }
        else if (bet == 0)
        {
            exit(1);
        }
        else
        {
            printf("\n\nPlease enter a bet from 1-5 or 0 to quit the game.\n");
        }
    } while ((bet < 0) || (bet > 5));
}

int analyzeHand(int ranksInHand[], int suitsInHand[])
{
    int num_consec = 0;
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;

    for (suit = 0; suit < 4; suit += 1)
    {
        if (suitsInHand[suit] == 5)
        {
            flush = TRUE;
        }
    }
    rank = 0;
    while (ranksInHand[rank] == 0)
    {
        rank += 1;
    }

    for (; rank < 13 && ranksInHand[rank]; rank += 1)
    {
        num_consec += 1;
    }

    if (num_consec == 5)
    {
        straight = TRUE;
    }

    for (rank = 0; rank < 13; rank += 1)
    {
        if (ranksInHand[rank] == 4)
        {
            four = TRUE;
        }
        if (ranksInHand[rank] == 3)
        {
            three = TRUE;
        }
        if (ranksInHand[rank] == 2)
        {
            pairs += 1;
        }
    }

    if (straight && flush)
    {
        printf("Straight flush\n\n");
        return (20);
    }
    else if (four)
    {
        printf("Four of a Kind\n\n");
        return (10);
    }
    else if (three && pairs == 1)
    {
        printf("Full House\n\n");
        return (8);
    }
    else if (flush)
    {
        printf("Flush\n\n");
        return (5);
    }
    else if (straight)
    {
        printf("Straight\n\n");
        return (4);
    }
    else if (three)
    {
        printf("Three\n\n");
        return (3);
    }
    else if (pairs == 2)
    {
        printf("Two Pairs\n\n");
        return (2);
    }
    else if (pairs == 1)
    {
        printf("Pairs\n\n");
        return (1);
    }
    else
    {
        printf("High Card\n\n");
        return (0);
    }
}

void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksInHand[], int suitsInHand[])
{
    int i, j, cardDup;
    char suit, rank, ans;

    for (i = 0; i < 5; i += 1)
    {
        suit = getSuit(cardSuit[i]);
        rank = getRank(cardRank[i]);
        printf("Do you want to keep card #%d: %c%c?", i + 1, rank, suit);
        printf("\nPlease answer (Y/N): ");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            finalRank[i] = cardRank[i];
            finalSuit[i] = cardSuit[i];
            ranksInHand[finalRank[i]] += 1;
            suitsInHand[finalSuit[i]] += 1;
            continue;

        }
        else if (toupper(ans) == 'N')
        {
            cardDup = 0;
            do
            {
                cardDup = 0;
                finalRank[i] = (rand() % 13);
                finalSuit[i] = (rand() % 4);

                for (j = 0; j < 5; j += 1)
                {
                    if ((finalRank[i] == cardRank[j]) && (finalSuit[i] == cardSuit[j]))
                    {
                        cardDup = 1;
                    }
                }
                for (j = 0; j < i; j += 1)
                {
                    if ((finalRank[i] == finalRank[j]) && (finalSuit[i] == finalSuit[j]))
                    {
                        cardDup = 1;
                    }
                }
            } while (cardDup == 1);
            ranksInHand[finalRank[i]] += 1;
            suitsInHand[finalSuit[i]] += 1;
        }
    }
}
