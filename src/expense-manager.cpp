#include "../includes/includes.h"


bool ExpenseManager::getIsChanged() const
{
	return isChanged;
}
		
int ExpenseManager::getExpensesCount() const
{
	return expenses.size();
}
		
void ExpenseManager::createExpenseRecord(std::string description, float amount)
{
	Date today = getToday();
	int id = expenses.back().getID() + 1;
	Expense newExpense(id, today, description, amount);
	expenses.push_back(newExpense);
	std::cout << "Expense added successfully [ID: " << 1 << "]" << std::endl;
}
		
void ExpenseManager::deleteExpenseRecord(int expID)
{

}
		
void ExpenseManager::listExpenseRecords(int month, int year)
{

}
		
void ExpenseManager::summaryOfExpenses(int month, int year)
{

}

void ExpenseManager::showHelper(char* appName)
{
	std::cout << "Usage:" << std::endl;
	std::cout << "    " << appName << " add \"<expense>\" <amount> -- Adds a new expense record." << std::endl;
	std::cout << "    " << appName << " delete <expense-id> -- Deletes an expense record specified by an id.\n" << std::endl;
	std::cout << "    " << appName << " list -- List all the available expense records." << std::endl;
	std::cout << "        " << appName << " list --day <day> -- List all the available expenses belong to a certain day." << std::endl;
	std::cout << "        " << appName << " list --month <month> -- List all the available expenses belong to a certain month." << std::endl;
	std::cout << "        " << appName << " list --year <year> -- List all the available expenses belong to a certain year.\n" << std::endl;
	std::cout << "    " << appName << " summary -- Prints the summary of all the expense records available." << std::endl;
	std::cout << "        " << appName << " summary --day <day> -- Print the summary of all the available expenses belong to a certain day." << std::endl;
	std::cout << "        " << appName << " summary --month <month> -- Print the summary of all the available expenses belong to a certain month." << std::endl;
	std::cout << "        " << appName << " summary --year <year> -- Print the summary of all the available expenses belong to a certain year.\n" << std::endl;
	std::cout << "    " << appName << " help -- Prints this help message." << std::endl;
}

void ExpenseManager::readFromFile()
{
	std::ifstream File(".records");
	if (!File.is_open())
	{
		std::ofstream newFile(".records");
		newFile.close();
		std::ifstream File(".records");
	}
	
	std::string line;

	while (getline(File, line))
	{
		Expense expense;
		expense.convertFromString(line);
		expenses.push_back(expense);
	}

	File.close();
}
		
void ExpenseManager::writeToFile()
{
	std::ofstream File(".records", std::ios::trunc);

	for (Expense expense : expenses)
	{
		File << expense.convertToString() << std::endl;
	}

	File.close();
}

