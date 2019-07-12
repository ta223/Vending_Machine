#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

String::Exceptions::Exceptions(char *error_type) {
	printf("Error:%s\n", error_type);
}

void String::copy_char(const char *source, char *dest) {

	int len = strlen(source);
	for (int i = 0; i < len; i++) dest[i] = source[i];

}

int String::string_length() {

	return mem_size - 1;
}

String::String(const char *init_string):mem_size(0),cstring(NULL) {

	int len = strlen(init_string);
	cstring = (char *)malloc(sizeof(char)*(len + 1));
	if (cstring == NULL) throw Exceptions((char *)"Memory error in class constructor");

	mem_size = len+1;
	cstring[len] = '\0';

	for (int i = 0; i < len; i++) cstring[i] = init_string[i];

}

String::String(class String &other_string) {
	
	if (mem_size != 0) { free(cstring); mem_size = 0; cstring = NULL; }
	cstring = (char *)malloc(sizeof(char)*(other_string.string_length() + 1));

	if (cstring == NULL) throw Exceptions((char *)"Memory error in copy constructor");

	mem_size = other_string.string_length() + 1;
	cstring[mem_size - 1] = '\0';
	copy_char(other_string.cstring, this->cstring);

}

String::~String() {if (mem_size != 0) free(cstring);}

static int string_case_compare(class String &a, class String &b) { return 1; }

class String String::operator + (class String &other_string) {


	int len1 = this->mem_size - 1, len2 = other_string.string_length(), total_len = len1 + len2;

	char *new_string = (char *)malloc(sizeof(char)*(total_len+1));

	if (new_string == NULL) throw Exceptions((char *)"Memory error in overloaded operator +");

	for (int i = 0; i < len1; i++)
		new_string[i] = this->cstring[i];

	for (int i = len1, j = 0; i < total_len, j < len2 ; i++, j++)
		new_string[i] = other_string.cstring[j];

	new_string[total_len] = '\0';

	class String result(new_string);
	free(new_string);

	return result;

}

class String String::operator = (class String &other_string) {

	int len = other_string.string_length();
	char *new_string = (char *)malloc(sizeof(char )*(len+1));
	if (new_string == NULL) throw Exceptions((char *)"Memory error in overloaded operator = ");

	new_string[len] = '\0';
	for (int i = 0; i < len; i++) new_string[i] = other_string.cstring[i];

	class String result(new_string);
	free(new_string);

	return result;
}

class String String::operator = (const char *other_string) {


	int len = strlen(other_string);
	char *new_string = (char *)malloc(sizeof(char)*(len + 1));
	if (new_string == NULL) throw Exceptions((char *)"Memory error in overloaded operator = ");
	new_string[len] = '\0';
	for (int i = 0; i < len; i++) new_string[i] = other_string[i];

	class String result(new_string);
	free(new_string);

	return result;

}

String::operator char*() {
	return cstring;
}


char* String::get_ptr() {
	return this->cstring;
}

bool String::operator == (class String &other_string) {

	int size1 = strlen(this->cstring), size2 = strlen(other_string.cstring);

	if (size1 != size2) return false;

	for (int i = 0; i < size1; i++)
		if(this->cstring[i] != '\n' && other_string.cstring[i] != '\n')
			if (this->cstring[i] != other_string.cstring[i]) return false;
	

	return true;

}

bool String::operator == (const char *other_string) {

	int size1 = strlen(this->cstring), size2 = strlen(other_string);

	if (size1 != size2) return false;

	for (int i = 0; i < size1; i++)
		if (this->cstring[i] != '\n' && other_string[i] != '\n')
			if (this->cstring[i] != other_string[i]) return false;

	return true;

}

int String::GetCoin() {

	if (*this == "ONE POUND") return 100;
	else if (*this == "TWO POUNDS") return 200;

	return atoi(static_cast<char*>(*this));

}

bool String::IsCoin() {

	class String input_coins[] = { "ONE POUND", "TWO POUNDS", "1", "2", "5", "10", "20", "50" };

	for (int i = 0; i < 8; i++)
		if (*this == input_coins[i]) return true;

	return false;

}
