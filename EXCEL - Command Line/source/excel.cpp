
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include <ctype.h>
#include<errno.h>
#include<stack>
#include<iostream>
#include"excel.h"
#include"ExcelDS.h"
#include"excelUtil.h"

using namespace std;

//DISPLAY FUNCTIONS
void initGreeting()
{
	printf("--------------Welcome to excel application-------------------\n\n");
	printf("Type \"help\" for list of commands");
}


void ListOfCommands()
{
	printf("\t\nSET\t--\tSet cell data\nGET\t--\tget cell data\nPRINT\t--\t");
	printf("prints the sheet \nEXPORT\t--\texport to different file\nIMPORT\t--\timport data from file\n");
	printf("EVAL\t--\tEvaluates a given expression\nSAVE\t--\tSaves current sheet into an imported file\n");
	printf("\nARITHMETIC FUNCTIONS\n");
	printf("SUM\t--\tSum of row or column\n");
	printf("AVG\t--\tAverage of row or column\n");
	printf("MAX\t--\tMax of row or column\n");
	printf("MIN\t--\tMin of row or column\n\n");
	printf("EXIT\t--\texit the application \nHELP\t--\tget list of commands\n");
}

void printSymbol()
{
	printf("\n> ");
	return;
}

//-------------------------

//INPUT FUNCTIONS
int isNumber(char* s)
{
	for (int i = 0; i < s[i]!='\0'; i++)
		if (isdigit(s[i]) == 0)
			return 0;

	return 1;
}

int getIntFromUser()
{
	int val;
	scanf("%d", &val);
	return val;
}

char* getInputFromUser()
{
	char* input = (char*)malloc(10);
	scanf("%s", input);
	//printf("!%s!", input);
	for (int i = 0; input[i] != '\0'; i++)
	{
		input[i] = tolower(input[i]);
	}
	return input;
}

char* getCommandFromUser()
{
	int i = 0;
	char* input = (char*)malloc(100 * sizeof(char));
	int input_i = 0;
	int trail = 1;
	for ( i = 0; i < 100; i++)
	{
		char temp;
		temp = getchar();
		if (trail && temp == ' ')
		{
			continue;
		}
		if (temp == ' ' || temp=='\n')
		{
			break;
		}
		trail = 0;
		temp = tolower(temp);
		input[input_i++] = temp;
	}
	input[input_i] = '\0';
	return input;
}

//---------------------------------------


//  ------------EXPRESSION EVALUATOR-----------
int precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

int applyOp(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0)
		{
			printf("Error : Division by 0 not allowed");
			return NULL;
		}
		return a / b;
	}
}

int evalExpression(cell * *sheet, char* eval)
{
	if (!strcmp(eval, ""))
	{
		return 0;
	}
	stack <int> values;
	stack <char> ops;
	int p = 0;
	while (eval[p] != '\0')
	{
		if (eval[p] == '(')
		{
			ops.push(eval[p]);
		}
		else if (eval[p] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
				if (values.top() == NULL)
				{
					return NULL;
				}
			}
			ops.pop();
		}
		else if (eval[p] >= 'a' && eval[p] <= 'z')
		{
			int row = 0;
			int col = 0;
			col = eval[p] - 'a';
			row = eval[p + 1] - '0';
			row--;
			if (strcmp(sheet[row][col].dependency, ""))
			{
				int val = evalExpression(sheet, sheet[row][col].dependency);
				if (val == NULL)
				{
					return NULL;
				}
				sheet[row][col].data = val;
			}
			values.push(sheet[row][col].data);
			p += 2;
			continue;
		}
		else if (isdigit(eval[p]))
		{
			int val = 0;
			while (eval[p] != '\0' && isdigit(eval[p]))
			{
				val = (val * 10) + (eval[p] - '0');
				p++;
			}
			values.push(val);
			continue;
		}
		else
		{
			while (!ops.empty() && precedence(ops.top())
				>= precedence(eval[p])) {
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			ops.push(eval[p]);
		}
		p++;
	}
	while (!ops.empty())
	{
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}
	return values.top();

}
//----------------------------------------------


