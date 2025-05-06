#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <functional> 
#include <unordered_map>
#include <utility>

class User final
{

	// Add your code here
	struct UserPairHash
	{
		std::size_t operator()(const std::pair<const User*, const User*>& pair) const
		{
			const User* a = pair.first;
			const User* b = pair.second;
			if (a > b) std::swap(a, b);  // ensure consistent ordering
			return std::hash<const User*>()(a) ^ (std::hash<const User*>()(b) << 1);
		}
	};


public:
	User();
	User(const std::string& identifier, const std::string& name, const std::string& country, int age, double rateOfActivity);
	std::string GetUserData() const;
	bool AddFriend(User* user);
	const std::vector<User*>& GetFriends() const;
	const std::string& GetIdentifier() const;
	const bool IsFriend(const User& user) const;
	const std::string& GetName() const;
	const std::string& GetCountry() const;
	const double GetRateOfActivity() const;
	const double FindFriendScore(const User* user2) const;
	const int FindNumMutuals(const User* User2) const;
	const int FindSeparation(const User* identifier2) const;

private:


	std::vector<User*> _friends;
	std::string _identifier = "";
	std::string _name;
	std::string _country;
	int _age;
	float _rateOfActivity;

	mutable std::unordered_map<std::pair<const User*, const User*>, int, UserPairHash> _separationCache;
	mutable std::unordered_map<std::pair<const User*, const User*>, double, UserPairHash> _friendScoreCache;



	
	// Add your code here
};