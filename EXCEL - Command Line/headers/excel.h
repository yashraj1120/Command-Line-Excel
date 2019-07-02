#ifndef _excelcli

#define _excelcli

#include"ExcelDS.h"

int eval(cell**, char* eval);

int evalExpression(cell**, char* eval);

int getIntFromUser();

void setCell(cell** );

void getCell(cell** );

void initGreeting();

void ListOfCommands();

void printSymbol();

void excel();

char* getCommandFromUser();

int parseCommand(char*,cell **,char*);

void exportExcel(cell**,char*);

char* importExcel(cell** );

char* getInputFromUser();

void testing_func();



#endif 