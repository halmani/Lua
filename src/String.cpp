#include <stdio.h>
#include "String.h"

String::String()
	: buffer(NULL)
{
}

String::String(const char c)
	: buffer(NULL)
{
	char str[2] = {c, '\0'};
	buffer = Create(str);
}

String::String(const char* const str)
	: buffer(NULL)
{
	buffer = Create(str);
}

String::~String()
{
	Clear();
}

char* String::Create(const char* const str) 
{
	if (str == NULL)
		return NULL;
	Clear();
	int s = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		s++;
	size = s;
//	printf("%s(%d)\n", str, size);

	char* ret = NULL;
	if (0 < size)
	{
		ret = new char[size+1];
		for (int i = 0; i < size; ++i)
			ret[i] = str[i];
		ret[size] = '\0';
	}
//	printf("%s(%d)\n", ret, size);
	return ret;
}

void String::Clear()
{
	if (buffer != NULL)
	{
		delete[] buffer;
		buffer = NULL;
	}
}

int String::Size()
{
	return size;
}

// operator
const char* String::operator () () const
{
	return buffer;
}

/*
const char* String::operator = (const char* const str)
{
	return NULL;
}

const char* String::operator + (const char* const str)
{
	return Create("");
}

const char* String::operator + (const char* const str)
{
	return Create("");
}
*/
