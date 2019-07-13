#include "String.h"
#include <iostream>
#include <string>

using namespace std;

String::Exceptions::Exceptions(const char *error_type) {
	cout << "Error:" << error_type << endl;
}

void String::copy_char(const char *source, char *dest) {

	int len = strlen(source);
	for (int i = 0; i < len; i++) dest[i] = source[i];

}

int String::string_length() {

	return mem_size - 1;
}

String::String():mem_size(0), cstring(NULL) {}

String::String(const char *init_string):mem_size(0),cstring(NULL) {

	int len = strlen(init_string);
	cstring = new char[len + 1];
	if (cstring == NULL) throw Exceptions("Memory error in class constructor");

	mem_size = len+1;
	cstring[len] = '\0';

	for (int i = 0; i < len; i++) cstring[i] = init_string[i];

}

String::String(class String &other_string) {
	
	if (mem_size > 0) { delete cstring; mem_size = 0; cstring = NULL; }

	cstring = new char[other_string.string_length() + 1];

	if (cstring == NULL) throw Exceptions("Memory error in copy constructor");

	mem_size = other_string.string_length() + 1;
	cstring[mem_size - 1] = '\0';
	copy_char(other_string.cstring, this->cstring);

}


void String::Clear() {

	if (mem_size > 0  && cstring != NULL) { delete cstring; cstring = NULL; }
	mem_size = 0;

}

class String String::operator + (class String &other_string) {


	int len1 = this->mem_size - 1, len2 = other_string.string_length(), total_len = len1 + len2;

	char *new_string = new char[total_len + 1];

	if (new_string == NULL) throw Exceptions("Memory error in overloaded operator +");

	for (int i = 0; i < len1; i++)
		new_string[i] = this->cstring[i];

	for (int i = len1, j = 0; i < total_len, j < len2 ; i++, j++)
		new_string[i] = other_string.cstring[j];

	new_string[total_len] = '\0';

	class String result(new_string);
	delete new_string;

	return result;

}

class String String::operator + (const char *other_string) {

	int len1 = this->mem_size - 1, len2 = strlen(other_string), total_len = len1 + len2;

	char *new_string = new char[total_len + 1];

	if (new_string == NULL) throw Exceptions("Memory error in overloaded operator +");

	for (int i = 0; i < len1; i++)
		new_string[i] = this->cstring[i];

	for (int i = len1, j = 0; i < total_len, j < len2; i++, j++)
		new_string[i] = other_string[j];

	new_string[total_len] = '\0';

	class String result(new_string);
	delete new_string;

	return result;

}

void String::operator = (class String &other_string) {

	if (mem_size > 0 && cstring != NULL) { delete cstring; cstring = NULL; mem_size = 0; }

	int len = other_string.string_length();
	cstring = new char[len + 1];

	if (cstring == NULL) throw Exceptions("Memory error in overloaded operator = ");

	cstring[len] = '\0';
	for (int i = 0; i < len; i++) cstring[i] = other_string.cstring[i];
	mem_size = len + 1;

}

void String::operator = (const char *other_string) {

	if (mem_size > 0 && cstring != NULL) { delete cstring; cstring = NULL; mem_size = 0; }

	int len = strlen(other_string);
	cstring = new char[len + 1];
	if (cstring == NULL) throw Exceptions("Memory error in overloaded operator = ");
	cstring[len] = '\0';
	for (int i = 0; i < len; i++) cstring[i] = other_string[i];

	mem_size = len + 1;

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

bool String::IsVoid() {

	if (mem_size <= 0) return true;
	return false;

}

char* String::LowerCase(const char *string) {

	int len = strlen(string);
	char *new_string = new char[len + 1];
	new_string[len] = '\0';

	for (int i = 0; i < len; i++) new_string[i] = tolower(string[i]);
	return new_string;
}

void String::LowerCase() {

	int len = strlen(cstring);
	for (int i = 0; i < len; i++) cstring[i] = tolower(cstring[i]);

}

String::~String() { if (mem_size > 0) delete cstring; }
