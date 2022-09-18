#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter card holder name: ");
	gets(&cardData->cardHolderName);

	uint8_t cardHolderName_size = strlen(cardData->cardHolderName);

	/*
	* If name is null, less than 20 chars or more than 24 chars return wrong
	* else return ok
	*/
	if (cardData->cardHolderName == NULL ||
		cardHolderName_size < 20 ||
		cardHolderName_size > 24) 
	{
		return WRONG_NAME;
	}
	else 
	{
		return CARD_OK;
	}
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter card expiry date in a format MM/YY: ");
	gets(&cardData->cardExpirationDate);

	uint8_t cardDate_size = strlen(cardData->cardExpirationDate);

	/*
	* Equivalant to
	* if(cardData->cardExpirationDate == NULL ||
	* sizeof(cardData->cardExpirationDate) < 5 ||
	* sizeof(cardData->cardExpirationDate) > 5)
	* If expiration date is not 5 bytes return wrong
	* else return ok
	*/
	if (cardDate_size != 5) 
	{
		return WRONG_EXP_DATE;
	}
	else 
	{
		return CARD_OK;
	}
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter PAN: ");
	gets(&cardData->primaryAccountNumber);

	uint8_t cardPAN_size = strlen(cardData->primaryAccountNumber);

	/*
	* If PAN is null, less than 16 chars or more than 19 chars return wrong
	* else return ok
	*/
	if (cardData->primaryAccountNumber == NULL ||
		cardPAN_size < 16 ||
		cardPAN_size > 19) 
	{
		return WRONG_PAN;
	}
	else 
	{
		return CARD_OK;
	}
}