//---------------COMMAND FUNTCIONS----------------------

//SET CELL
void setCell(cell **sheet)
{
	int row, col;
	while ((col = getchar()) == ' ' || col == '\n');
	col = tolower(col);
	col = col - 97;
	scanf("%d", &row);
	row--;
	char middle;
	scanf("%c", &middle);
	if (middle == ' ')
	{
		char* data = (char*)malloc(20);
		scanf("%s",data);
		if (isNumber(data))
		{
			printf("Number");
			sheet[row][col].data_type = 1;
			sheet[row][col].data = atoi(data);
			strcpy(sheet[row][col].s_data, "");
		}
		else
		{
			sheet[row][col].data_type = 2;
			sheet[row][col].s_data = data;
			sheet[row][col].data = 0;
		}
	}
	else
	{
		char* cellInput = (char*)malloc(25);
		scanf("%[^\n]s", cellInput);
		printf("%s\n",cellInput);
		if (cellInput[0] == '"')
		{
			cellInput++;
			sheet[row][col].data_type = 2;
			strcpy(sheet[row][col].s_data, cellInput);
			sheet[row][col].s_data[strlen(cellInput)-1]='\0';
		}
		else
		{
			strcpy(sheet[row][col].dependency, cellInput);
		}
	}
	return;
}

//GET FUNCTION
void getCell(cell **sheet)
{
	char* arg = getInputFromUser();
	int row = arg[1] - 48;
	int col = arg[0] - 97;
	row--;
	//printf("rowg=%d colg=%d", row, col);
	if (sheet[row][col].data_type == 1)
	{
		if (strcmp(sheet[row][col].dependency, ""))
		{
			int res = evalExpression(sheet, sheet[row][col].dependency);
			if(isdigit(res))
			if ( res == NULL)
			{
				return;
			}
			sheet[row][col].data = res ? res : sheet[row][col].data;
		}
		printf("%d\n", sheet[row][col].data);
	}
	else
	{
		printf("%s\n", sheet[row][col].s_data);
	}
	printf("%s", sheet[row][col].dependency);

	return;
}

//IMPORT FUNCTION
char* importExcel(cell **sheet)
{
	const char* mode = "r";
	char* filename = getInputFromUser();
	char* filename_d = (char*)malloc(strlen(filename) + 3);
	FILE* fp,*fp_d;
	int i, j;
	char* checker = (filename + strlen(filename) - 4);
	if (strcmp(checker, ".csv"))
	{
		strcpy(filename_d, filename);
		strcat(filename_d, "_d.csv");
		filename = strcat(filename, ".csv");
	}
	else
	{
		strcat(filename_d, filename);
	}

	if ((fp = fopen(filename, mode)) == NULL)
	{
		printf("File does not exist\n");
		fclose(fp);
		return NULL;
	}
	fp = fopen(filename, mode);
	fp_d = fopen(filename_d,mode);

	char junk = 0;
	int k = 0;
	for (i = 0; i < _ROWS; i++)
	{
		k = 0;
		for (j = 0; j < _COLS; j++)
		{
			fscanf_s(fp, "%d", &sheet[i][j].data);
			fscanf_s(fp_d, "%[^,]", sheet[i][j].dependency);
			if (j < _COLS - 1)
			{
				fscanf_s(fp, "%c", &junk);
				//fscanf_s(fp_d, "%c", &junk);
			}
		}
		fscanf_s(fp, "%c", &junk);
		fscanf_s(fp_d, "%c", &junk);
	}
	
	fclose(fp);
	fclose(fp_d);
	return filename;
}

