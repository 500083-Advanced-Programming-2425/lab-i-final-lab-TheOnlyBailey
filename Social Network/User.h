#pragma once

#include <fstream>
#include <string>
#include <vector>

class User final
{

	// Add your code here


public:
	User();
	User(const std::string& identifier, const std::string& name, int age, const std::string& country, double rateOfActivity);
	std::string GetUserData() const;
	bool AddFriend(User* user);
	const std::vector<User*>& GetFriends();
	
	std::string& GetIdentifier();
	std::string& GetName();
	std::string& GetCountry();
	double GetRateOfActivity();

	double FindFriendScore(const User* user2) const;
	const int FindNumMutuals(const User* User2);
	const int FindSeparaton(const User* identifier2);

private:
	std::vector<User*> _friends;
	std::string _identifier = "";
	std::string _name;
	std::string _country;
	int _age;
	float _rateOfActivity;


	
	// Add your code here
};