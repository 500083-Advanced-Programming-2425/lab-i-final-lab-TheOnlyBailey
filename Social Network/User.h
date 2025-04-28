#pragma once

#include <fstream>
#include <string>

class User
{

	// Add your code here

public:
	User(std::string identifier, std::string name, int age, std::string country, double rateOfActivity);
	std::ofstream GetUserData() const;

	 
private:
	std::string _identifier;
	std::string _name;
	int _age;
	std::string _country;
	double _rateOfActivity;
	User* _friendList[1000];
	// Add your code here
};