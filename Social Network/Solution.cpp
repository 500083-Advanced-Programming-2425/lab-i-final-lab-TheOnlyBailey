#include <sstream>
#include <iostream>
#include "Solution.h"

Solution::Solution() : _outFile("Output.txt") {
	// Add your code here
}
Solution::~Solution()
{
	if (_outFile.is_open())
	{
		_outFile.close();
	}
}

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
	std::vector<User*> mutuals;
	int mutualCount = 0;
	for (User* friendptr : GetUser(identifier1)->GetFriends())
	{
		for (User* friendptr2 : GetUser(identifier2)->GetFriends())
		{
			if (friendptr->GetIdentifier() == friendptr2->GetIdentifier())
			{
				mutuals.push_back(friendptr);
				mutualCount++;
			}
		}
	}
	_outFile << mutualCount << " Mutual friend(s) found. " << std::endl;
	for (User* friendptr : mutuals)
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
		std::string data[5];
		int end = line.find(',', 0);
		for (int i = 0; i < 5; i++)
		{
			data[i] = line.substr(start, end - start);
			start = end + 1;
			end = line.find(',', start);
		}
		_users.push_back(User(data[0], data[1], std::stoi(data[2]), data[3], std::stod(data[4])));
	}
	while (std::getline(finFriendships, line))
	{
		GetUser(line.substr(0, line.find(',')))->AddFriend(GetUser(line.substr(line.find(',') + 1, line.length())));
		GetUser(line.substr(line.find(',') + 1, line.length()))->AddFriend(GetUser(line.substr(0, line.find(','))));
	}
	return true;
}

bool Solution::ListFriends(const std::string& identifier)
{
	_outFile << "ListFriends " << identifier << std::endl;
	_outFile << GetUser(identifier)->GetFriends().size() << " friend(s) found." << std::endl;
	for (User *friendptr : GetUser(identifier)->GetFriends())
	{
		_outFile << friendptr->GetName() << " [" << friendptr->GetIdentifier() << "]" << std::endl;
	}
	_outFile << std::endl;
	return true;
}
// Add your code here
