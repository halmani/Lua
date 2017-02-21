#include <stdio.h>
#include "../lib/lua-5.3.4/install/include/lua.hpp"
#include "String.h"

int main()
{
	String string("Hello my string class!!");
	printf("%s\n", string());
    return 0;
}
