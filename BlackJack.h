/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: Blackjack bonus assignment
* Last Updated: October 14, 2024
* Description: This program plays a virtual game of Blackjack
*			   between a solo user and a dealer.
*****************************************************************/
#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // rand (), srand ()
#include <time.h> // time ()

#define ACE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define JACK 11
#define QUEEN 12
#define KING 13

/**********************************************************
* Function: print_game_rules()
* Last Updated: 10/13/2024
* Description: Prints out the rules of the game of
*				Blackjack.
* Input Parameters: void
* Returns: nothing
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
void print_game_rules(void);

/**********************************************************
* Function: get_bank_balance()
* Last Updated: 10/9/2024
* Description: Prompts the player for an initial bank
*				balance from which wagering will be added
*				or subtracted.The player entered bank
*				balance(in dollars, i.e.$100.00) is
*				returned.
* Input Parameters: none
* Returns: double
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
double get_bank_balance(void);

/**********************************************************
* Function: adjust_bank_balance()
* Last Updated: 10/9/2024
* Description: If add_or_subtract is 1, then the wager
*				amount is added to the bank_balance.If
*				add_or_subtract is 0, then the wager amount
*				is subtracted from the bank_balance.
*				Otherwise, the bank_balance remains the
*				same.The bank_balance result is returned.
* Input Parameters: double bank_balance, double wager_amount,
*					int add_or_subtract
* Returns: double
* Preconditions: none
* Postconditions: none
* ********************************************************/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

/**********************************************************
* Function: get_wager_amount()
* Last Updated: 9/28/2024
* Description: Prompts the player for a wager on a
*				particular roll. The wager is returned.
* Input Parameters: none
* Returns: double
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
double get_wager_amount(void);

/**********************************************************
* Function: check_wager_amount()
* Last Updated: 10/9/2024
* Description: Checks to see if the wager is within the
*				limits of the player's available balance.
*				If the wager exceeds the player's allowable
*				balance, then 0 is returned; otherwise 1 is
*				returned.
* Input Parameters: double wager, double balance
* Returns: int
* Preconditions: none
* Postconditions: none
* ********************************************************/
int check_wager_amount(double wager, double balance);

/**********************************************************
* Function: prompt_add_to_bank_balance()
* Last Updated: 10/9/2024
* Description: Prompts how many credits to add and check if
*				it is a valid amount.
* Input Parameters: double amount
* Returns: double
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
double prompt_add_to_bank_balance(double amount);

/**********************************************************
* Function: add_to_bank_balance()
* Last Updated: 10/14/2024
* Description: Prompts if user would like to add to bank.
*				If 'y' is entered will run through process
*				to add to bank balance
* Input Parameters: double amount,
*					double current_bank_balance
* Output Parameters: double *initial_bank_balance
* Returns: double
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
double add_to_bank_balance(double* initial_bank_balance, double current_bank_balance);

/**********************************************************
* Function: cash_out()
* Last Updated: 10/14/2024
* Description: Prompts if user would like to cash out.
*				If 'y' is entered will run through process
*				to cash out
* Input Parameters: double current_bank_balance
* Returns: double
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
double cash_out(double current_bank_balance);

/**********************************************************
* Function: print_card()
* Last Updated: 10/11/2024
* Description: Draws random card from deck array and 
*				returns its value. The corresponding card
*				at the index it was drawn from is set to 
*				null. If a null card is drawn, it draws
*				again until a valid card is drawn.
* Input Parameters: int size
* Output Parameters: int deck[]
* Returns: int
* Preconditions: includes standard header stdio.h
*				 includes standard header stdlib.h
* Postconditions: none
* ********************************************************/
int draw_card(int deck[], int size);

