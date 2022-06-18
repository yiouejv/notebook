#include <iostream>
#include <lua.hpp>
using namespace std;


lua_State* L;

int main(int argc, char const *argv[])
{
    L = luaL_newstate();
    luaL_openlibs(L);
    //luaL_dostring(L, "print('hello')");
    luaL_dostring(L, "local 我 = 1;\n print(我)");
    cout << "我" << endl;
    return 0;
}