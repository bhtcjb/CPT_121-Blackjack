/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: Blackjack bonus assignment
* Last Updated: October 14, 2024
* Description: This program plays a virtual game of Blackjack
*			   between a solo user and a dealer.
*****************************************************************/
#include "BlackJack.h"

void print_game_rules(void)
{
	printf("Black Jack Game Rules:\n\nAfter placing your bet, the dealer will draw two cards for you and place each face up,"
			"\nand two cards for themselves, placed one face up and one face down.\nYou can then decide to either hit or stand.\n"
			"If you hit, the dealer will draw another card for you and place it face up.\nYou can keep hitting until you either"
			" decide to stand or until the sum of your cards surpasses 21.\nIf you stand before going over, the dealer will flip"
			" over their face-down card\nand begin to draw, trying for a sum that beats yours without going over.\nThe goal of the"
			" game is to have a highest sum of cards on the table without going over 21.\n\n");
	system("pause");
}

double get_bank_balance(void)
{
	double amount = 0;

	do
	{
		printf("Please enter starting credits: $");
		scanf("%lf", &amount);

		//check validaty - amount must be greater than zero up to two decimal places
		if (amount <= 0 || amount * 100 != (int)(amount * 100))
		{
			printf("Invalid Amount\n");
		}
	} while (amount <= 0 || amount * 100 != (int)(amount * 100));

	return amount;
}

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	return (1 == add_or_subtract) * (bank_balance + wager_amount) +			// if add_or_subtract is 1, balance and wager are added
		(0 == add_or_subtract) * (bank_balance - wager_amount) +			// if add_or_subtract is 0, wager is subtracted from balance
		!(1 == add_or_subtract || 0 == add_or_subtract) * bank_balance;		// if add_or_subtract is anything else balance stays the same
}

double get_wager_amount(void)
{
	double amount = 0;

	printf("Please enter bet: $");
	scanf("%lf", &amount);

	return amount;
}

int check_wager_amount(double wager, double balance)
{
	// checks if wager is not greater than balance, if wager is not less than 0, and if wager is not beyond two decimal places
	// all three must be true to return 1
	return (int)(wager <= balance && wager >= 0 && (wager * 100) == (int)(wager * 100));
}

double prompt_add_to_bank_balance(double amount)
{
	printf("\n\n");

	// prompts to add to bank balance and keeps asking until amount is greater than zero and is within two decimal places
	do
	{
		printf("How many credits would you like to add? $");
		scanf("%lf", &amount);
		if (amount < 0 || amount * 100 != (int)(amount * 100))
		{
			printf("Invalid Amount\n");
		}
	} while (amount < 0 || amount * 100 != (int)(amount * 100));
	system("cls");
	return amount;
}

double add_to_bank_balance(double* initial_bank_balance, double current_bank_balance)
{
	char answer = 'n';
	double amount = 0;

	printf("Would you like to add more credits?\ny or n? ");
	scanf(" %c", &answer);
	if ('y' == answer)
	{
		// if yes runs funtion asking to add to bank balance
		amount = prompt_add_to_bank_balance(amount);

		current_bank_balance += amount;
		*initial_bank_balance += amount; // also adds to initial amount for the chatter messages to make sense
		printf("You have added $%.2lf to your bank balance\n\n", amount);
		system("pause");

	}

	return current_bank_balance;
}

double cash_out(double current_bank_balance)
{
	char answer = 'n';

	printf("Would you like to cash out?\ny or n? ");
	scanf(" %c", &answer);
	if ('y' == answer)
	{
		// if yes sets bank balance to 0 to kick it out of the run game loop
		system("cls");
		printf("You cashed out with $%.2lf!\n\n\n\n\n", current_bank_balance);
		current_bank_balance = 0;
		system("pause");
	}
	return current_bank_balance;
}

int draw_card(int deck[], int size) 
{
	int index = rand() % size;
	int card = NULL;
	// draws again if card drawn was null
	while (deck[index] == NULL)
	{
		index = rand() % size;
	}
	
	card = deck[index];
	// sets card to null if drawn to indicate no card
	deck[index] = NULL;

	return card;
}