/**********************************************************
* Function: print_card()
* Last Updated: 10/11/2024
* Description: Prints input card with custom design
* Input Parameters: int card_num
* Returns: nothing
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void print_card(int card_num);

/**********************************************************
* Function: sum_cards()
* Last Updated: 10/11/2024
* Description: Adds up the value of every card in the
*				input array. Aces are 11 until sum is over
*				21. Kings, queens, and jacks are all added
*				as 10.
* Input Parameters: int cards[], int size
* Returns: int
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
int sum_cards(int cards[], int size);

/**********************************************************
* Function: print_all_cards()
* Last Updated: 10/11/2024
* Description: Prints every card in the input array.
* Input Parameters: int cards[], int size
* Returns: nothing
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void print_all_cards(int cards[], int size);

/**********************************************************
* Function: hit_or_stand()
* Last Updated: 10/11/2024
* Description: Prompts if user would like to hit. Loops
*				while input is not 'y' or 'n'. Returns 1 
*				if 'y', and 0 if 'n'.
* Input Parameters: none
* Returns: int
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
int hit_or_stand(void);

/**********************************************************
* Function: excecute_print_initial_cards()
* Last Updated: 10/14/2024
* Description: Displays each of the first 2 player cards
*				and first dealer card, one at a time.
* Input Parameters: int player_hand[], int dealer_hand[]
*					int dealer_card_sum
* Output Parameters: int* player_card_sum 
* Returns: nothing
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void excecute_print_initial_cards(int player_hand[], int* player_card_sum, int dealer_hand[], int dealer_card_sum);

/**********************************************************
* Function: excecute_hit_or_stand()
* Last Updated: 10/14/2024
* Description: Excecutes loop for each time player hits.
*				Prompts if user would like to hit. If yes,
*				will draw card and ask again. Loop 
*				continues until player decides not to hit
*				or goes over 21. All cards are displayed
*				each iteration.
* Input Parameters: int dealer_hand[], int dealer_card_sum
*					int number_cards_in_hand
* Output Parameters: int deck[], int* player_card_sum 
*					 int player_hand[]
* Returns: nothing
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void excecute_hit_or_stand(int deck[], int player_hand[], int* player_card_sum, int dealer_hand[], int dealer_card_sum, int number_cards_in_hand);

/**********************************************************
* Function: excecute_dealer_draws()
* Last Updated: 10/14/2024
* Description: Excecutes loop for dealer draws. Dealer
*				draws until at or above a sum of 17. Takes
*				int number_cards_in_hand as starting point.
*				All cards are displayed	each iteration.
* Input Parameters: int player_hand[], int player_card_sum
*					int number_cards_in_hand
* Output Parameters: int deck[], int dealer_hand[]
*						int* dealer_card_sum
* Returns: nothing
* Preconditions: includes standard header stdio.h
*				 includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void excecute_dealer_draws(int deck[], int player_hand[], int player_card_sum, int dealer_hand[], int* dealer_card_sum, int number_cards_in_hand);

/**********************************************************
* Function: win_loss_message()
* Last Updated: 10/14/2024
* Description: States explicitly if won, lost, or tie. 
*				Returns 1 if won, 0 if lost, and -1 if tie
* Input Parameters: double current_bank_balance
* Returns: int
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
int win_loss_message(int dealer_card_sum, int player_card_sum, double wager_amount);

/**********************************************************
* Function: shuffle_deck()
* Last Updated: 10/13/2024
* Description: Sets all indeces in the deck array to 
*				regular 52 card deck values - 4 of each 
*				card.
* Input Parameters: none
* Output Parameters: int deck[]
* Returns: nothing
* Preconditions: must be at least size 52 array
* Postconditions: none
* ********************************************************/
void shuffle_deck52(int deck[]);

/**********************************************************
* Function: reset_hand()
* Last Updated: 10/13/2024
* Description: Sets all indeces in the hand array to 0
* Input Parameters: int size
* Output Parameters: int hand[]
* Returns: nothing
* Preconditions: none
* Postconditions: none
* ********************************************************/
void reset_hand(int hand[], int size);

/**********************************************************
* Function: chatter_messages()
* Last Updated: 10/14/2024
* Description: Prints an appropriate message dependent on
*				the number of rolls taken so far by the
*				player, the current balance, and whether or
*				not the player just won his roll.The
*				parameter win_loss_neither indicates the
*				result of the previous roll.
* Input Parameters: int number_rolls, int win_loss_neither,
*					double initial_bank_balance,
*					double current_bank_balance
* Returns: nothing
* Preconditions: includes standard header stdio.h
* Postconditions: none
* ********************************************************/
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);

/**********************************************************
* Function: play_game()
* Last Updated: 10/14/2024
* Description: Runs a game of Blackjack
* Input Parameters: nothing
* Returns: nothing
* Preconditions: includes standard header stdio.h
*					includes local header "BlackJack.h"
* Postconditions: none
* ********************************************************/
void play_game(void);


#endif