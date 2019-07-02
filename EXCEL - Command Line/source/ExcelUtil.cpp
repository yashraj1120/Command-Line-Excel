#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"excelUtil.h"
#include"ExcelDS.h"


//Sum of a row or column
int sum(cell **sheet)
{
	char dir;
	scanf("%c", &dir);
	int sum = 0;
	if (isdigit(dir))
	{
		dir = dir - 48;
		dir--;
		for (int i = 0; i < _COLS; i++)
		{
			if (sheet[dir][i].data_type == 1)
			{
				sum += sheet[dir][i].data;
			}
		}
	}
	else
	{
		dir = dir - 97;
		for (int i = 0; i < _ROWS; i++)
		{
			if (sheet[i][dir].data_type == 1)
			{
				sum += sheet[i][dir].data;
			}
		}
	}
	return sum;
}


//Average of a row or column
float avg(cell **sheet)
{
	int sum_v = sum(sheet);
	return (float)sum_v/_ROWS;
}


//Max value in a row or column
int max(cell **sheet)
{
	char dir;
	scanf("%c", &dir);
	int max_val= INT_MIN;
	if (isdigit(dir))
	{
		dir = dir - 48;
		dir--;
		for (int i = 0; i < _COLS; i++)
		{
			if (sheet[dir][i].data_type == 1)
			{
				int t = sheet[dir][i].data;
				max_val = max_val >=  t? max_val : t;
			}
		}
	}
	else
	{
		dir = dir - 97;
		for (int i = 0; i < _ROWS; i++)
		{
			if (sheet[i][dir].data_type == 1)
			{
				int t = sheet[i][dir].data;
				max_val = max_val >= t ? max_val : t;
			}
		}
	}
	return max_val;
}


//Min value in a row or column
int min(cell **sheet)
{
	char dir;
	scanf("%c", &dir);
	int min_val = INT_MAX;
	if (isdigit(dir))
	{
		dir = dir - 48;
		dir--;
		for (int i = 0; i < _COLS; i++)
		{
			if (sheet[dir][i].data_type == 1)
			{
				int t = sheet[dir][i].data;
				min_val = min_val <= t ? min_val : t;
			}
		}
	}
	else
	{
		dir = dir - 97;
		for (int i = 0; i < _ROWS; i++)
		{
			if (sheet[i][dir].data_type == 1)
			{
				int t = sheet[i][dir].data;
				min_val = min_val <= t ? min_val : t;
			}
		}
	}
	return min_val;
}