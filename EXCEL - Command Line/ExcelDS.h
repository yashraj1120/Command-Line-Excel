#ifndef _excelds
#define _excelds

#define _ROWS 10
#define _COLS 10

//------------CELL MATRIX------------

typedef struct cell
{
	int data_type;
	char* s_data;
	int data;
	char* dependency;
}cell;

cell** allocateCellMatrix(int, int);
void printCellMatrixExcel(cell**, int m, int n);

//--------------------------------------------

//Array Functions
void printArray(int* arr, int n);
int* arrInput(int);
int sumOfArray(int a[], int n);

//Matrix Functions
int** allocateMatrix(int, int);
int** matrixInput(int, int);
void printMatrix(int** a, int m, int n);
void printMatrixExcel(int**,int m,int n);
int** multiply_matrix(int** a, int** b, int m, int n, int p);

#endif // !_excelds