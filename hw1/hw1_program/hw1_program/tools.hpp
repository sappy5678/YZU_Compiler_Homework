
#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <iostream>
#include <string>
#include<utility>
#include <fstream>
#include "global_variables.h"
using namespace std;


inline string get_name(token t)
{
	if(t.type == ID)
		return id_name[id_table[t.id].name];
	else
		return special_name[special_table[t.id].name];
}

inline string get_name(int type,int id)
{
	if (type == ID)
		return id_name[id_table[id].name];
	else
		return special_name[special_table[id].name];
}


#endif // !TOOLS_HPP

