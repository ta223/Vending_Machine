#pragma once

class String {

public:
	String();
	String(const char *init_string);	//conversion constructor
	String(class String &other_string);	//copy constructor

	int string_length();

	void Clear();

	/*overloading operators*/
	class String operator + (class String &other_string);
	class String operator + (const char *other_string);
	void operator = (class String &other_string);
	void operator = (const char *other_string);
	bool operator == (class String &other_string);
	bool operator == (const char *other_string);
	operator char*();

	char *get_ptr();

	int GetCoin();
	bool IsCoin();

	bool IsVoid();

	static char* LowerCase(char *string);
	void LowerCase();

	class Exceptions{
	public:
		Exceptions(char *error_type);
	};

	~String();

private:
	char *cstring;
	int mem_size;
	void copy_char(const char *source, char *dest);

};
