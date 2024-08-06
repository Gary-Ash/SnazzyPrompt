/*****************************************************************************************
 * segmentMachine.cpp
 *
 * The file implements a user's machine/host name segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :   7-Jul-2024  6:48pm
 * Modified :
 *
 * Copyright © 2024 By Gary Ash All rights reserved.
 ****************************************************************************************/
#include <unistd.h>
#include "snazzy-prompt.h"

void segmentMachine(int argc, const char** argv, options_t& options, segment_t& segment)
{
	char host[_POSIX_HOST_NAME_MAX];

	segment.foreground	= options.foreground;
	segment.background	= options.background;

	gethostname(host, _POSIX_HOST_NAME_MAX);
	char* p = strrchr(host, '.');
	if (p) {
		*p = '\0';
	}
	segment.text = host;
}
