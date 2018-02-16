#ifndef sysfunc_h
#define sysfunc_h

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdio>
#include<string>

using namespace std;
void swap(char &a, char &b);
char* toStr(int i);
string tidy(string a);

#endif