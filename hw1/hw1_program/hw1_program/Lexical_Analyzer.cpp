#include <iostream>
#include <string>
#include<utility>
#include <fstream>
#include "global_variables.h"
using namespace std;
// Todo �ҥ~����

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
			cout << "< ID , " << tmp.second << ">�AValue = '" << id_name[id_table[tmp.second].name] << "'" << endl;
		else
			cout << "< SPECIAL , " << tmp.second << ">�AValue = '" << special_name[special_table[tmp.second].name] << "'" << endl;
	}

	system("pause");
}

/**
 * \brief input string and return token <type,index>
 * \return token<type,index> -> pair<int,int>  
 */
pair<int,int> lexical_analyzer()
{
	// �ΨӴy�z�ثe lexical analyzer �����A
	// state = -1 �N��O�ثe�X�{�F���~
	// state = 0 �N��O�ثeŪ���O�S��Ÿ�
	// state = 1 �N��O�ثeŪ���OID �H�� and or true flase ��
	// int state;

	string lexeme = "";
	char next_character;	

	// ���L�Ŧr��
	while(fin.get(next_character))
	{
		if (!::is_empty(next_character))
			break;
	}
	// �ˬd EOF
	if (fin.eof())
		return lookup("eof");
	lexeme += next_character;
	// �ݬO���O�S��r���A�O���ܪ����^��
	if (is_terminal(lexeme[0]))
		return lookup(lexeme);

	// �ɧ�ID or true or and false���ѤU������
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
	// ���ݬݦ��S���b����r + �S��Ÿ���
	for(unsigned i = 0 ; i < special_table.size(); ++i)
	{
		if (x == special_name[i])
			return pair<int, int>(SPECIAL, i);
	}

	// �S�����ܦA�h ID ��d
	for (unsigned i = 0; i < id_table.size(); ++i)
	{
		if (x == id_name[i])
			return pair<int, int>(ID, i);
	}

	// ���S���N�h �⥦��b ID ��
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
	// �j�g�r��
	if (n >= 'A' && n <= 'Z')
		return true;
	// �p�g�r��
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
	// �r��
	if (is_alphabet(n))
		return true;
	// �Ʀr
	else if (is_number(n))
		return true;
	// �U���u
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