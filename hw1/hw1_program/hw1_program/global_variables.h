#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<utility>
#include <vector>
#define ERROR -1
#define SPECIAL 0
#define ID 1

using namespace std;
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H


struct table_row
{
	int name;
	int value;
};

extern vector<table_row> special_table;
extern vector<string> special_name;
extern vector<string> id_name;
extern vector<table_row> id_table;
extern fstream fin;
fstream fin;
vector<string> special_name =
{
	"error","eof",";","=","or","and","(",")","true","false"
};

vector<table_row> special_table;
vector<string> id_name;
vector<table_row> id_table;

void init()
{

	for (int i = 0; i < 10; ++i)
	{		
		special_table.push_back(table_row());
		special_table[i].name = i;
		special_table[i].value = 0;
	}

}


#endif
