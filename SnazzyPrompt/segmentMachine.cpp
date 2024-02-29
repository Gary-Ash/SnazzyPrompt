/*****************************************************************************************
 * segmentMachine.cpp
 *
 * The file implements a user's machine/host name segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :   17-Sep-2022  2:19pm
 * Modified :   21-Jan-2023  1:21pm
 *
 * Copyright © 2022 - 2023 By Gee Dbl A All rights reserved.
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