void print_card(int card_num)
{
	switch (card_num)
	{
	case ACE: printf("_______\n|A    |\n|     |\n|  *  |\n|     |\n|    A|\n-------\n"); 
		break;
	case TWO: printf("_______\n|2    |\n|  *  |\n|     |\n|  *  |\n|    2|\n-------\n");
		break;
	case THREE: printf("_______\n|3    |\n|  *  |\n|  *  |\n|  *  |\n|    3|\n-------\n");
		break;
	case FOUR: printf("_______\n|4    |\n| * * |\n|     |\n| * * |\n|    4|\n-------\n");
		break;
	case FIVE: printf("_______\n|5    |\n| * * |\n|  *  |\n| * * |\n|    5|\n-------\n");
		break;
	case SIX: printf("_______\n|6    |\n| * * |\n| * * |\n| * * |\n|    6|\n-------\n");
		break;
	case SEVEN: printf("_______\n|7    |\n|* * *|\n|  *  |\n|* * *|\n|    7|\n-------\n");
		break;
	case EIGHT: printf("_______\n|8    |\n|* * *|\n| * * |\n|* * *|\n|    8|\n-------\n");
		break;
	case NINE: printf("_______\n|9    |\n|* * *|\n|* * *|\n|* * *|\n|    9|\n-------\n");
		break;
	case TEN: printf("_______\n|10   |\n|** **|\n| * * |\n|** **|\n|   10|\n-------\n");
		break;
	case JACK: printf("_______\n|J    |\n|  o ||\n| -|-||\n| / \\ |\n|    J|\n-------\n");
		break;
	case QUEEN: printf("_______\n|Q    |\n| (o)*|\n| -|-||\n| / \\||\n|    Q|\n-------\n");
		break;
	case KING: printf("_______\n|K _  |\n| <o>*|\n| -|-||\n| / \\||\n|    K|\n-------\n");
		break;
	default: printf("X(\n");
		break;
	}
}

int sum_cards(int cards[], int size)
{
	int sum = 0,
		num_aces = 0;

	for (int i = 0; i < size; ++i)
	{
		switch (cards[i])
		{
		case ACE: sum += 11; // ace is 11 by default
			++num_aces;
			break;
		case JACK: sum += 10; // jack queen and king are all give a value of 10
			break;
		case QUEEN: sum += 10;
			break;
		case KING: sum += 10;
			break;
		default: sum += cards[i]; // all other cards are just their number
			break;
		}
	}
	// if over 21 aces will become 1's until under 21
	while (sum > 21 && num_aces > 0)
	{
		sum -= 10;
		--num_aces;
	}
	
	return sum;
}

void print_all_cards(int cards[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (cards[i] != 0)
		{
			print_card(cards[i]);
		}
	}
}

int hit_or_stand(void)
{
	int hit = -1;
	char selection = 'n';

	// promt if user want to hit and keeps asking until they enter y or n
	do
	{
		printf("Would you like to hit?\ny or n? ");
		scanf(" %c", &selection);

		if (selection != 'n' && selection != 'y')
		{
			printf("Invalid Selection X(\n");
		}
	} while (selection != 'n' && selection != 'y');

	if (selection == 'y')
	{
		hit = 1;
	}
	else if (selection == 'n')
	{
		hit = 0;
	}

	return hit;
}

void excecute_print_initial_cards(int player_hand[], int* player_card_sum, int dealer_hand[], int dealer_card_sum)
{
	// shows each card drawn one at a time
	// first player card shown
	printf("Player cards\n");
	print_card(player_hand[0]);
	printf("player sum: %d\n\n", *player_card_sum);
	system("pause");
	system("cls");

	// first dealer and player card shown
	printf("Player cards\n");
	print_card(player_hand[0]);
	printf("player sum: %d\n\n", *player_card_sum);
	printf("Dealer cards\n");
	print_card(dealer_hand[0]);
	printf("dealer sum: %d\n\n", dealer_card_sum);
	system("pause");
	system("cls");
	*player_card_sum = sum_cards(player_hand, 9);

	// first two player cards and first dealer card shown
	printf("Player cards\n");
	print_card(player_hand[0]);
	print_card(player_hand[1]);
	printf("player sum: %d\n\n", *player_card_sum);
	printf("Dealer cards\n");
	print_card(dealer_hand[0]);
	printf("dealer sum: %d\n\n", dealer_card_sum);
}

void excecute_hit_or_stand(int deck[], int player_hand[], int* player_card_sum, int dealer_hand[], int dealer_card_sum, int number_cards_in_hand)
{
	int hit = -1,
		index = number_cards_in_hand;
	do
	{
		hit = hit_or_stand();
		// if hit draw card
		if (hit)
		{
			player_hand[index] = draw_card(deck, 52);
			++index;
		}

		*player_card_sum = sum_cards(player_hand, 9);

		// displays cards each iteration
		system("cls");
		printf("Player cards\n");
		print_all_cards(player_hand, 9);
		printf("player sum: %d\n\n", *player_card_sum);
		printf("Dealer cards\n");
		print_card(dealer_hand[0]);
		printf("dealer sum: %d\n\n", dealer_card_sum);



	} while (hit && *player_card_sum <= 21);
}

