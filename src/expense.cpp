#include "../includes/includes.h"

void Expense::setID(int& newID)
{
	expID = newID;
}

void Expense::setDate(std::string& newDate)
{

	Date formattedDate = convertStringToDate(newDate);
	date = formattedDate;
}

void Expense::setDescription(std::string& newDesc)
{
	description = newDesc;
}

void Expense::setAmount(float& newAmount)
{
	amount = newAmount;
}

int Expense::getID() const
{
	return expID;
}

Date Expense::getDate() const
{
	return date;
}
		
std::string Expense::getStrDate() const
{
	std::string strDate = std::to_string(getDate().year) + "-";
	if (getDate().month < 10)
	{
		strDate = strDate + "0" + std::to_string(getDate().month) + "-"; 
	}
	else
	{
		strDate = strDate + std::to_string(getDate().month) + "-";
	}
	if (getDate().day < 10)
	{
		strDate = strDate + "0" + std::to_string(getDate().day); 
	}
	else
	{
		strDate = strDate + std::to_string(getDate().day);
	}

	return strDate;
}

std::string Expense::getDescription() const
{
	return description;
}
		
float Expense::getAmount() const
{
	return amount;
}

std::string Expense::convertToString() const
{
	std::string formattedDate = std::to_string(getDate().year) + "-" + std::to_string(getDate().month) + "-" + std::to_string(getDate().day); 
	std::string newStr = std::to_string(getID()) + "|" + formattedDate + "|" + getDescription() + "|" + std::to_string(getAmount());
	return newStr;
}
		
void Expense::convertFromString(std::string& line)
{
	std::vector<std::string> details;
	std::string word = "";
	for (char& c : line)
	{
		if (c == '|')
		{
			details.push_back(word);
			word = "";
			continue;
		}
		word += c;
	}
	details.push_back(word);

	int newID = std::stoi(details[0]);
	float newAmount = std::stof(details[3]);

	setID(newID);
	setDate(details[1]);
	setDescription(details[2]);
	setAmount(newAmount);
}

