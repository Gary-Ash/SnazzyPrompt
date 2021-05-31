/*****************************************************************************************
 * segmentCwd.cpp
 *
 * The file implements a current directory segment segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  12-Jan-2020  1:22pm
 * Modified :  12-Jan-2020  1:22pm
 *
 * Copyright © 2020 By Gee Dbl A All rights reserved.
 ****************************************************************************************/
#include <pwd.h>
#include <unistd.h>
#include "snazzy-prompt.h"

void segmentCwd(int argc, const char** argv, options_t& options, segment_t& segment) {
	char   dir [PATH_MAX];

	getcwd(dir, PATH_MAX);
	struct passwd*  pw = getpwuid(getuid());
	if ( access(dir, W_OK) ) {
		segment.text = "";
		segment.foreground	= options.alternateForeground;
		segment.background	= options.alternateBackground;
	}
	else {
		segment.foreground	= options.foreground;
		segment.background	= options.background;
	}
	char*  p = dir;
	if ( strstr(dir, pw->pw_dir) ) {
		appendSpaceAsNeeded(segment.text);
		segment.text.append("");
		p = (dir + strlen(pw->pw_dir));
	}
	if (strlen(p) > 20) {
		p = strrchr(p, '/');
		appendSpaceAsNeeded(segment.text);
		if	(strlen(p) > 20) {
			segment.text.append("/…");
			p = (p + strlen(p)) - 20;
		}
	}
	appendSpaceAsNeeded(segment.text);
	segment.text.append(p);
}
