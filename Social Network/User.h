#pragma once

#include <fstream>
#include <string>
#include <vector>

class User final
{

	// Add your code here


public:
	User();
	User(const std::string& identifier, const std::string& name, const std::string& country, int age, double rateOfActivity);
	std::string GetUserData() const;
	bool AddFriend(User* user);
	const std::vector<User*>& GetFriends() const;
	
	const std::string& GetIdentifier() const;
	const std::string& GetName() const;
	const std::string& GetCountry() const;
	const double GetRateOfActivity() const;
	const double FindFriendScore(const User* user2) const;
	const int FindNumMutuals(const User* User2) const;
	const int FindSeparaton(const User* identifier2) const;

private:
	std::vector<User*> _friends;
	std::string _identifier = "";
	std::string _name;
	std::string _country;
	int _age;
	float _rateOfActivity;


	
	// Add your code here
};