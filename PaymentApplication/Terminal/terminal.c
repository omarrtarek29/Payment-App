#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Enter transaction date in a format DD/MM/YYYY: ");
	gets(&termData->transactionDate);

	uint8_t dateLen = strlen(termData->transactionDate);

	/*
	* Equivalant to
	* if(termData->transactionDate == NULL ||
	* sizeoftermData->transactionDate) < 10 ||
	* sizeof(termData->transactionDate) > 10)
	* or it's in wrong format
	* If expiration date is not 10 bytes return wrong
	* else return ok
	*/
	if (dateLen != 10 ||
		termData->transactionDate[2] != '/'	||
		termData->transactionDate[5] != '/')
	{
		return WRONG_DATE;
	}
	else {
		return TERMINAL_OK;
	}

}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	/*
	* Calculating transaction and expiry date as integers to compare them easily
	*/
	// 09/09/2022
	uint8_t trans_month = ((termData.transactionDate[3] - 48) * 10) + (termData.transactionDate[4] - 48);
	uint8_t trans_year = ((termData.transactionDate[8] - 48) * 10) + (termData.transactionDate[9] - 48);
	uint8_t exp_month = ((cardData.cardExpirationDate[0] - 48) * 10) + (cardData.cardExpirationDate[1] - 48);
	uint8_t exp_year = ((cardData.cardExpirationDate[3] - 48) * 10) + (cardData.cardExpirationDate[4] - 48);

	/*
	* If transaction year equals expiry year, we check if transaction month is less than or equal expiry month
	* Else if trasaction year is less than expiry year, we don't have to check the transaction month
	*/
	if (trans_year == exp_year) {
		if (trans_month < exp_month) {
			return TERMINAL_OK;
		}
	}
	else if (trans_year < exp_year) {
		return TERMINAL_OK;
	}
	else {
		return EXPIRED_CARD;
	}

	return EXPIRED_CARD;
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter transaction amount: ");
	scanf_s("%f", &termData->transAmount);

	if (termData->transAmount > 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_AMOUNT;
	}

}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Enter Maximum transaction amount: ");
	scanf_s("%f", &termData->maxTransAmount);


	if (termData->maxTransAmount > 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_MAX_AMOUNT;
	}

}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}


