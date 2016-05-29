/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/


#ifndef PRINTSTUFF_H
#define PRINTSTUFF_H

#include <iostream> //for files
#include <fstream> //for the goddamn files
#include <string>
#include <sstream> //for string stream
#include <stdlib.h>

using namespace std;

//puts the boilers for text and data section in the text and data files, previously created by the makefile
void print_boiler()
{
	//data
	ifstream boiler("boiler.txt", ios::in);

	string line;

	while(1)
	{
		getline(boiler, line);
		if(boiler.eof()) break;
		istringstream stream(line);
		cout << line << endl;
	}

	boiler.close();
	
}

void print_end()
{
	cout << "mov eax, 0\n leave\n ret\n";
	
}


/*
	this function performs part of the syntax directed translation which prints out a float or a long
using printf. it assumes that the value to be printed is on top of the x86 stack, yes even if its a float. 
*/
void print(long type, int newLine, string scope)
{
		switch(type)
		{
			case 0:
				if(newLine == 1)
					cout << "	mov edi, fmt_decimal_nl" << endl;
				else
					cout << "	mov edi, fmt_decimal" << endl;
				cout << "	pop rsi" << endl;
				cout << "	mov rax, 0" << endl;
				cout <<"	call printf" << endl;
				break;
			case 1:	
				cout << "	pop rax" << endl;
				cout << "	mov [rbp-8], rax\n";
				//cout << "	push rax\n";
				cout << "	movsd xmm0, [rbp - 8]" << endl;
				if(newLine == 1)
					cout << "	mov edi, fmt_float_nl" << endl;
				else
					cout << "	mov edi, fmt_float" << endl;
				cout << "	mov eax, 1\n\t" << endl;
				cout <<"	call printf" << endl;
				//cout << "	pop rax\n";
				break;
			case 2: //string
				if(newLine == 1)
					cout << "	mov edi, fmt_string_nl" << endl;
				else
					cout << "	mov edi, fmt_string" << endl;
				cout << "	pop rsi" << endl;
				cout << "	mov rax, 0" << endl;
				cout <<"	call printf" << endl;
				break;
			case 3: // booleann
				if(newLine == 1)
					cout << "	mov edi, fmt_decimal_nl" << endl;
				else
					cout << "	mov edi, fmt_decimal" << endl;
				cout << "	pop rsi" << endl;
				cout << "	mov rax, 0" << endl;
				cout <<"	call printf" << endl;
				break;
			default:
				break;
		}

		return;

}

#endif
