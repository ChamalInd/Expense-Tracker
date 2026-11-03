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
		
void ExpenseManager::listExpenseRecords(int year, int month, int day)
{
	std::vector<Expense> filterredExpenses = filterExpenses(year, month, day);
	int maxLength = getMaximumStringLength(filterredExpenses);
	
	std::cout << std::left << std::setw(4) << "ID" << std::left << std::setw(12) << "Date" << std::left << std::setw(maxLength + 3) << "Description" << std::setw(5) << "Amount" << std::endl;

	for (Expense e : filterredExpenses)
	{
		int id = e.getID();
		Date date = e.getDate();
		std::string strDate = std::to_string(date.year) + "-" + std::to_string(date.month) + "-" + std::to_string(date.day);
		std::string desc = e.getDescription();
		float amount = e.getAmount();

		std::cout << std::left << std::setw(4) << id << std::left << std::setw(12) << strDate << std::left << std::setw(maxLength + 3) << desc << std::setw(5) << amount << std::endl;
	}
}
		
void ExpenseManager::summaryOfExpenses(int year, int month, int day)
{
	std::vector<Expense> filterredExpenses = filterExpenses(year, month, day);
	float totalExpenses = 0;

	for (Expense& e : filterredExpenses)
	{
		totalExpenses += e.getAmount();
	}

	std::cout << "Total expenses for given period: " << totalExpenses << " currency unit." << std::endl; 
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

std::vector<Expense> ExpenseManager::filterExpenses(int year, int month, int day)
{
	std::vector<Expense> filteredExpenses;

	bool hasYear = year > 0 ? true : false;
	bool hasMonth = month > 0 ? true : false;
	bool hasDay = day > 0 ? true : false;

	for (Expense& exp : expenses)
	{
		if (hasYear && exp.getDate().year == year) 
		{
			filteredExpenses.push_back(exp);
		}
		else if (!hasYear && !hasMonth && !hasDay)
		{
			filteredExpenses.push_back(exp);
		}
	}

	return filteredExpenses;
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

