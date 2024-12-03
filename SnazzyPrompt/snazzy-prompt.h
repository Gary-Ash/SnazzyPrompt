/*****************************************************************************************
 * snazzy-prompt.h
 *
 * This is the project's global include file
 *
 * Author   :  Gary Ash <gary.ash@icloud.com>
 * Created  :  24-Nov-2024  2:24pm
 * Modified :
 *
 * Copyright © 2024 By Gary Ash All rights reserved.
 ****************************************************************************************/
#ifndef __SNAZZY_PROMPT_INCLUDED__
#define __SNAZZY_PROMPT_INCLUDED__

/*****************************************************************************************
 * system include files
 ****************************************************************************************/
#include <map>
#include <string>
#include <vector>
#include <cstdio>
#include <climits>
#include <locale>
#include <codecvt>

/*****************************************************************************************
 * segment data structure
 ****************************************************************************************/
struct options_t;
struct segment_t;
typedef void (* segmentFunction)(int argc, const char** argv, options_t& options, segment_t& segment);

struct options_t {
	unsigned int	defaultForeground;
	unsigned int	defaultBackground;
	unsigned int	defaultAlternateForeground;
	unsigned int	defaultAlternateBackground;
	unsigned int	foreground;
	unsigned int	background;
	unsigned int	alternateForeground;
	unsigned int	alternateBackground;
	segmentFunction functionPointer;
};

struct segment_t {
	std::string		text;
	unsigned int	foreground;
	unsigned int	background;
};

/*****************************************************************************************
 * function prototypes
 ****************************************************************************************/
bool    getOptions(std::vector<std::string>&  selected);
void    segmentCwd(int argc, const char** argv, options_t& options, segment_t& segment);
void    segmentError(int argc, const char** argv, options_t& options, segment_t& segment);
void    segmentGit(int argc, const char** argv, options_t& options, segment_t& segment);
void    segmentMachine(int argc, const char** argv, options_t& options, segment_t& segment);
void    segmentUser(int argc, const char** argv, options_t& options, segment_t& segment);
void    appendSpaceAsNeeded(std::string& str);

/*****************************************************************************************
 * globals
 ****************************************************************************************/
extern std::map<std::string, options_t>								supportedSegments;
extern std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>	converter;

#endif
