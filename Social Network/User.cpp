#include "User.h"
User::User() : _identifier(), _name(), _age(0), _country(), _rateOfActivity(0.0) {}
User::User(std::string identifier, std::string name, int age, std::string country, double rateOfActivity) : _identifier(identifier), _name(name), _age(age), _country(country), _rateOfActivity(rateOfActivity) {}

std::string& User::GetIdentifier() { return _identifier; }
std::string& User::GetName() { return _name; }
bool User::AddFriend(User* user)
{
	_friends.push_back(user);
	return true;
}
std::vector<User*>& User::GetFriends() { return _friends; }
std::string User::GetUserData() const
{
	std::string _outFile;
	_outFile += "ViewProfile " + _identifier + "\n";
	_outFile += "Name: " + _name + "\n";
	_outFile += "Age: " + std::to_string(_age) + "\n";
	std::string country;
	if (_country == "DEU") { country = "Germany"; }
	else if (_country == "NOR") { country = "Norway"; }
	else if (_country == "DNK") { country = "Denmark"; }
	else if (_country == "FIN") { country = "Finland"; }
	else if (_country == "FRA") { country = "France"; }
	else if (_country == "GBR") { country = "United Kingdom"; }
	else if (_country == "NLD") { country = "Netherlands"; }
	else if (_country == "SWE") { country = "Sweden"; }

	_outFile += "Country: " + country + "\n";
	_outFile += "Activity Rate: " + std::to_string(_rateOfActivity * 100).erase(std::to_string(_rateOfActivity * 100).find_last_of('.')) + "%\n";
	_outFile += "Friends: " + std::to_string(_friends.size()) + "\n";
	return _outFile;
}