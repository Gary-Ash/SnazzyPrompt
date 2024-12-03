/*****************************************************************************************
 * segmentCwd.cpp
 *
 * The file implements a current directory segment segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  24-Nov-2024  2:24pm
 * Modified :
 *
 * Copyright © 2024 By Gary Ash All rights reserved.
 ****************************************************************************************/
#include <pwd.h>
#include <unistd.h>
#include "snazzy-prompt.h"

void segmentCwd(int argc, const char** argv, options_t& options, segment_t& segment)
{
	struct passwd*	pw		= getpwuid(getuid());
	std::string		homeDir = pw->pw_dir;

	struct knownDir_t { std::string symbol; std::string directory; }
			knownDirectories[] = {
		{ std::string("􀣰"),		 std::string(homeDir + "/Desktop")	 },
		{ std::string("􀈷"),		 std::string(homeDir + "/Documents") },
		{ std::string("􀤨"),		 std::string(homeDir + "/Library")	 },
		{ std::string("􀙄"),		 std::string(homeDir + "/Developer") },
		{ std::string("􀁸"),		 std::string(homeDir + "/Downloads") },
		{ std::string(""),		 std::string(homeDir + "/Music")	 },
		{ std::string("􀎶"),		 std::string(homeDir + "/Movies")	 },
		{ std::string(""),		 std::string(homeDir + "/Pictures")	 },
		{ std::string(""),		 std::string(homeDir + "/Sites")	 },

		// bottom of the list on purpoae
		{ std::string("􂘞"), std::string(homeDir)				 },
	};
	char	dir[PATH_MAX];

	memset(dir, 0, PATH_MAX);
	getcwd(dir, PATH_MAX);

	char* p = dir;
	if (access(dir, W_OK)) {
		segment.text		= "";
		segment.foreground	= options.alternateForeground;
		segment.background	= options.alternateBackground;
	} else {
		segment.foreground	= options.foreground;
		segment.background	= options.background;
		for (int i = 0; i < sizeof(knownDirectories) / sizeof(knownDir_t); i++) {
			if (strncmp(knownDirectories[i].directory.c_str(), dir, knownDirectories[i].directory.length()) == 0) {
				segment.text.append(knownDirectories[i].symbol);
				p = dir + knownDirectories[i].directory.length() + 1;
				if (*p != '\0') {
					segment.text.append(" ");
				}
				break;
			}
		}
	}
	if (strlen(p) > 30) {
		p = strrchr(p, '/');
		segment.text.append(" ");
		if (strlen(p) > 30) {
			segment.text.append("/…");
			p = (p + strlen(p)) - 30;
		}
	}
	segment.text.append(" ");
	segment.text.append(p);
}
