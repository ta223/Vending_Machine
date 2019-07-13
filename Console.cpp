#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Console::Exceptions::Exceptions(const char *_error_) {

	printf("Error Message: %s \n", _error_);

}


void Console::fflush_stdin(void) {

	char c;
	while ((c = getchar()) != '\n' && c != EOF);

}



char* Console::Stdin_str() {

	char *str = (char *)malloc(sizeof(char) * 2);

	if (str == NULL) throw Exceptions("Memory Error:Failed to get string input from command line");

	size_t used = 0, allocated = sizeof(char);
	int i = 0;
	char temp;

	while (1) {

		if (used == allocated)
			str = (char *)realloc(str, allocated += sizeof(char));

		temp = getchar();

		if (temp == '\n' || temp == '\t' || temp == EOF)
			break;

		str[i++] = temp;
		used += sizeof(char);

	}

	fflush_stdin();

	str[i] = '\0';
	return str;

}


char *Console::Stdin_str_nocommas(void) {

	char *str = (char *)malloc(sizeof(char) * 2);

	if (str == NULL) throw Exceptions("Memory Error:Failed to get string input from command line");

	size_t used = 0, allocated = sizeof(char);
	int i = 0;
	char temp;

	while (1) {

		if (used == allocated)
			str = (char *)realloc(str, allocated += sizeof(char));

		temp = getchar();

		if (temp == '\n' || temp == '\t' || temp == EOF)
			break;

		if (temp != ',') {
			str[i++] = temp;
			used += sizeof(char);
		}

	}

	fflush_stdin();

	str[i] = '\0';
	return str;

}

bool Console::compare_string(const char *str1, const char *str2) {

	for (int i = 0; i < (int )strlen(str2); i++) 
		if (*(str1 + i) != '\n' &&  *(str1 + i) != *(str2 + i))	//ignore \n
			return false;

	return true;
}

double Console::GetDouble() {

	char *Numstr;



	while (1) {

		Numstr = Stdin_str();

		if (compare_string((char *)Numstr, "zero"))
			return 0;

		if (atof(Numstr) == 0.0) {

			printf("*Error: The input number is invalid\nEnter the number again: ");
			continue;

		}

		else return atof(Numstr);

	}



}

int Console::GetInt() {

	char *Numstr;

	while (1) {

		Numstr = Stdin_str();

		if (compare_string((char *)Numstr, "zero"))
			return 0;

		if (atoi(Numstr) == 0) {

			printf("*Error: Invalid integer\nEnter the number again:");
			continue;

		}

		else return atoi(Numstr);

	}


}

