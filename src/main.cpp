#include "../includes/includes.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printErrors(1);
		return 0;
	}

	ExpenseManager expense_manager;
	expense_manager.readFromFile();

	if (strcmp(argv[1], "add") == 0)
	{
		addExpense(expense_manager, argc, argv);
		expense_manager.writeToFile();
	}
	else if (strcmp(argv[1], "list") == 0 || strcmp(argv[1], "summary") == 0)
	{
		listExpenses(expense_manager, argc, argv);
	}
	else if (strcmp(argv[1], "delete") == 0)
	{
		deleteExpenses(expense_manager, argc, argv);
		expense_manager.writeToFile();
	}
	else if (strcmp(argv[1], "help") == 0)
	{
		expense_manager.showHelper(argv[0]);
	}

	return 0;
}
