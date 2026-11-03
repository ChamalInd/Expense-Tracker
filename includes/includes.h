#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstring>
#include <vector>
#include <ctime>
#include <iomanip>

struct Date
{
	int day;
	int month;
	int year;
};


class Expense
{
	private:
		int expID;
		Date date;
		std::string description;
		float amount;
	
	public:
		Expense() {}
		Expense(int i, Date d, std::string de, float a) : expID(i), date(d), description(de), amount(a) {}

		void setID(int& newID);
		void setDate(std::string& newDate);
		void setDescription(std::string& newDesc);
		void setAmount(float& newAmount);

		int getID() const;
		Date getDate() const;
		std::string getDescription() const;
		float getAmount() const;

		std::string convertToString() const;
		void convertFromString(std::string& line);
};


class ExpenseManager
{
	private:
		std::vector<Expense> expenses;
		bool isChanged = false;

	public:
		bool getIsChanged() const;
		int getExpensesCount() const;
		
		void createExpenseRecord(std::string description, float amount);
		void deleteExpenseRecord(int expID);
		void listExpenseRecords(int year, int month, int day);
		void summaryOfExpenses(int year, int month, int day);

		void showHelper(char* appName);
		std::vector<Expense> filterExpenses(int year, int month, int day);

		void readFromFile();
		void writeToFile();
};


void printErrors(int errNo);
Date getToday();
Date convertStringToDate(std::string& date);
int getMaximumStringLength(std::vector<Expense>& vector);

void addExpense(ExpenseManager& em, int argc, char* arguments[]);
void listExpenses(ExpenseManager& em, int argc, char* arguments[]);
void deleteExpenses(ExpenseManager& em, int argc, char* arguments[]);
