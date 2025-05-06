#include "User.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Solution.h"
User::User() : _identifier(), _name(), _age(0), _country(), _rateOfActivity(0.0) {}
User::User(const std::string& identifier,const std::string& name, int age,const std::string& country, double rateOfActivity) : _identifier(identifier), _name(name), _age(age), _country(country), _rateOfActivity(rateOfActivity) {}

std::string& User::GetIdentifier() { return _identifier; }
std::string& User::GetName() { return _name; }
bool User::AddFriend(User* user)
{
	_friends.push_back(user);
	return true;
}
const std::vector<User*>& User::GetFriends() { return _friends; }

const int User::FindNumMutuals(const User* User2)
{
	int mutualCount = 0;
	for (User* friendptr : this->GetFriends())
	{
		for (User* friendptr2 : User2->GetFriends())
		{
			if (friendptr->GetIdentifier() == friendptr2->GetIdentifier())
			{
				mutualCount++;
			}
		}
	}
	return mutualCount;
}


double User::GetRateOfActivity()
{
	return _rateOfActivity;
}


const int User::FindSeparaton(const User* identifier2)
{
	std::queue<User*> queue;
	std::unordered_map<User*, User*> from;
	std::unordered_set<User*> visited;

	int maxDegree = 0;
	User* _startNode = this;
	User* _endNode = identifier2;

	queue.push(_startNode);
	visited.insert(_startNode);
	from[_startNode] = nullptr;

	while (!queue.empty())
	{
		User* current = queue.front();
		queue.pop();

		if (current->GetIdentifier() == identifier2->GetIdentifier())
		{
			int separations = 0;
			for (User* node = current; node != nullptr; node = from[node])
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

		for (User* friendUser : current->GetFriends())
		{
			if (visited.find(friendUser) == visited.end())
			{
				queue.push(friendUser);
				visited.insert(friendUser);
				from[friendUser] = current;
			}
		}
		maxDegree++;
	}
	return 6;

}

double User::FindFriendScore(const User* user2) const
{
	int mutuals = this->FindNumMutuals(user2);
	int separation = this->FindSeparaton(user2);
	float score = (mutuals * this->GetRateOfActivity() * user2->GetRateOfActivity()) + (720 / std::min(separation, 6));
	return (this->FindNumMutuals(user2) * this->GetRateOfActivity() * user2->GetRateOfActivity()) + (720 / std::min(this->FindSeparaton(user2), 6));
}
std::string& User::GetCountry() { return _country; }
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