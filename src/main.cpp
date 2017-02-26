#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "time.h"
#include "lua.hpp"
#include <unistd.h>

int GetSelection(const char* title)
{
	char input[100];

	printf("%s >", title);
	fgets(input, sizeof(input), stdin);
	printf("\n");
	if (strlen(input) == 0 || !isdigit(input[0]))
		return -1;
	return atoi(input);
}

int GetSelectionGlue(lua_State* L)
{
	const char* title = lua_tostring(L, 1);
	int index = GetSelection(title);
	lua_settop(L, 0);
	lua_pushnumber(L, index);
	return 1;
}

typedef struct SItemType
{
	char name[100];
	int price;
} ItemInfo;

#define MAX_SHOP_ITEMS 5

ItemInfo shop_items[MAX_SHOP_ITEMS] = {
	{ "薬草", 100 },
	{ "こんぼう", 1000 },
	{ "布の服", 2000 },
	{ "黄金の斧", 9990000 },
	{ "", -1 },
};

static int s_money = 0;

int GetMoney()
{
	return s_money;
}

int GetMoneyGlue(lua_State* L)
{
	int money = GetMoney();
	lua_settop(L, 0);
	lua_pushnumber(L, money);
	return 1;
}

void SetMoney(int money)
{
	s_money = money;
}

int SetMoneyGlue(lua_State* L)
{
	int index = (int)lua_tonumber(L, 1);
	SetMoney(index);
	lua_settop(L, 0);
	return 0;
}

/*
static bool Shop()
{
	printf("\nいらっしゃいませ！道具や[C]へようこそ！\n");
	while (true)
	{
		printf("何にするかい？\n");
		printf("(所持金：%d円)\n", s_money);

		for (int i = 0; i < MAX_SHOP_ITEMS; ++i)
		{
			ItemInfo* item = &shop_items[i];
			if (item->price <= -1)
				continue;
			printf("%2d. %-10s %6d円\n", i+1, item->name, item->price);
		}
		printf(" 0. 帰る\n");
		int num = GetSelection("どうする？");
		int idx = num -1;
		if (num == 0)
			break;
		if (num < 0 || MAX_SHOP_ITEMS < num || shop_items[idx].price <= -1)
		{
			printf("え？なんだって？");
			continue;
		}
		ItemInfo* item = &shop_items[idx];
		if (s_money < item->price)
		{
			printf("%s だね。でもお金が %d円足りないみたいだね。またおいで。\n",
				item->name, item->price - s_money);
			continue;
		}
		printf("%s だね。じゃあ %d円いただくよ。\n次へ (Push Any Key)",
				item->name, item->price);
		s_money -= item->price;
		return true; 
	}
	printf("またいらっしゃい！");
	return false;
}
*/

// -------------------------------------------------------
static void PrintStackItem(lua_State* L, int idx)
{
	int type = lua_type(L, idx);
	switch (type)
	{
		case LUA_TSTRING:
			printf("index %2d : type=%2s : \"%s\"\n",
					idx,
					lua_typename(L,type),
					lua_tostring(L, idx)
				);
			break;
		case LUA_TNUMBER:
			printf("index %2d : type=%2s : %f\n",
					idx,
					lua_typename(L,type),
					lua_tonumber(L, idx)
				);
			break;
		case LUA_TBOOLEAN:
			printf("index %2d : type=%2s : \"%s\"\n",
					idx,
					lua_typename(L,type),
					lua_toboolean(L, idx) ? "true" : "false"
				);
			break;
		default:
			printf("index %2d : type=%2s\n",
					idx,
					lua_typename(L,type)
				);
			break;
	}
}

static void PrintStack(lua_State* L)
{
	printf("----- state -----\n");
	int top = lua_gettop(L);
	for (int i = top; i >= 1; --i)
		PrintStackItem(L, i);
	printf("-----------------\n");
	for (int i = -1; i >= -top; --i)
		PrintStackItem(L, i);
	printf("-----------------\n");
}

// -------------------------------------------------------
const ItemInfo* GetItem(int index)
{
	if (index < 0 || index >= MAX_SHOP_ITEMS)
		return NULL;
	return &shop_items[index];
}

const char* GetItemName(int index)
{
	const ItemInfo* item = GetItem(index);
	if (item == NULL)
		return NULL;
	return item->name;
}

const int GetItemPrice(int index)
{
	const ItemInfo* item = GetItem(index);
	if (item == NULL)
		return -1;
	return item->price;
}

int GetItemNameGlue(lua_State* L)
{
	//printf("GetItemName() 関数実行\n");
	//PrintStack(L);
	int index = (int)lua_tonumber(L, 1);
	const char* name = GetItemName(index);
	lua_settop(L, 0);
	lua_pushstring(L, name);
	//PrintStack(L);
	return 1;
}

int GetItemPriceGlue(lua_State* L)
{
	int index = (int)lua_tonumber(L, 1);
	int price = GetItemPrice(index);
	lua_settop(L, 0);
	lua_pushnumber(L, price);
	return 1;
}


// -------------------------------------------------------
int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; ++i)
		rand();

	// luaの操作ハンドラ取得
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	//luaL_dostring(L, "print('Luaスクリプト開始！')");

	// グローバル変数の共有
	lua_pushnumber(L, MAX_SHOP_ITEMS);
	lua_setglobal(L, "MAX_SHOP_ITEMS");

	// glue関数の設定
	lua_register(L, "GetItemName", GetItemNameGlue);
	lua_register(L, "GetItemPrice", GetItemPriceGlue);
	lua_register(L, "GetSelection", GetSelectionGlue);
	lua_register(L, "GetMoney", GetMoneyGlue);
	lua_register(L, "SetMoney", SetMoneyGlue);

	s_money = (rand() + 10000 / RAND_MAX) + 500;

	while (true)
	{
		int ret = -1;
		char filename[128] = "scripts/douguya.lua";
		ret = luaL_dofile(L, filename);
		if (ret != 0)
			printf("Error loading %s. Error code: %s\n", filename, lua_tostring(L, -1));
	
		int top = lua_gettop(L);
		lua_getglobal(L, "Shop");
		ret = lua_pcall(L, 0, 0, NULL);
		//PrintStack(L);
		if (ret != 0)
		{
			printf("error: \"%s\" %s\n", filename, lua_tostring(L, -1));
			lua_pop(L, 1);
			printf("<エンターキーを押すとスクリプトを読み直します>\n");
			getchar();
		}
		else
		{
			break;
		}
		lua_settop(L, top);
	}
	lua_close(L);
} 