void excecute_dealer_draws(int deck[], int player_hand[], int player_card_sum, int dealer_hand[], int* dealer_card_sum, int number_cards_in_hand)
{
	int index = number_cards_in_hand;

	// dealer flips face-down card which was drawn at begining
	system("cls");
	print_all_cards(player_hand, 9);
	printf("player sum: %d\n\n", player_card_sum);
	printf("Dealer cards\n");
	print_card(dealer_hand[0]);
	print_card(dealer_hand[1]);
	*dealer_card_sum = sum_cards(dealer_hand, 9);
	printf("dealer sum: %d\n\n", *dealer_card_sum);
	system("pause");
	system("cls");

	// loops dealer draws until 17 or over
	while (*dealer_card_sum < 17 && *dealer_card_sum <= player_card_sum)
	{
		printf("Player cards\n");
		print_all_cards(player_hand, 9);
		printf("player sum: %d\n\n", player_card_sum);
		dealer_hand[index] = draw_card(deck, 52);
		++index;
		printf("Dealer cards\n");
		print_all_cards(dealer_hand, 9);
		*dealer_card_sum = sum_cards(dealer_hand, 9);
		printf("dealer sum: %d\n\n", *dealer_card_sum);
		system("pause");
		system("cls");
	}
}

int win_loss_message(int dealer_card_sum, int player_card_sum, double wager_amount)
{
	int win_loss_tie = -1;
	if (dealer_card_sum > 21 || (player_card_sum > dealer_card_sum && player_card_sum <= 21))
	{
		win_loss_tie = 1;
		printf("You won!\n\n");
		system("pause");
		system("cls");
		printf("+$%.2lf\n", wager_amount);
	}
	else if (player_card_sum > 21 || (player_card_sum < dealer_card_sum && dealer_card_sum <= 21))
	{
		win_loss_tie = 0;
		printf("You lost!\n\n");
		system("pause");
		system("cls");
		printf("-$%.2lf\n", wager_amount);
	}
	else
	{
		printf("Tie!\n\n");
		system("pause");
		system("cls");
		printf("-$0\n");
	}

	return win_loss_tie;
}

void shuffle_deck52(int deck[])
{
	int shuffled_deck[52] = { ACE,ACE,ACE,ACE,TWO,TWO,TWO,TWO,THREE,THREE,THREE,THREE,
							FOUR,FOUR,FOUR,FOUR,FIVE,FIVE,FIVE,FIVE,SIX,SIX,SIX,SIX,
							SEVEN,SEVEN,SEVEN,SEVEN,EIGHT,EIGHT,EIGHT,EIGHT,NINE,NINE,
							NINE,NINE,TEN,TEN,TEN,TEN,JACK,JACK,JACK,JACK,QUEEN,QUEEN,
							QUEEN,QUEEN,KING,KING,KING,KING };
	// sets each index back to the original deck
	for (int i = 0; i < 52; ++i)
	{
		deck[i] = shuffled_deck[i];
	}

}

void reset_hand(int hand[], int size)
{
	// sets every index in hand to 0 to indicate no card
	for (int i = 0; i < size; ++i)
	{
		hand[i] = 0;
	}
}

