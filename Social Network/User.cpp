#include "User.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

User::User() : _identifier(), _name(), _country(), _age(0), _rateOfActivity(0.0) {}
User::User(const std::string& identifier, const std::string& name, const std::string& country, int age, double rateOfActivity) : _identifier(identifier), _name(name), _country(country), _age(age), _rateOfActivity(rateOfActivity) {}

const std::string& User::GetIdentifier() const { return _identifier; }

const std::string& User::GetName() const { return _name; }

bool User::AddFriend(User* user)
{
	_friends.push_back(user);
	return true;
}

const std::vector<User*>& User::GetFriends() const { return _friends; }

const int User::FindNumMutuals(const User* user2) const
{
	std::unordered_set<const User*> const friendsOfThis(this->_friends.begin(), this->_friends.end());

	int mutualCount = 0;
	for (const User* const friendPtr : user2->GetFriends())
	{
		if (friendsOfThis.count(friendPtr))
		{
			++mutualCount;
		}
	}

	return mutualCount;
}


const double User::GetRateOfActivity() const
{
	return _rateOfActivity;
}


const int User::FindSeparation(const User* user2) const
{
	auto key = std::minmax(this, user2);
	auto& cache = _separationCache;

	if (cache.find(key) != cache.end())
		return cache[key];

	std::queue<const User*> queue;
	std::unordered_map<const User*, int> visited;

	queue.push(this);
	visited[this] = 0;


	while (!queue.empty())
	{
		const User* const current = queue.front();
		queue.pop();

		int depth = visited[current];
		if (depth >= 6) break;

		for (const User* const friendUser : current->GetFriends())
		{
			if (visited.find(friendUser) == visited.end())
			{
				if (friendUser == user2)
				{
					cache.emplace(key, depth + 1);
					return depth + 1;
				}
				visited[friendUser] = depth + 1;
				queue.push(friendUser);
			}
		}
	}

	cache[key] = 6;
	return 6;
}





const double User::FindFriendScore(const User* user2) const
{
	const auto key = std::minmax(this, user2);
	auto& cache = _friendScoreCache;

	if (cache.find(key) != cache.end())
		return cache[key];

	const int mutuals = this->FindNumMutuals(user2);
	const int separation = this->FindSeparation(user2);
	const int clampedSep = std::max(1, std::min(separation, 6));

	const double activityProduct = this->GetRateOfActivity() * user2->GetRateOfActivity();
	const double score = (mutuals * activityProduct) + (720.0 / clampedSep);

	cache[key] = score;
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

const std::string& User::GetCountry() const { return _country; }

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