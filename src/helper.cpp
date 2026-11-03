#include "../includes/includes.h"

void listExpenses(ExpenseManager& em, int argc, char* arguments[])
{
	int year = 0;
	int month = 0;
	int day = 0;

	if (argc == 2)
	{
	}
	if (strcmp(arguments[1], "list") == 0)
	{
		em.listExpenseRecords(year, month, day);
	}
	else
	{
		em.summaryOfExpenses(year, month, day);
	}
}

void addExpense(ExpenseManager& em, int argc, char* arguments[])
{
	if (argc < 4)
	{
		printErrors(2);
		return;
	}
	std::string desc = arguments[2];
	float amount = 0;
	try
	{
		amount = atof(arguments[3]);
	}
	catch (int errCode)
	{
		printErrors(2);
		return;
	}

	em.createExpenseRecord(desc, amount);
}


void printErrors(int errNo)
{
	switch (errNo)
	{
		case 1:
			std::cout << "Use help command to print the help message." << std::endl;
			break;
		case 2:
			std::cout << "Incorrect argument format for the current operation.\nUse help command see the correct formatting." << std::endl;
			break;
	}
}

int getMaximumStringLength(std::vector<Expense>& vector)
{
	int length = 0;

	for (Expense& e : vector)
	{
		if (e.getDescription().length() > length)
		{
			length = e.getDescription().length();
		}
	}

	return length;
}

Date getToday()
{
	time_t timestamp = time(NULL);
	struct tm datetime = *localtime(&timestamp);
	char date[50];
	std::strftime(date, 50, "%Y-%m-%d", &datetime);
	std::string strDate(date);

	Date today = convertStringToDate(strDate);
	return today;
}

Date convertStringToDate(std::string& date)
{
	Date formattedDate;
	std::vector<int> dateItems;
	std::string word = "";

	for (char& c : date)
	{
		if (c == '-')
		{
			dateItems.push_back(std::stoi(word));
			word = "";
			continue;
		}
		word += c;
	}
	dateItems.push_back(stoi(word));
	
	formattedDate.day = dateItems[2];
	formattedDate.month = dateItems[1];
	formattedDate.year = dateItems[0];

	return formattedDate;
}
