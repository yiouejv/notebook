/*
 *Author: yiouejv
 *Email: yiouejv@126.com
 *Time: 2022-06-12 15:24:24
 *Name: 1.cpp
*/
#include<iostream>
using namespace std;


void print()
{}

template<class T, class... Types>
void print(const T& firstArg, const Types&... args)
{
        cout << "template<class T, class... Types>" << endl;
}

template<class... Types>
void print(const Types&... args)
{
        cout << "template<class... Types>" << endl;
}


int main(int argc, const char *argv[]) {
    return 0;
}
