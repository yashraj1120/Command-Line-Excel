
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ExcelDS.h"
#include"excel.h"


cell** allocateCellMatrix(int m, int n)
{
	cell** temp = (cell * *)malloc(m * sizeof(cell*));
	for (int i = 0; i < m; i++)
	{
		temp[i] = (cell*)malloc(n * sizeof(cell));
		for (int j = 0; j < n; j++)
		{
			temp[i][j].data_type = 1;
			temp[i][j].data = 0;
			temp[i][j].dependency = (char*)malloc(20);
			temp[i][j].s_data= (char*)malloc(20);
			strcpy(temp[i][j].dependency, "");
			strcpy(temp[i][j].s_data, "");
		}
	}
	return temp;
}

void printCellMatrixExcel(cell** mat, int m, int n)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < m; i++)
	{
		for (int k = 0; k < n; k++)
		{
			printf("------");
		}
		printf("\n|");
		for (j = 0; j < n; j++)
		{
			if (mat[i][j].data_type == 2)
			{
				printf("  %s  |", mat[i][j].s_data);
			}
			else
			{
				int res = evalExpression(mat, mat[i][j].dependency);
				mat[i][j].data = res ? res : mat[i][j].data;
				printf("  %d  |", mat[i][j].data);
			}
		}
		printf("\n");
	}
	for (int k = 0; k < n; k++)
	{
		printf("------");
	}
	printf("\n");
	return;
}

void printMatrix(int** a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int** allocateMatrix(int row_size, int col_size)
{
	int** temp = (int**)malloc(row_size * sizeof(int*));
	for (int i = 0; i < row_size; i++)
	{
		temp[i] = (int*)malloc(col_size * sizeof(int));
		for (int j = 0; j < col_size; j++)
		{
			temp[i][j] = 0;
		}
	}
	return temp;
}

int** matrixInput(int m, int n)
{
	int** temp = allocateMatrix(m, n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &temp[i][j]);
		}
	}
	return temp;
}

void printArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int* arrInput(int n)
{
	int* arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf("%d ", &arr[i]);
	}

	return arr;
}

int sumOfArray(int a[], int n)
{
	if (n == 0)
	{
		return a[n];
	}
	return a[n - 1] + sumOfArray(a, n - 1);
}

int** multiply_matrix(int** a, int** b, int m, int n, int p)
{
	int** t = allocateMatrix(m, p);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				t[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return t;
}

