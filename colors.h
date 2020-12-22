#ifndef COLORS_H
#define COLORS_H

	#if defined(__APPLE__) || defined(__linux__)
		#define RED "\x1B[31m"
		#define GREEN = "\x1B[32m"
		#define MAGENTA = "\x1B[35m"
		#define YELLOW = "\x1B[33m"
		#define BLUE = "\x1B[34m"
		#define NORM = "\x1B[0m"
	#else
		#define RED ""
		#define GREEN ""
		#define MAGENTA ""
		#define YELLOW ""
		#define BLUE ""
		#define NORM ""
	#endif

#endif