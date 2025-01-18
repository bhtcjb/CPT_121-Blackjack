/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: Blackjack bonus assignment
* Last Updated: October 14, 2024
* Description: This program plays a virtual game of Blackjack 
*			   between a solo user and a dealer.
*****************************************************************/

// We are designing and building a game of Blackjack. We are making some
// simplifications to our game. We'll not worry about the suit of a card.
// We'll get a start to the implementation and then this will become a bonus
// assignment.

// History:10/14/24 - imported betting system and chatter messages from craps assignment
//					  implemented 3 functions excecute_print_initial_cards(),
//					  excecute_hit_or_stand(), and excecute_dealer_draws() to make 
//					  play_game() look cleaner
//		   10/13/24 - set up a play_game() function and lots of display formatting
//					  and print instructions function from craps assignment and 
//					  several other functions to run the game such as shuffle_deck()
//					  and reset_hand()
//	       10/11/24 - Set up an array as the deck to have real deck odds. 
//					  draw_card() function was changed a bit to fit new system.
//					  Set up functions to hit_or_stand() or to print_all_cards()
//					  at once
// 
//			9/30/24 - We advanced further in our flowchart for Blackjack. We implemented
//                    sum_cards (). We then discussed output parameters and pointers.
//                    This assignment is now officially a bonus one. Please complete
//                    a version of Blackjack with a dealer and one player for
//                    bonus credit. You must start from the code that is provided.
//					  Please send the solution to me via email: aofallon@wsu.edu 
//                    with your solution attached in a zip file. Please remove
//                    the two debug, x64, and/or release folders in the project
//                    before zipping. The assignment is due by Wednesday, 
//                    October 16.
// 
//          9/27/24 - Started drawing a flowchart for Blackjack. Introduced
//                    random number generation using srand () and rand (), which
//                    is very helpful for PA 4 as well. Implemented functions
//                    draw_card () and print_card (). The function print_card ()
//                    is incomplete.

#include "BlackJack.h"

int main(void)
{

	int option = 0;
	
	srand((unsigned int)time(NULL));

	do
	{
		system("cls");
		printf("1. Display rules.\n2. Play game.\n3. Exit.\n");
		scanf("%d", &option);

		switch (option)
		{
		case 1: system("cls");
			print_game_rules();
			break;
		case 2: system("cls");
			play_game();
			break;
		case 3: system("cls");
			printf("Now Exiting ...\n");
			break;
		default: printf("Invalid Input X(\n\n");
			break;
		}

	} while (option <= 1 || option == 2 || option > 3);

	

	return 0;
}