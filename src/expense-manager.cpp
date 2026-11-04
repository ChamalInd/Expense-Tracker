#include "../includes/includes.h"

void ExpenseManager::createExpenseRecord(std::string description, float amount)
{
	Date today = getToday();
	int id = expenses.empty() ? 1 : expenses.back().getID() + 1;
	Expense newExpense(id, today, description, amount);
	expenses.push_back(newExpense);
	std::cout << "Expense added successfully [ID: " << id << "]" << std::endl;
}
		
void ExpenseManager::deleteExpenseRecord(int expID)
{
	int index = 0;

	for (Expense& e : expenses)
	{
		if (e.getID() == expID)
		{
			break;
		}
		index++;
	}

	if (expID < 1 || index == expenses.size())
	{
		std::cout << "Enter a correct expense ID." << std::endl;
		return;
	}
	expenses.erase(expenses.begin() + index);
	std::cout << "Expense removed successfully [ID: " << expID << "]" << std::endl;
}
		
void ExpenseManager::listExpenseRecords(int year, int month, int day)
{
	std::vector<Expense> filterredExpenses = filterExpenses(year, month, day);

	if (filterredExpenses.size() < 1)
	{
		std::cout << "No expense records found for given period." << std::endl;
		return;
	}

	int maxLength = getMaximumStringLength(filterredExpenses);
	int length = maxLength + 29;
	
	std::cout << std::left << std::setw(4) << "ID" << std::setw(12) << "Date" << std::setw(maxLength + 3) << "Description" << std::setw(8) << "Amount ($)" << std::endl;

	for (int i = 0; i < length; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;

	for (Expense e : filterredExpenses)
	{
		int id = e.getID();
		std::string date = e.getStrDate();
		std::string desc = e.getDescription();
		std::string amount = formatCurrency(e.getAmount());

		std::cout << std::left << std::setw(4) << id << std::setw(12) << date << std::setw(maxLength + 3) << desc << std::right << std::setw(8) << amount << std::endl;
	}
}
		
void ExpenseManager::summaryOfExpenses(int year, int month, int day)
{
	std::vector<Expense> filterredExpenses = filterExpenses(year, month, day);
	
	if (filterredExpenses.size() < 1)
	{
		std::cout << "No expense records found for given period." << std::endl;
		return;
	}

	float totalExpenses = 0;

	for (Expense& e : filterredExpenses)
	{
		totalExpenses += e.getAmount();
	}

	std::string strTotal = formatCurrency(totalExpenses);

	std::cout << "Total expenses for given period: $ " << strTotal << std::endl; 
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
		int expYear = exp.getDate().year;
		int expMonth = exp.getDate().month;
		int expDay = exp.getDate().day;

		if ((!hasYear || expYear == year) && (!hasMonth || expMonth == month) && (!hasDay || expDay == day))
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

