#pragma once
#ifndef STRUCT_H
#define STRUCT_H
struct token
{
	int type;
	int id;
};

struct Unknow_token
{
	int type;
	int id;
};
// 表的資料結構
struct table_row
{
	int name;
	int value;
};
#endif
