#include <stdio.h>
#include "lua.hpp"
#include "String.h"

int main()
{
	String string("Hello my String class!!");
	printf("%s\n", string());
    return 0;
}