void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
	int random_factor = rand() % 4 + 1;


	if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 1 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("I think your losing your edge.\n");
			break;
		case 2: printf("I mean that's nothing for you.\n");
			break;
		case 3:	printf("Finally a bust!");
			break;
		case 4: printf("Never saw that one coming.\n");
			break;
		}
	}
	else if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 1 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("How do you just keep on winning?\n");
			break;
		case 2: printf("You must be cheating at this point.\n");
			break;
		case 3: printf("You can't be getting away with this.\n");
			break;
		case 4: printf("This is just robbery.\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 1 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("It's ok, your still doing \"mostly\" good.\n");
			break;
		case 2: printf("Luck's already wearing off.\n");
			break;
		case 3: printf("Dang you had it.\n");
			break;
		case 4: printf("No big deal. Just brush it off.\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 1 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Must be beginners luck.\n");
			break;
		case 2: printf("Wow you're so good at that.\n");
			break;
		case 3: printf("No way you can keep this up.\n");
			break;
		case 4: printf("Just keep makin' it work.\n");
			break;
		}
	}
	else if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 0.7 &&
		(current_bank_balance / initial_bank_balance) <= 1 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Less than average performance.\n");
			break;
		case 2: printf("You can do better than this.\n");
			break;
		case 3: printf("Skill issue.\n");
			break;
		case 4: printf("I thought you were better than this.\n");
			break;
		}
	}
	else if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 0.7 &&
		(current_bank_balance / initial_bank_balance) <= 1 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Now that's more like it.\n");
			break;
		case 2: printf("I see your luck turning around!\n");
			break;
		case 3: printf("You couldn't have at least wagered more?\n");
			break;
		case 4: printf("Good job this time.\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 0.7 &&
		(current_bank_balance / initial_bank_balance) <= 1 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Go again! What do you have to lose?\n");
			break;
		case 2: printf("Maybe try blowing on the cards.\n");
			break;
		case 3: printf("If only you were just better at the game.\n");
			break;
		case 4: printf("Keep trying I believe in you.\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 0.7 &&
		(current_bank_balance / initial_bank_balance) <= 1 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Just try to keep you're head above water.\n");
			break;
		case 2: printf("Now you're making your mother proud!\n");
			break;
		case 3: printf("Having a good time?\n");
			break;
		case 4: printf("If you keep playing, you might win more like that!\n");
			break;
		}
	}
	else if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 0.15 &&
		(current_bank_balance / initial_bank_balance) <= 0.7 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Oh how you've fallen.\n");
			break;
		case 2: printf("It only gets worse from here.\n");
			break;
		case 3: printf("You're in deep stuff now.\n");
			break;
		case 4: printf("I don't think you'll make it out of this one.\n");
			break;
		}
	}
	else if (number_rolls > 5 && (current_bank_balance / initial_bank_balance) > 0.15 &&
		(current_bank_balance / initial_bank_balance) <= 0.7 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("I'm starting to believe in you.\n");
			break;
		case 2: printf("You won't be as lucky next time.\n");
			break;
		case 3: printf("Setting a new trend I see.\n");
			break;
		case 4: printf("It seems you think you're gonna make it out of this hole.\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 0.15 &&
		(current_bank_balance / initial_bank_balance) <= 0.7 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("This is the beginning of your downfall.\n");
			break;
		case 2: printf("A few more like that and you'll be toast.\n");
			break;
		case 3: printf("Uh ohhhh ...\n");
			break;
		case 4: printf("It's possible to improve! You just need more practice!\n");
			break;
		}
	}
	else if (number_rolls <= 5 && (current_bank_balance / initial_bank_balance) > 0.15 &&
		(current_bank_balance / initial_bank_balance) <= 0.7 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Maybe keep doing that.\n");
			break;
		case 2: printf("If you just do that more, things might actually look good for you.\n");
			break;
		case 3: printf("See what happens when you actually try.\n");
			break;
		case 4: printf("Wow, you actually won something.\n");
			break;
		}
	}
	else if (number_rolls <= 10 && (current_bank_balance / initial_bank_balance) <= 0.15 &&
		(current_bank_balance / initial_bank_balance) > 0 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("You just love to waist your money!\n");
			break;
		case 2: printf("Big loser I see.\n");
			break;
		case 3: printf("You might just want to quit now.\n");
			break;
		case 4: printf("You're already running out of money?\n");
			break;
		}
	}
	else if (number_rolls <= 10 && (current_bank_balance / initial_bank_balance) <= 0.15 &&
		(current_bank_balance / initial_bank_balance) > 0 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("There might just be hope.\n");
			break;
		case 2: printf("I guess you do win sometimes.\n");
			break;
		case 3: printf("And this is why we stay optimistic.\n");
			break;
		case 4: printf("Maybe there's still life left in you\n");
			break;
		}
	}
	else if (number_rolls > 10 && (current_bank_balance / initial_bank_balance) <= 0.15 &&
		(current_bank_balance / initial_bank_balance) > 0 && 0 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Please stop. I cannot keep feeding your gambling addiction.\n");
			break;
		case 2: printf("As a good friend, I worry for you. Please go home, I'm begging you.\n");
			break;
		case 3: printf("Your spouse is going to be upset. Please get help. Do it for your children.\n");
			break;
		case 4: printf("French Guy: Wee wee sibuplet!\n");
			break;
		}
	}
	else if (number_rolls > 10 && (current_bank_balance / initial_bank_balance) <= 0.15 &&
		(current_bank_balance / initial_bank_balance) > 0 && 1 == win_loss_neither)
	{
		switch (random_factor)
		{
		case 1: printf("Please make this you're last one. You're addicted.\n");
			break;
		case 2: printf("Don't let this win cause you to relapse. You have a problem.\n");
			break;
		case 3: printf("Quit while your ahead. Your family will appriciate it.\n");
			break;
		case 4: printf("I understand you just won, but this has gone on long enough. Go see your kids.\n");
			break;
		}
	}
	else if (!(1 == win_loss_neither || 0 == win_loss_neither))
	{
		switch (random_factor)
		{
		case 1: printf("At least you didn't lose!\n");
			break;
		case 2: printf("That was a close one!\n");
			break;
		case 3: printf("You could have won ... but ... didn't.\n");
			break;
		case 4: printf("What's even the point?!\n");
			break;
		}

	}
	else
	{
		printf("Out of Money :(\n");
		switch (random_factor)
		{
		case 1: printf("You are today's big loser. L L L L\n");
			break;
		case 2: printf("How can you fail so hard?\n");
			break;
		case 3: printf("Pitiful ...\n");
			break;
		case 4: printf("Why would you even play if you're gonna do that horribly.\n");
			break;
		}


	}
}

