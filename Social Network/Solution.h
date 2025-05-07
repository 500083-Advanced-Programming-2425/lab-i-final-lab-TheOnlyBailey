#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "User.h"

class Solution final
{
	std::ofstream _outFile;

	struct UserPairHash //custom hash function for std::pair since their wasn't one
	{
		template <typename T1, typename T2>
		std::size_t operator ()(const std::pair<T1, T2>& p) const
		{
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);
			return h1 ^ (h2 << 1);
		}
	};

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

	User* GetUser(const std::string& identifier);


private:
	std::vector<User> _users;
};