#include "User.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

User::User() : _identifier(), _name(), _country(), _age(0), _rateOfActivity(0.0) {}
User::User(const std::string& identifier,const std::string& name, const std::string& country, int age, double rateOfActivity) : _identifier(identifier), _name(name), _country(country), _age(age), _rateOfActivity(rateOfActivity) {}

const std::string& User::GetIdentifier() const { return _identifier; }

const std::string& User::GetName() const{ return _name; }

bool User::AddFriend(User* user)
{
	_friends.push_back(user);
	return true;
}

const std::vector<User*>& User::GetFriends() const { return _friends; }

const int User::FindNumMutuals(const User* User2) const
{
	int mutualCount = 0;
	for (const User* const friendptr : this->GetFriends())
	{
		for (const User* const friendptr2 : User2->GetFriends())
		{
			if (friendptr == friendptr2)
			{
				mutualCount++;
			}
		}
	}
	return mutualCount;
}


const double User::GetRateOfActivity() const
{
	return _rateOfActivity;
}


const int User::FindSeparaton(const User* identifier2) const
{
	std::queue<const User*> queue;
	std::unordered_map<const User*,const User*> from;
	std::unordered_set<const User*> visited;

	const User*const  _startNode = this;

	queue.push(_startNode);
	visited.insert(_startNode);
	from[_startNode] = nullptr;

	while (!queue.empty())
	{
		const User* const current = queue.front();
		queue.pop();

		if (current == identifier2)
		{
			int separations = 0;
			for (const User* node = current; node != nullptr; node = from[node])
			{
				separations++;
			}
			separations--;
			if (separations > 6)
			{
				return 6;
			}
			else
			{
				return separations;
			}
		}

		for (User* const friendUser : current->GetFriends())
		{
			if (visited.find(friendUser) == visited.end())
			{
				queue.push(friendUser);
				visited.insert(friendUser);
				from[friendUser] = current;
			}
		}
	}
	return 6;

}

const double User::FindFriendScore(const User* user2) const
{
	const int mutuals = this->FindNumMutuals(user2);
	const int separation = this->FindSeparaton(user2);
	const float score = (mutuals * this->GetRateOfActivity() * user2->GetRateOfActivity()) + (720 / std::min(separation, 6));
	return score;
}

const bool User::IsFriend(const User& user) const
{

	for (User* const friendpntr : this->GetFriends())
	{
		if (friendpntr == &user)
		{
			return true;
		}
	}
	return false;
	
}

const std::string& User::GetCountry() const{ return _country; }

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