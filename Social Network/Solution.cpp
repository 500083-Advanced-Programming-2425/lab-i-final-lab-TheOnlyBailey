#include <sstream>
#include "Solution.h"

Solution::Solution() : _outFile("Output.txt") {
	// Add your code here
}

bool Solution::processCommand(const std::string& commandString) {
	std::istringstream inString(commandString);
	std::string command;
	inString >> command;

	//if (command == "ViewProfile")
	//{
	//	std::string identifier;
	//}

	return false;
}

bool Solution::buildNetwork(const std::string& fileNameUsers, const std::string& fileNameFriendships) {
	std::ifstream finUsers(fileNameUsers);
	std::ifstream finFriendships(fileNameFriendships);
	if (finUsers.fail() || finFriendships.fail()) {
		return false;
	}
	std::string line;
	while (std::getline(finUsers, line))
	{
		int start = 0;
		std::string data[5];
		for (int i = 0; start < line.length(); i++)
		{
			data[i] = line.substr(start, line.find(','));
			start = line.substr(start, line.find(',')).length() + 1;
		}

	}
	
	return true;
}

// Add your code here
