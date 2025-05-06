#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "User.h"

class Solution final
{
	std::ofstream _outFile;

	// Add your code here
	
public:
	Solution();
	~Solution();

	bool buildNetwork(const std::string& fileNameUsers, const std::string& fileNameFriendships);
	bool processCommand(const std::string& commandString);


	bool ViewProfile(const std::string& ientifier);
	bool ListFriends(const std::string& identifier);
	bool ListMutuals(const std::string& identifier1, const std::string& identifier2);
	bool FindSeperation(const std::string& identifier1, const std::string& identifier2);
	bool FindFriendScore(const std::string& identifier1, const std::string& identifier2);
	bool SuggestFriends(const std::string& identifier1);
	bool TotalUsers();
	bool TotalUsers(const std::vector<std::string>& countries);
	const User* GetUser(const std::string& identifier);


private:
	std::vector<User> _users;
	// Add your code here
};