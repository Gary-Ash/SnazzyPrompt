/*****************************************************************************************
 * segmentUser.cpp
 *
 * The file implements a user's name segment
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  24-Nov-2024  2:24pm
 * Modified :
 *
 * Copyright © 2024 By Gary Ash All rights reserved.
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
