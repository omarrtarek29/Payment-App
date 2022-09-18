#include "server.h"

// ACCOUNTS SIMPLE DATABASE
ST_accountsDB_t accounts[SIZE] = {
	{25000.0, "4630 1200 3412 3451"},
	{55000.0, "4631 1200 3412 3452"},
	{75000.0, "4632 1200 3412 3453"},
	{85000.0, "4633 1200 3412 3454"},
	{2000.0, "4634 1200 3412 3455"}
};


ST_transaction_t transactionDB[SIZE] = {0};


uint8_t accountIndex;



EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	transData->transState = APPROVED;
	accounts[accountIndex].balance -= transData->terminalData.transAmount;

	if (saveTransaction(transData) == SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}

	return APPROVED;
};


EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (uint8_t i = 0; i < 5; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber) == 0)
		{
			accountIndex = i;
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
};

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount <= accounts[accountIndex].balance)
	{
		return SERVER_OK;
	}
	else
	{
		return LOW_BALANCE;
	}
};


EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	static uint32_t seqNum = 11111;  // Let's say it starts with 1111
	static uint8_t i = 0;
	
	transData->transactionSequenceNumber = seqNum;

	if (transData->transState == APPROVED)
	{
		transactionDB[i].cardHolderData = transData->cardHolderData;
		transactionDB[i].terminalData = transData->terminalData;
		transactionDB[i].transactionSequenceNumber = transData->transactionSequenceNumber;
		seqNum++;
		i++;
		return SERVER_OK;
	}
	else
	{
		return SAVING_FAILED;
	}
};

