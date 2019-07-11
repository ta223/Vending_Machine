#pragma once

#ifdef _WIN32
	#include <windows.h>
	#define CLEAR_CONSOLE   system("cls");	//clear screen for win32

#else
	#define CLEAR_CONSOLE printf("\033[H\033[J")  //for linux

#endif

class Console {

public:
	static void fflush_stdin(void);
	static char *Stdin_str();
	static bool compare_string(const char *str1, const char *str2);
	static double GetDouble();
	static int GetInt();

	class Exceptions {
	public:
		Exceptions(const char *_error_);

	};


};


