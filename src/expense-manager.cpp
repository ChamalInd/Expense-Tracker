#include "../includes/classes.h"


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

void ExpenseManager::showHelper()
{

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

