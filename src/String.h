#ifndef __STRING_H__
#define __STRING_H__

class String
{
private:
	int size;
	char* buffer;
	char* Create(const char* const str);

public:
	String();
	String(const char c);
	String(const char* const str);
	~String();

	void Clear();
	int Size();

	const char* operator () () const;
	/*
	const char* operator = (const char* const);
	const char* operator + (const char* const);
	const char* operator + (String);
	*/
};

#endif
