/**
 * Header file for red_black.cpp
 * It contains the function references as well as the structs for
 * the function pointers for reader and changer
 *
 */
#include "red_black.h"
struct reader{
	bool (*read_func)(int);
	int param;
};
struct changer{
	void (*change_func)(int);
	int param;
};
void push_func(string job);
struct reader pull_reader();
struct changer pull_changer();
string spull_changer();
string spull_reader();
void spush_func(string job);
