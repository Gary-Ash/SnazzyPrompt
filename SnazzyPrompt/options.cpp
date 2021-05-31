/*****************************************************************************************
 * options.cpp
 *
 * This file contains the code that parses the prompt optiona from the SNAZZY_PROMPT
 * environment variable
 *
 * SNAZZY_PROMPT=<Segment Name>,Foreground,Background,[,Alternate Foreground,Alternate Background]
 * Segment Names:
 *			cwd     = current working directory
 *			error   = error status of the last command
 *			git     = git status if the current directory is a git working tree  \
 *			machine = machine/host name
 *			user    = user name
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  12-Jan-2020  1:22pm
 * Modified :  12-Jan-2020  1:22pm
 *
 * Copyright © 2020 By Gee Dbl A All rights reserved.
 ****************************************************************************************/
#include <cstdlib>
#include <sstream>
#include "snazzy-prompt.h"

bool getOptions(std::vector<std::string>& selected) {
	std::string optionsText;
	const char* env = std::getenv("SNAZZY_PROMPT");
	if (env == NULL) {
		optionsText = "user,235,33,235,160;machine,235,37;cwd,235,227,235,166;git,235,219,235,40;error,235,166";
	}
	else {
		optionsText = env;
	}


	std::string description;
	std::istringstream optionsStream(optionsText);
	while (std::getline(optionsStream, description, ';')) {
		size_t comma = description.find(',');
		std::string option = description.substr(0, comma);
		auto iter = supportedSegments.find(option);
		if (iter != supportedSegments.end()) {
			description = description.substr(comma + 1);
			sscanf(description.c_str(), "%d,%d,%d,%d",
				   &iter->second.foreground,
				   &iter->second.background,
				   &iter->second.alternateForeground,
				   &iter->second.alternateBackground);
			selected.push_back(option);
		}
	}
	return true;
}
