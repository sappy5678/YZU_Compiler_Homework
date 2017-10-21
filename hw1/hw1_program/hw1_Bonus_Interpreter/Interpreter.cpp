#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#define VALUE 0
#define ID 1
struct value_row
{
	// 0 琌 计1琌跑计
	int type;

	// 计琌 boolean跑计琌id
	int value;
};

struct variable_row
{
	// lexicals(names_table)  id
	int id;

	// 计
	bool value;
};

stack<value_row> values_stack;
vector<variable_row> variables_table;
vector<string> names_list;
fstream fin;
variable_row lookup(const string x);
int main(int argc, char* argv[])
{
	fin.open(argv[1], ios::in);
	if (!fin)
	{
		cout << argv[1] << " Don't Exist\n";
	}
	string lookahead;
	variable_row tmp_variable;
	value_row tmp_value, tmp_value_1, tmp_value_2;
	while (fin >> lookahead)
	{
		if (lookahead == "push")
		{
			fin >> lookahead;
			if (lookahead == "lvalue")
			{
				fin >> lookahead;
				tmp_variable = lookup(lookahead);
				tmp_value = { ID,tmp_variable.id };

				values_stack.push(tmp_value);
			}
			else if (lookahead == "rvalue")
			{
				fin >> lookahead;
				tmp_variable = lookup(lookahead);
				tmp_value = { VALUE,tmp_variable.value };

				values_stack.push(tmp_value);
			}
			else if (lookahead == "true" || lookahead == "false")
			{
				if (lookahead == "true")
					values_stack.push({ VALUE,true });
				else if (lookahead == "false")
					values_stack.push({ VALUE,false });
			}
		}
		else if (lookahead == "or" || lookahead == "and")
		{
			if (lookahead == "or")
			{
				tmp_value_1 = values_stack.top();
				values_stack.pop();
				tmp_value_2 = values_stack.top();
				values_stack.pop();

				values_stack.push({ VALUE,tmp_value_1.value || tmp_value_2.value });
			}
			else if (lookahead == "and")
			{
				tmp_value_1 = values_stack.top();
				values_stack.pop();
				tmp_value_2 = values_stack.top();
				values_stack.pop();

				values_stack.push({ VALUE,tmp_value_1.value && tmp_value_2.value });
			}
		}
		else if (lookahead == "=")
		{
			tmp_value_1 = values_stack.top();
			values_stack.pop();
			tmp_value_2 = values_stack.top();
			values_stack.pop();

			variables_table[tmp_value_2.value].value = tmp_value_1.value;
		}
		else
		{

		}




	}
	for (int i = 0; i < variables_table.size(); ++i)
	{
		cout << names_list[variables_table[i].id] << ":\t" << bool(variables_table[i].value) << endl;
	}


	system("pause");
	return 0;

}
variable_row lookup(const string x)
{
	// Τ⊿ΤIDい
	for (unsigned i = 0; i < names_list.size(); ++i)
	{
		if (x == names_list[i])
			return variable_row({ int(i), variables_table[i].value });
	}


	// 常⊿Τ碞 рウ ID い
	names_list.push_back(x);
	variables_table.push_back(variable_row({ int(names_list.size()) - 1,false }));


	return { int(names_list.size()) - 1,false };
}