/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/

#ifndef PUSH_H
#define PUSH_H

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


//declare varaible in .data
void add_variable(string temp, long* tempNum, long type)
{
	string der;

	if(type == 1) der = "0.0";
	else der = "0";

	cout << "jmp var" << *tempNum << "\n\t SECTION .data\n\t "
	<< temp << ": dq " << der << "\n\t SECTION .text \n\t var" << *tempNum << ":\n";

	(*tempNum)++;
}

//push long value
void push_int(string temp)
{
	cout << "\t push QWORD " << temp << "\n";
}

//push any variable
void push_var(string temp)
{
	cout << "\t push QWORD [" << temp << "]\n";
}

//push raw string value. requires making an entry in .data first and then pushing the variable
void push_string(char* value, long *tempNum)
{
	cout << "jmp jump" << *tempNum  << endl;
	cout << "SECTION .data" << endl;
	cout << "var" << *tempNum << ": dq \"" << value << "\", 0" << endl;
	cout << "SECTION .text"  << endl;
	cout << "jump" << *tempNum << ":" << endl;

	cout << "	push var" << *tempNum << endl;
	(*tempNum)++; 
}

//push a float value. appends .0 to numbers without a decimal portion
void push_float(string temp, long *tempNum)
{

	int flag = 1;
	for(int i = 0; i < temp.length(); i++)
	{
		if( (temp.at(i)) == '.' )
		{
			flag = 0; break;
		}
	}

	if(flag == 1)
	{
		temp = temp + ".0";
	}

	cout << "jmp jump" << *tempNum  << endl;
	cout << "SECTION .data" << endl;
	cout << "var" << *tempNum << ": dq " << temp << endl;
	cout << "SECTION .text"  << endl;
	cout << "jump" << *tempNum << ":" << endl;

	cout << "	push QWORD [var" << *tempNum << "]"<< endl;

	(*tempNum)++; 
}

#endif
