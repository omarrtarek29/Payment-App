#include "app.h"

uint8_t* stolenCards[SIZE]= { 0 };
uint8_t stolenCardsCounter = 0;

void appStart(void) {

	ST_cardData_t card;
	ST_terminalData_t data;
	ST_transaction_t trans;


	// Stuck on loop until the user enters terminal max amount
	// Do it once at the beginning of the application
	// If you want to change the maximum amount you have to restart the application
	while (1)
	{
		if (setMaxAmount(&data) == TERMINAL_OK)
		{
			system("cls");
			break;
		}
		else
		{
			printf("Invalid amount!\n");
		}
	}
	
	// Program loop
	while (1)
	{
		// Stuck on loop until the user enters card holder name in the correct form
		while (1)
		{
			if (getchar() != 0) {}
			if (getCardHolderName(&card) == CARD_OK)
			{
				break;
			}
			else
			{
				printf("Invalid name!\n");
			}
		}

		// Stuck on loop until the user enters card expiry date in the correct form
		while (1)
		{
			if (getCardExpiryDate(&card) == CARD_OK)
			{
				break;
			}
			else
			{
				printf("Invalid date!\n");
			}
		}

		// Stuck on loop until the user enters card PAN in the correct form
		while (1)
		{
			if (getCardPAN(&card) == CARD_OK)
			{
				break;
			}
			else
			{
				printf("Invalid PAN!\n");
			}
		}

		uint8_t stolenFlag = 0;

		for (size_t i = 0; i < stolenCardsCounter; i++)
		{
			if (strcmp(card.primaryAccountNumber, stolenCards[i]) == 0)
			{
				printf("The card is blocked!\n");
				stolenFlag = 1;
			}
		}

		if (stolenFlag == 1)
		{
			continue;
		}

		// Stuck on loop until the user enters transaction date in the correct form
		while (1)
		{
			if (getTransactionDate(&data) == TERMINAL_OK)
			{
				break;
			}
			else
			{
				printf("Invalid date!\n");
			}
		}

		// Check if the card is expired
		if (isCardExpired(card, data) == EXPIRED_CARD)
		{
			printf("The card is expired!\n");
			break;
		}

		// Stuck on loop until the user enters transaction amount
		while (1)
		{
			if (getTransactionAmount(&data) == TERMINAL_OK)
			{
				break;
			}
			else
			{
				printf("Invalid amount!\n");
			}
		}

		// Check if the transaction amount is below the maximum amount
		if (isBelowMaxAmount(&data) == EXCEED_MAX_AMOUNT)
		{
			printf("Exceeded max amount!\n");
			break;
		}
		/*
		// Check if the account is valid
		if (isValidAccount(&card) == ACCOUNT_NOT_FOUND)
		{
			printf("Account not found!\n");
			break;
		}

		// Check if the amount is available
		if (isAmountAvailable(&data) == LOW_BALANCE)
		{
			printf("Low balance!\n");
			break;
		}
		*/

		trans.cardHolderData = card;
		trans.terminalData = data;

		EN_transState_t state = recieveTransactionData(&trans);

		if (state == APPROVED)
		{
			printf("Transaction approved!\n");
		}
		else if (state == DECLINED_STOLEN_CARD)
		{
			printf("Stolen card!\n");
			stolenCards[stolenCardsCounter++] = card.primaryAccountNumber;
		}
		else if (state == DECLINED_INSUFFECIENT_FUND)
		{
			printf("Insuffecient fund!\n");
		}
		else if (state == INTERNAL_SERVER_ERROR)
		{
			printf("Server error!\n");
		}

	}

	printf("Thank you!\n");
}