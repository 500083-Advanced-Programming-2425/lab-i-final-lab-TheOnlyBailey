#include <sstream>
#include <iostream>
#include <array>
#include "Solution.h"

Solution::Solution() : _outFile("Output.txt") {
	// Add your code here
}
Solution::~Solution() = default;

bool Solution::processCommand(const std::string& commandString) {
	std::istringstream inString(commandString);
	std::string command;
	inString >> command;

	if (command == "ViewProfile")
	{
		std::string identifier;
		inString >> identifier;
		return ViewProfile(identifier);
	}
	else if (command == "ListFriends")
	{
		std::string identifier;
		inString >> identifier;
		return ListFriends(identifier);
	}
	else if (command == "ListMutuals")
	{
		std::string identifier, identifier2;
		inString >> identifier;
		inString >> identifier2;
		return ListMutuals(identifier, identifier2);
	}
	else if (command == "FindSeparation")
	{
		std::string identifier, identifier2;
		inString >> identifier;
		inString >> identifier2;
		return FindSeperation(identifier, identifier2);
	}
	else if (command == "FriendScore")
	{
		std::string identifier, identifier2;
		inString >> identifier;
		inString >> identifier2;
		return FindFriendScore(identifier, identifier2);
	}
	else if (command == "SuggestFriends")
	{
		std::string identifier;
		inString >> identifier;
		return SuggestFriends(identifier);
	}
	else if (command == "TotalUsers")
	{
		std::string identifier;
		inString >> identifier;
		if (identifier == "")
		{
			return TotalUsers();
		}
		else
		{
			std::vector<std::string> countries;
			countries.push_back(identifier);
			std::string country;
			while (inString >> country)
			{
				countries.push_back(country);
			}
			return TotalUsers(countries);
		}
	}
	return false;
}
bool Solution::ViewProfile(const std::string& identifier)
{
	if (_outFile.is_open())
	{
		_outFile << GetUser(identifier)->GetUserData() << std::endl;
	}
	else
	{
		return false;
	}

	return true;
}
bool Solution::ListMutuals(const std::string& identifier1, const std::string& identifier2)
{
	_outFile << "ListMutuals " << identifier1 << " " << identifier2 << std::endl;
	std::vector<const User*> mutuals;
	int mutualCount = 0;
	for (const User* const friendptr : GetUser(identifier1)->GetFriends())
	{
		for (const User* const friendptr2 : GetUser(identifier2)->GetFriends())
		{
			if (friendptr == friendptr2)
			{
				mutuals.push_back(friendptr);
				mutualCount++;
			}
		}
	}
	_outFile << mutualCount << " Mutual friend(s) found. " << std::endl;
	for (const User* const friendptr : mutuals)
	{
		_outFile << friendptr->GetName() << " [" << friendptr->GetIdentifier() << "]" << std::endl;
	}
	_outFile << std::endl;
	return true;
}
User* Solution::GetUser(const std::string& identifier)
{
	for (int i = 0; i < _users.size(); i++)
	{
		if (_users[i].GetIdentifier() == identifier)
		{
			return &_users[i];
		}
	}
	return nullptr;
}
bool Solution::FindSeperation(const std::string& identifier1, const std::string& identifier2)
{
	_outFile << "FindSeparation " << identifier1 << " " << identifier2 << std::endl;
	_outFile << GetUser(identifier1)->FindSeparaton(GetUser(identifier2)) << " degree(s)" << std::endl << std::endl;
	return true;
}

bool Solution::FindFriendScore(const std::string& identifier1, const std::string& identifier2)
{
	const User* const user1 = GetUser(identifier1);
	const User* const user2 = GetUser(identifier2);
	const double friendScore = user1->FindFriendScore(user2);
	_outFile << "FriendScore " << identifier1 << " " << identifier2 << std::endl;
	_outFile << std::to_string(friendScore).erase(std::to_string(friendScore).find_last_of('.') + 3) << std::endl << std::endl;
	return true;
}


bool Solution::SuggestFriends(const std::string& identifier1)
{
	const User* const user1 = GetUser(identifier1);
	std::array<double, 5> friendScores{};
	std::vector<double> friendScores;
	const std::array<const std::string*, 5> friendIdentifiers{};
	for (const User& user2 : _users)
	{
	    if (&user2 != user1)
		{
				friendScores.push_back(user1->FindFriendScore(&user2));
		}
	}
	_outFile << "SuggestFriends " << identifier1 << std::endl;
	for (int i = 0; i < 5; i++)
	{
		_outFile << GetUser(*friendIdentifiers[i])->GetName() << " [" << GetUser(*friendIdentifiers[i])->GetIdentifier() << "] - " << user1->FindNumMutuals(GetUser(*friendIdentifiers[i])) << " mutual friend(s)" << std::endl;
	}
	_outFile << std::endl;
	return true;
}

bool Solution::TotalUsers()
{
	_outFile << "TotalUsers" << std::endl;
	_outFile << _users.size() << std::endl << std::endl;
	return true;
}

bool Solution::TotalUsers(const std::vector<std::string>& countries)
{
	int total = 0;
	for (int i = 0; i < _users.size(); i++)
	{
		for (int j = 0; j < countries.size(); j++)
		{
			if (countries[j] == _users[i].GetCountry())
			{
				total++;
			}
		}
	}
	std::string countriesString;
	for (int i = 0; i < countries.size(); i++)
	{
		if (i == countries.size() - 1)
		{
			countriesString += countries[i];
		}
		else
		{
			countriesString += countries[i] + " ";
		}
	}
	_outFile << "TotalUsers " << countriesString << std::endl;
	_outFile << total << std::endl << std::endl;
	return true;
}

bool Solution::buildNetwork(const std::string& fileNameUsers, const std::string& fileNameFriendships) {
	std::ifstream finUsers(fileNameUsers);
	std::ifstream finFriendships(fileNameFriendships);
	if (finUsers.fail() || finFriendships.fail()) {
		return false;
	}
	std::string line;
	while (std::getline(finUsers, line))
	{
		int start = 0;
		std::array<std::string, 5> data;
		int end = line.find(',', 0);
		for (int i = 0; i < 5; i++)
		{
			data[i] = line.substr(start, end - start);
			start = end + 1;
			end = line.find(',', start);
		}
		_users.push_back(User(data[0], data[1],  data[3], std::stoi(data[2]), std::stod(data[4])));
	}
	while (std::getline(finFriendships, line))
	{
		User* const user1 = GetUser(line.substr(0, line.find(',')));
		User* const user2 = GetUser(line.substr(line.find(',') + 1, line.length()));
		user1->AddFriend(user2);
		user2->AddFriend(user1);
	}
	return true;
}

bool Solution::ListFriends(const std::string& identifier)
{
	_outFile << "ListFriends " << identifier << std::endl;
	_outFile << GetUser(identifier)->GetFriends().size() << " friend(s) found." << std::endl;
	for (const User* const friendptr : GetUser(identifier)->GetFriends())
	{
		_outFile << friendptr->GetName() << " [" << friendptr->GetIdentifier() << "]" << std::endl;
	}
	_outFile << std::endl;
	return true;
}
// Add your code here
