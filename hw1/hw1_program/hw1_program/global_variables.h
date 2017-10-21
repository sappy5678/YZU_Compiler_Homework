#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<utility>
#include <vector>
#include "Struct.h"
#define ERROR -1
#define SPECIAL 0
#define ID 1

using namespace std;




// token 結構


extern vector<table_row> special_table;

extern vector<string> special_name;


extern vector<string> id_name;

extern vector<table_row> id_table;

extern fstream fin, fout;




// 標記行數用的

extern int line_position;

extern int character_position;




#endif
