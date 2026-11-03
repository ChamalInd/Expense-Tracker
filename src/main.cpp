#include "../includes/includes.h"

int main(int argc, char* argv[])
{
	ExpenseManager expense_manager;
	expense_manager.readFromFile();
	expense_manager.writeToFile();
	return 0;
}
