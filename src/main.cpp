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

	return 0;
}
