#pragma once

#include <fstream>
#include <string>
#include <vector>

class User
{

	// Add your code here

public:
	User();
	User(std::string identifier, std::string name, int age, std::string country, double rateOfActivity);
	std::string GetUserData() const;
	bool AddFriend(User* user);
	std::vector<User*>& GetFriends();
	
	std::string& GetIdentifier();
	std::string& GetName();
private:
	std::string _identifier = "";
	std::string _name;
	int _age;
	std::string _country;
	float _rateOfActivity;

	std::vector<User*> _friends;
	
	// Add your code here
};