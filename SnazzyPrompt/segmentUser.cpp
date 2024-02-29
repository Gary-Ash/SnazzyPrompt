/*****************************************************************************************
 * segmentUser.cpp
 *
 * The file implements a user's name segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :   17-Sep-2022  2:19pm
 * Modified :   21-Jan-2023  1:21pm
 *
 * Copyright © 2022 - 2023 By Gee Dbl A All rights reserved.
 ****************************************************************************************/
#include <unistd.h>
#include "snazzy-prompt.h"

void segmentUser(int argc, const char** argv, options_t& options, segment_t& segment)
{
	segment.foreground	= options.foreground;
	segment.background	= options.background;
	segment.text		= getlogin();

	if (geteuid() == 0) {
		segment.foreground	= options.alternateForeground;
		segment.background	= options.alternateBackground;
	}
}
