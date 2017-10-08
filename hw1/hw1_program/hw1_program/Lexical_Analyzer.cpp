#include <iostream>
#include <string>
#include<utility>
#include <fstream>
#include "global_variables.h"
using namespace std;
// Todo 例外捕捉

pair<int, int> lexical_analyzer();
pair<int, int> lookup(string x);
bool is_number(const char n);
bool is_number(string n);
bool is_alphabet(const char n);
bool is_alphabet(string n);
bool is_id(const char n);
bool is_id(string n);
bool is_terminal(const char n);
bool is_empty(const char n);

// Just for test
int main(int argc, char* argv[])
{
	init();
	fin.open(argv[1]);
	for (unsigned i = 0;  ; ++i)
	{
		pair<int, int> tmp = lexical_analyzer();
		if (tmp.first == SPECIAL && tmp.second == 1)
			break;
		if (tmp.first == 1)
			cout << "< ID , " << tmp.second << ">，Value = '" << id_name[id_table[tmp.second].name] << "'" << endl;
		else
			cout << "< SPECIAL , " << tmp.second << ">，Value = '" << special_name[special_table[tmp.second].name] << "'" << endl;
	}

	system("pause");
}

/**
 * \brief input string and return token <type,index>
 * \return token<type,index> -> pair<int,int>  
 */
pair<int,int> lexical_analyzer()
{
	// 用來描述目前 lexical analyzer 的狀態
	// state = -1 代表是目前出現了錯誤
	// state = 0 代表是目前讀的是特殊符號
	// state = 1 代表是目前讀的是ID 以及 and or true flase 等
	// int state;

	string lexeme = "";
	char next_character;	

	// 跳過空字元
	while(fin.get(next_character))
	{
		if (!::is_empty(next_character))
			break;
	}
	// 檢查 EOF
	if (fin.eof())
		return lookup("eof");
	lexeme += next_character;
	// 看是不是特殊字元，是的話直接回傳
	if (is_terminal(lexeme[0]))
		return lookup(lexeme);

	// 補完ID or true or and false等剩下的部分
	while (fin.get(next_character))
	{
		if (::is_empty(next_character))
		{
			break;
		}
		else if (is_terminal(next_character))
		{
			fin.unget();
			break;
		}
		else 
			lexeme += next_character;
	}
	return lookup(lexeme);
}



pair<int, int> lookup(const string x)
{
	// 先看看有沒有在關鍵字 + 特殊符號表中
	for(unsigned i = 0 ; i < special_table.size(); ++i)
	{
		if (x == special_name[i])
			return pair<int, int>(SPECIAL, i);
	}

	// 沒有的話再去 ID 表查
	for (unsigned i = 0; i < id_table.size(); ++i)
	{
		if (x == id_name[i])
			return pair<int, int>(ID, i);
	}

	// 都沒有就去 把它放在 ID 表中
	id_name.push_back(x);
	id_table.push_back(table_row({ int(id_name.size()) - 1,0}));
	
	
	return { ID,id_table.size()-1};
}

bool is_number(const char n)
{
	if (n >= '0' && n <= '9')
		return true;
	else
		return false;
}

bool is_number(string n)
{
	for(unsigned i = 0;i < n.size();++i)
	{
		if (!is_number(n[i]))
			return false;
	}

	return true;
}

bool is_alphabet(const char n)
{
	// 大寫字母
	if (n >= 'A' && n <= 'Z')
		return true;
	// 小寫字母
	else if (n >= 'a' && n <= 'z')
		return true;
	else
		return false;
}

bool is_alphabet(string n)
{
	for (unsigned i = 0; i < n.size(); ++i)
	{
		if (!is_alphabet(n[i]))
			return false;
	}

	return true;
}

bool is_id(const char n)
{
	// 字母
	if (is_alphabet(n))
		return true;
	// 數字
	else if (is_number(n))
		return true;
	// 下底線
	else if (n == '_')
		return true;
	else
		return false;
}

bool is_id(string n)
{
	for (unsigned i = 0; i < n.size(); ++i)
	{
		if (!is_id(n[i]))
			return false;
	}

	return true;
}

bool is_terminal(const char n)
{
	if (n == ';' || n == '='|| n == '(' || n == ')')
	{
		return true;
	}
	return false;
}

bool is_empty(const char n)
{
	if (n == ' ' || n == '\n' || n == '\t')
	{
		return true;
	}
	return false;
}