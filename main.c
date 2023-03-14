#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

// スタックを見る関数
void printStack(lua_State *L) {
    // スタック数を取得
    const int num = lua_gettop(L);
    if (num == 0) {
        printf("No stack.\n");
        return;
    }
    for (int i = num; i >= 1; i--) {
        printf("%03d(%04d): ", i, -num + i - 1);
        int type = lua_type(L, i);
        switch(type) {
        case LUA_TNIL:
            printf("NIL\n");
            break;
        case LUA_TBOOLEAN:
            printf("BOOLEAN %s\n", lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TLIGHTUSERDATA:
            printf("LIGHTUSERDATA\n");
            break;
        case LUA_TNUMBER:
            printf("NUMBER %f\n", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("STRING %s\n", lua_tostring(L, i));
            break;
        case LUA_TTABLE:
            printf("TABLE\n");
            break;
        case LUA_TFUNCTION:
            printf("FUNCTION\n");
            break;
        case LUA_TUSERDATA:
            printf("USERDATA\n");
            break;
        case LUA_TTHREAD:
            printf("THREAD\n");
            break;
        }
    }
    printf("-----------------------------\n\n");
}

void test_init(){
    lua_State *L = luaL_newstate();
    if(luaL_dofile(L, "main.lua")) {
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return;
    }

    lua_getglobal(L,"windowWidth");
    lua_getglobal(L,"windowHeight");
    lua_getglobal(L,"windowName");

    printStack(L);

    // printStack(L);
    int num = lua_gettop(L);
    lua_pop(L,num);
}

void test_callLuaFunc() {
    lua_State *L = luaL_newstate();
    if(luaL_dofile(L, "main.lua")) {
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return;
    }
    lua_getglobal(L, "calc");
    lua_pushnumber(L, 100);
    lua_pushnumber(L, 200);

    printStack(L);

    if(lua_pcall(L,2,4,0)) {
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return;
    }
    printStack(L);

    float add_res = (float)lua_tonumber(L,1);
    float sub_res = (float)lua_tonumber(L,2);
    float mult_res = (float)lua_tonumber(L,3);
    float dev_res = (float)lua_tonumber(L,4);
    // lua_pop(L,L);
    // printStack(L);
    int num = lua_gettop(L);
    lua_pop(L,num);
    lua_close(L);
}

// float Linear(float t, float start, float end){
//     return (1-t) * start + t*end;
// }

int Linear(lua_State *L){
    float start = (float)lua_tonumber(L,1);
    float end = (float)lua_tonumber(L,2);
    float t = (float)lua_tonumber(L,3);

    float res = (1-t)*start + t*end;

    lua_pop(L,lua_gettop(L));

    lua_pushnumber(L,res);
    printf("%lf\n", res);
    return 1;
}

// void test_coroutine() {
//     lua_State * L = luaL_newstate();
//     luaopen_base(L);

//     if(luaL_dofile(L, "main.lua")) {
//         printf("%s\n", lua_tostring(L,lua_gettop(L)));
//         lua_close(L);
//         return;
//     }
//     lua_State *co = lua_newthread(L);
//     lua_getglobal(co, "step");

//     while(lua_resume(co, 0)) {
//         printStack(L);
//         _getch();
//     }
//     lua_close(L);
// }

int FuncC(lua_State *L){
    return 0;
}

int main(void) {
    // char buf[256];
    // int error;
    lua_State *L = luaL_newstate();
    // lua_pushboolean(L, 1);
    // lua_pushnumber(L, 100.0);
    // lua_pushstring(L, "Marupeke");

    // printStack(L);

    // lua_close(L);

    // test_init();
    test_callLuaFunc();
    // test_coroutine();
    
    lua_register(L, "Linear", &Linear);

    if(luaL_dofile(L, "main.lua")){
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return 0;
    }
    lua_getglobal(L,"glue_test");
    printStack(L);
    if (lua_pcall(L,0,0,0)){
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return 0;
    }
    lua_close(L);
    // lua_register(L, "FuncC", &FuncC);
    return 0;
}