void play_game(void)
{
	int p_hand[9] = { 0 },
		d_hand[9] = { 0 },
		p_card_sum = 0,
		d_card_sum = 0,
		plays = 0,
		wager_check = 0,
		win = -1,
		deck[52] = { ACE,ACE,ACE,ACE,TWO,TWO,TWO,TWO,THREE,THREE,THREE,THREE,
					FOUR,FOUR,FOUR,FOUR,FIVE,FIVE,FIVE,FIVE,SIX,SIX,SIX,SIX,
					SEVEN,SEVEN,SEVEN,SEVEN,EIGHT,EIGHT,EIGHT,EIGHT,NINE,NINE,
					NINE,NINE,TEN,TEN,TEN,TEN,JACK,JACK,JACK,JACK,QUEEN,QUEEN,
					QUEEN,QUEEN,KING,KING,KING,KING };
	double balance = 0,
		initial_balance = 0,
		wager_amount = 0;

	system("cls");
	printf("Let's get started!\n\n");
	system("pause");
	system("cls");

	//get initail balance
	balance = get_bank_balance();
	initial_balance = balance;
	system("cls");
	
	// plays while player still has money or decides to cash out
	while (balance > 0)
	{
		printf("Your current bank balance is $%.2lf\n\n", balance);
		system("pause");
		system("cls");

		//count number rounds played this game
		++plays;
		printf("Game %d:\n\n", plays);

		//prompt bet and keeps asking until wager is checked to be valid
		do
		{
			wager_amount = get_wager_amount();
			wager_check = check_wager_amount(wager_amount, balance);
			if (wager_check != 1)
			{
				printf("Invalid Amount\n");
			}
		} while (wager_check != 1);

		system("cls");
		printf("You are betting $%.2lf\n\n", wager_amount);
		system("pause");
		system("cls");

		// draw the initial 2 cards for player 1
		p_hand[0] = draw_card(deck, 52);
		p_card_sum = sum_cards(p_hand, 9);
		d_hand[0] = draw_card(deck, 52);
		d_card_sum = sum_cards(d_hand, 9); //calculates dealer sum before drawing second card
		p_hand[1] = draw_card(deck, 52);
		d_hand[1] = draw_card(deck, 52);
		

		// print the cards
		excecute_print_initial_cards(p_hand, &p_card_sum, d_hand, d_card_sum);

		
		// prompt hit or stand
		excecute_hit_or_stand(deck, p_hand, &p_card_sum, d_hand, d_card_sum, 2);

		system("pause");
		system("cls");

		// if player doesn't go over dealer starts drawing
		if (p_card_sum <= 21)
		{
			excecute_dealer_draws(deck, p_hand, p_card_sum, d_hand, &d_card_sum, 2);
		}

		// display win loss or tie
		win = win_loss_message(d_card_sum, p_card_sum, wager_amount);

		balance = adjust_bank_balance(balance, wager_amount, win); 
		chatter_messages(plays, win, initial_balance, balance);

		printf("\n\n");
		system("pause");
		system("cls");

		// prompts user if they would like to cash out
		if (0 < balance)
		{

			printf("Your current bank balance is $%.2lf\n\n", balance);

			balance = cash_out(balance);

		}

		// prompts user if they would like to add to bank balance
		if (0 < balance)
		{
			system("cls");
			printf("Your current bank balance is $%.2lf\n\n", balance);

			balance = add_to_bank_balance(&initial_balance, balance);
			system("cls");
		}
		
		// reset everything that needs it
		reset_hand(p_hand, 9);
		reset_hand(d_hand, 9);
		shuffle_deck52(deck);
		p_card_sum = 0;
		d_card_sum = 0;
	}
	
}