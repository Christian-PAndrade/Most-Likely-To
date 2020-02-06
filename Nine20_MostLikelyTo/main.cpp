#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <iomanip>

void addToMap(std::map<std::string, int>& map, std::string key);
void getResults(std::map<std::string, int>& map, std::vector<std::string>& resultsVec);
void getInput(std::map<std::string, int>& map, std::vector<std::string>& resultsVec, int& qNum); 
std::string getNumAsString(int num);

int main() {
	// Maps
	std::map<std::string, int> question;

	// Result vec
	std::vector<std::string> resultsVec;

	std::cout << "Most Likely to!" << std::endl
		<< "Enter 10 names or 0 to go to the next question" << std::endl
		<< "If you make a mistake enter 0 and then follow prompt" << std::endl
		<< "Names should not include spaces, use underscore: 'Christian_P'" << std::endl;

	// number of current question
	int qNum = 1;
	// Question 1
	for (int i = 0; i < 12; i++)
	{
		getInput(question, resultsVec, qNum);
		question.clear();
	}

	std::cout
		<< std::endl
		<< std::endl
		<< "+-------------------------------------------------------------------+" << std::endl
		<< "|       Results       |                    Name(s)                  |" << std::endl
		<< "+-------------------------------------------------------------------+" << std::endl;

	for (int i = 0; i < resultsVec.size(); i++)
	{
		std::string s = resultsVec[i];
		printf ("| Most Likely to # %2i | %-43s |\n", (i + 1), s.c_str());
	}

	std::cout << "+-------------------------------------------------------------------+" << std::endl;

	// Prompt to keep the window open
	std::cout << std::endl << "Once done click anything really... (and then enter to close)" << std::endl;
	std::string closer;
	std::cin >> closer;
}

void addToMap(std::map<std::string, int>& map, std::string key)
{
	// Loop map looking for key
	std::map<std::string, int>::iterator it;
	it = map.find(key);
	if (it != map.end())
		map[key]++;
	else
		map[key] = 1;
}

void getResults(std::map<std::string, int>& map, std::vector<std::string>& resultsVec)
{
	// Loop through values to find highest, add key to vector
	// Temp values that point to the highest count
	int tempHighest = 0;
	std::string tempHighestKey = "";

	// Bool and vec to keep track of a tie
	bool tie = false;
	std::set<std::string> reps;
	for (std::map<std::string, int>::iterator it = map.begin(); it != map.end(); it++)
	{
		if (it->second == tempHighest)
		{
			tie = true;

			std::string curr = it->first;
			// adds the number to the string
			curr += ": ";
			curr += getNumAsString(tempHighest);

			// Adds current and previous to reps vec
			reps.insert(curr);
			reps.insert(tempHighestKey);
		}
		else if (it->second > tempHighest)
		{
			// Switch highest to new
			tempHighest = it->second;
			tempHighestKey = it->first;
			tempHighestKey += ": ";

			// adds the number to the string
			tempHighestKey += getNumAsString(tempHighest);

			// Switches bool back to false and empties the vector
			tie = false;
			reps.clear();
		}
	}

	// if a tie, add all names to a string, pass that
	if (reps.size() > 0)
	{
		tempHighestKey = "";
		for (std::string s : reps)
		{
			tempHighestKey += s;
			tempHighestKey += ", ";
		}
		tempHighestKey = tempHighestKey.substr(0, tempHighestKey.length() - 2);
	}

	// Add highest value's key to vec
	resultsVec.push_back(tempHighestKey);
}

void getInput(std::map<std::string, int>& map, std::vector<std::string>& resultsVec, int& qNum)
{
	bool saveData = false;
	do
	{
		bool keepgoing = false;
		int tableNum = 1;

		std::cout << std::endl;
		do
		{
			std::string tempKey;
			printf( "MLT #%02i Table #%02i: ", qNum ,tableNum);
			std::cin >> tempKey;

			// If input == 0 break
			if (tempKey == "0")
				keepgoing = true;
			else
			{
				// Search current map's keys to see if there is a match, if not create a key
				addToMap(map, tempKey);
			}
			tableNum++;

			// Since we have 11 tables, once we reach that number ( 1+ after increment) quit
			if (tableNum == 11)
				keepgoing = true;
		} while (!keepgoing);

		std::cout << "==============End of question #" << qNum << "==============" << std::endl;

		char sd;
		std::cout << "Save data (Y/N)? (If you made a mistake type 'N'): ";
		std::cin >> sd;
		
		if (toupper(sd) == 'Y')
			saveData = true;
		else
			map.clear();
	} while (!saveData);
	getResults(map, resultsVec);
	qNum++;
}

std::string getNumAsString(int num) {
	// adds the number to the string
	switch (num)
	{
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	case 11:
		return "11";
	default:
		return "something went wrong my guy";
	}
}