/*
 * Author: sappy5678
 * Detail: 解析器
 */
#include <csignal>
#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <string>
#include <fstream>
#include  "global_variables.h"
#include "Lexical_Analyzer.hpp"
#include "tools.hpp"
using namespace std;
void init()
{
	for (int i = 0; i < 10; ++i)
	{
		special_table.push_back(table_row());
		special_table[i].name = i;
		special_table[i].value = 0;
	}
}

int start();
int stmtseq();
int stmtseqlist();
int assignment();
int expr();
int term();
int moreterm();
int factor();
int morefactors();
int match(string m);
vector<table_row> special_table;
vector<string> special_name =
{
	"error","eof",";","=","or","and","(",")","true","false"
};
vector<string> id_name;
vector<table_row> id_table;
fstream fin, fout;
int line_position = 0;
int character_position = 0;
token lookahead;


/**
 * \brief 標誌起始區
 * \return statment_code(int)
 */
int start()
{
	stmtseq();
	match("eof");

	// action dumpIDs
	cout << "% % IDs: ";
	for(int i = 0 ; i < id_table.size();++i)
	{
		cout << "\t" << get_name(ID,i);
	}

	return 0;
}


int stmtseq()
{
	assignment();
	stmtseqlist();
	return 0;
}

int stmtseqlist()
{
	if (get_name(lookahead) == ";")
	{
		match(";");
		assignment();
		stmtseqlist();
	}
	else
	{

	}
	return 0;
}

int assignment()
{
	if (lookahead.type == ID)
	{
		// match id
		// lookahead = lexical_analyzer();

		// action emit "push lvalue" + id.lexeme
		// and goto next lexical
		fout << "push lvalue " + get_name(lookahead) << endl;

		// match id
		lookahead = lexical_analyzer();

		match("=");
		expr();

		// action emit "="
		fout << "=\n";
	}
	else
	{

	}
	return 0;
}

int expr()
{
	term();
	moreterm();

	return 0;
}

int moreterm()
{
	if(get_name(lookahead) == "or")
	{
		match("or");
		term();

		// emit "or"
		fout << "or\n";

		moreterm();
	}
	else
	{

	}

	return 0;
}

int term()
{
	factor();
	morefactors();

	return 0;
}

int morefactors()
{
	if (get_name(lookahead) == "and")
	{
		match("and");
		factor();

		// emit "and"
		fout << "and\n";

		morefactors();
	}
	else
	{

	}

	return 0;
}

int factor()
{
	if (get_name(lookahead) == "(")
	{
		match("(");
		expr();
		match(")");
	}
	else if (get_name(lookahead) == "true")
	{
		match("true");

		// emit "push true"
		fout << "push true\n";
	}
	else if (get_name(lookahead) == "false")
	{
		match("false");

		// emit "push ture"
		fout << "push false\n";
	}
	else if (lookahead.type == ID)
	{
		
		// emit "push rvalue" + id.lexeme
		fout << "push rvalue " + get_name(lookahead) << endl;
		lookahead = lexical_analyzer();
	}
	else
	{
		throw(string("Unknow Error."));
	}

	return 0;
}


/**
 * \brief try to match terminal or return error
 * \param m (string)
 * \return statment_code(int)
 */

int match(string m)
{
	if(get_name(lookahead) == m)
	{
		lookahead = lexical_analyzer();
		return 0;
	}
	else
	{
		throw(string("maybe " + m));
		return 1;
	}
}

void Error_Message(string type,string msg)
{
	cout << "[" + type +"]\t" << msg << "\tin line " << line_position << " , " << character_position << endl;
	return;
}
int main(int argc, char* argv[])
{
	init();
	fin.open(argv[1],ios::in);
	fout.open(argv[2], ios::out);
	
	if (!fin)
	{
		Error_Message("Error", "No such file or directory");
		system("pause");
		return 0;
	}
	lookahead = lexical_analyzer();
	if (lookahead.type == SPECIAL && lookahead.id == 1)
	{
		Error_Message("Error", "The File can't be empty");
	}
	else
	{
		try {
			start();
		}
		catch(string e)
		{
			Error_Message("Error", e);
		}
		catch (Unknow_token e)
		{
			
		}
	}

	fin.close();
	fout.close();
	system("pause");
	return 0;
}


#endif