//EXPORT FUNCTION
void exportExcel(cell **sheet,char* file)
{
		char* filename=(char*)malloc(20);
		char* filename_d;
		if (strcmp("",file))
		{
			strcpy(filename, file);
		}
		else
		{
			filename= getInputFromUser();
		}
		filename_d = (char*)malloc(strlen(filename) + 3);
		strcpy(filename_d, "");
		FILE *fp,*fp_d;
		int i,j;
		char* checker = (filename + strlen(filename) - 4);
		//printf("%s\n", checker);
		if (strcmp(checker, ".csv"))
		{	
			strcpy(filename_d, filename);
			strcat(filename_d, "_d.csv");
			filename = strcat(filename, ".csv");
		}
		else
		{
			int i = 0;
			for (i = 0; filename[i] != '.'; i++)
			{
				filename_d[i] = filename[i];
			}
			filename_d[i] = '\0';
			strcat(filename_d, "_d.csv\0");
		}
		if ((fp=fopen(filename,"r"))!=NULL)
		{
			printf("File already exists. Do you want to overwrite (y/n) ?\n");
			printSymbol();
			char* ans = (char*)malloc(10);
			scanf("%s", ans);
			for (i = 0; ans[i]!='\0'; i++)
				ans[i] = tolower(ans[i]);
			fclose(fp);
			if (!strcmp(ans, "no") || !strcmp(ans,"n"))
			{
				return;
			}
		}
		fp = fopen(filename, "w");
		fp_d = fopen(filename_d, "w");

		for (i = 0; i < _ROWS; i++)
		{
			for (j = 0; j < _COLS; j++)
			{
				fprintf(fp, "%d,",sheet[i][j].data);
				fprintf(fp_d, "%s,", sheet[i][j].dependency);
			}
			fprintf(fp, "%c",'\n');
			fprintf(fp_d, "%c", '\n');
		}
		printf("Successfully overwritten");
		fclose(fp);
		fclose(fp_d);
}

//EVAL FUNCTION
int eval(cell** sheet,char *expression)
{
	return evalExpression(sheet, expression);
}

//COMMAND PARSER
int parseCommand(char* command,cell** sheet,char* filename)
{
	if (!strcmp(command,"get")) 
	{
		getCell(sheet);
		return 0;
	}
	else if (!strcmp(command,"set")) 
	{
		setCell(sheet);
		fflush(stdin);
		return 0;
	}
	else if (!strcmp(command, "print")) 
	{
		printCellMatrixExcel(sheet, _ROWS, _COLS);
		return 0;
	}
	else if (!strcmp(command,"export")) 
	{
		strcpy(filename,"");
		exportExcel(sheet,filename);
		return 0;
	}
	else if (!strcmp(command,"import")) 
	{
		strcpy(filename,importExcel(sheet));
		return 0;
	}
	else if (!strcmp(command, "save"))
	{
		if (!strcmp(filename,""))
		{
			exportExcel(sheet,filename);
		}
		return 0;
	}
	else if (!strcmp(command, "exit")) 
	{
		return 1;
	}
	else if (!strcmp(command, "help"))
	{
		ListOfCommands();
		return 0;
	}
	else if (!strcmp(command, "eval"))
	{
		char* expression = (char*)malloc(20);
		expression = getInputFromUser();
		int val = eval(sheet, expression);
		if (val == NULL)
		{
			return 0;
		}
		printf("%d",val);
		free(expression);
		return 0;
	}
	else if (!strcmp(command, "sum")) {
		int output = sum(sheet);
		printf("%d", output);
		return 0;
	}
	else if (!strcmp(command, "avg")) {
		float output = avg(sheet);
		printf("%f", output);
		return 0;
	}
	else if (!strcmp(command, "max")) {
		int output = max(sheet);
		printf("%d", output);
		return 0;
	}
	else if (!strcmp(command, "min")) {
		int output = min(sheet);
		printf("%d", output);
		return 0;
	}
	else {
		printf("Invalid command!");
		return 0;
	}
}

void excel()
{
	cell** sheet = allocateCellMatrix(10, 10);
	char* filename = (char*)malloc(20);
	strcmp(filename,"");
	initGreeting();
	do
	{
		
		printSymbol();
		char* command = getCommandFromUser();
		if (!strcmp(command, ""))
		{
			command = getCommandFromUser();
		}
		if (parseCommand(command, sheet,filename))
		{
			break;
		}
		strcpy(command, "");
	} while (1);
}

void testing_func()
{
	return;
}