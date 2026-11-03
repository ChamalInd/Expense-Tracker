#pragma once
#include <iostream>
#include <cstring>
#include <cstring>
#include <vector>
#include <ctime>

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
		void listExpenseRecords(int month, int year);
		void summaryOfExpenses(int month, int year);

		void showHelper();

		void readFromFile();
		void writeToFile();
};
