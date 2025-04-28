#include "User.h"

User::User(std::string identifier, std::string name, int age, std::string country, double rateOfActivity) : _identifier(identifier), _name(name), _age(age), _country(country), _rateOfActivity(rateOfActivity) {}

std::ofstream User::GetUserData() const
{
	std::ofstream _outFile;
	_outFile << "Name: " << _name << std::endl;
	_outFile << "Age: " << _age << std::endl;
	_outFile << "Country: " << _country << std::endl;
	_outFile << "Activity Rate: " << _rateOfActivity << std::endl;
	_outFile << "Friends: " << std::size(_friendList) << std::endl;
	return _outFile;
}