/*****************************************************************************************
 * main.cpp
 *
 * This is the program's entry point
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  24-Nov-2024  2:24pm
 * Modified :
 *
 * Copyright © 2024 By Gary Ash All rights reserved.
 ****************************************************************************************/
#include "snazzy-prompt.h"
#include <term.h>

// *INDENT-OFF*
std::map<std::string, options_t> supportedSegments = {
	{ "cwd",				{ 235, 220, 235, 166,   0,   0,   0,   0, segmentCwd 		}},
	{ "error",				{ 235, 166,   0,   0,   0,   0,   0,   0, segmentError  	}},
	{ "git",				{ 235, 125, 235,   2,   0,   0,   0,   0, segmentGit      	}},
	{ "machine",			{ 235,  37,   0,   0,   0,   0,   0,   0, segmentMachine	}},
	{ "user",				{ 235,  33, 235, 160,   0,   0,   0,   0, segmentUser		}},
};
// *INDENT-ON*

std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

int main(int argc, const char* argv[])
{
	std::string					prompt;
	std::string					openBracket;
	std::string					closingBracket;
	std::vector<std::string>	selected;
	std::vector<segment_t>		segments(selected.size());

	const char*					shell = std::getenv("SHELL");

	if (strstr(shell, "zsh")) {
		openBracket		= "\%{";
		closingBracket	= "\%}";
	} else if (strstr(shell, "bash")) {
		openBracket		= "\\[";
		closingBracket	= "\\]";
	}

	setupterm(NULL, fileno(stdout), NULL);
	char*	sataf	= tigetstr(const_cast<char*>("setaf"));
	char*	setab	= tigetstr(const_cast<char*>("setab"));
	char*	reset	= tigetstr(const_cast<char*>("sgr0"));

	if (getOptions(selected)) {
		size_t	index	= 0;
		size_t	count	= 0;

		for (auto selectedSegment : selected) {
			segment_t	segment;
			options_t	options = supportedSegments[selectedSegment];
			options.functionPointer(argc, argv, options, segment);

			if (!segment.text.empty()) {
				++count;
				segments.push_back(segment);
			}
		}

		if (count > 0) {
			for (auto segment : segments) {
				prompt.append(openBracket);
				prompt.append(tparm(const_cast<char*>(sataf), segment.foreground));
				prompt.append(closingBracket);

				prompt.append(openBracket);
				prompt.append(tparm(const_cast<char*>(setab), segment.background));
				prompt.append(closingBracket);

				prompt.append(segment.text);
				prompt.append(" ");
				prompt.append(openBracket);
				prompt.append(tparm(const_cast<char*>(sataf), segment.background));
				prompt.append(closingBracket);

				if ((index + 1) < count) {
					segment_t next = segments[index + 1];
					prompt.append(openBracket);
					prompt.append(tparm(const_cast<char*>(setab), next.background));
					prompt.append(closingBracket);
					prompt.append("");
				}else {
					prompt.append(openBracket);
					prompt.append(reset);
					prompt.append(closingBracket);
					prompt.append(openBracket);
					prompt.append(tparm(const_cast<char*>(sataf), segment.background));
					prompt.append(closingBracket);
					prompt.append("");
					prompt.append(openBracket);
					prompt.append(reset);
					prompt.append(closingBracket);
					prompt.append(" ");
				}
				++index;
			}
			printf("%s", prompt.c_str());
		}
	}
	return 0;
}

void appendSpaceAsNeeded(std::string& str)
{
	size_t len = str.length();

	if (len > 0 && !isspace(str[len - 1])) {
		str.append(" ");
	}
}
