/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/


#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
using namespace std;

//logic functions ---------------------------------------------

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left == right and 0 otherwise

types of left and right must match
*/
void equ(long* tempNum)
{
	cout << "\t pop rax\n\t pop rbx\n\t xor rax, rbx\n\t jnz equ" << *tempNum
	<< "\n\t push QWORD 1\n\t jmp continue" << *tempNum << "\n"
	<< "equ" << *tempNum << ": \n\t push QWORD 0 \n continue" << *tempNum << ":\n";

	(*tempNum)++;
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left != right and 0 otherwise

types of left and right must match
*/
void nequ(int type, long* tempNum)
{
		cout << "\t pop rax\n\t pop rbx\n\t xor rax, rbx\n\t jnz equ" << *tempNum
		<< "\n\t push QWORD 0\n\t jmp continue" << *tempNum << "\n"
		<< "equ" << *tempNum << ": \n\t push QWORD 1 \n continue" << *tempNum << ":\n";

	(*tempNum)++;
}


/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left > 0 && right > 0, and 0 otherwise

types of left and right must match
*/
void conjunction(long* tempNum)
{
	cout << "\t pop rax \n\t pop rbx \n\t and rax, rbx \n\t jz and" << *tempNum 
	<< " \n\t mov rax, 1 \n\t push rax \n\t jmp continue" << *tempNum
	<< " \n\t and" << *tempNum << ": \n\t mov rax, 0 \n\t push rax"
	<< " \n\t continue" << *tempNum << ":\n\t";

	(*tempNum)++;
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left > 0 || right > 0, and 0 otherwise

types of left and right must match
*/
void disjunction(long* tempNum)
{

	cout << "\t pop rax \n\t pop rbx \n\t or rax, rbx \n\t jz or" << *tempNum 
	<< " \n\t mov rax, 1 \n\t push rax \n\t jmp continue" << *tempNum
	<< " \n\t or" << *tempNum << ": \n\t mov rax, 0 \n\t push rax"
	<< " \n\t continue" << *tempNum << ":\n\t";

	(*tempNum)++;
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left < right, and 0 otherwise

types of left and right must match
thankyou stack overflow http://stackoverflow.com/questions/27528930/compare-two-numbers-in-intel-x86-assembly-nasm
*/
void less_than(int type, long* tempNum)
{
	switch(type)
	{
		case 0:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jg LT" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t LT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		case 1:
			cout <<	"jmp LT_temp" << *tempNum << "\n\t SECTION .data\n\t"
			<<  "lvar" << *tempNum << ": dq 0.0\n\t "
			<< "rvar" << *tempNum << ": dq 0.0\n\t SECTION .text \n"
			<< "LT_temp" << *tempNum << ": \n\t pop QWORD [lvar" 
			<< *tempNum << "]\n\t pop QWORD [rvar"
			<< *tempNum << "]\n\t fld QWORD [lvar" << *tempNum
			<< "] \n\t fcomp QWORD [rvar"<< *tempNum << "] \n\t"
			<< "fstsw ax\n\t sahf \n\t jbe not_less" << *tempNum
			<< "\n\t push QWORD 1 \n\t jmp continue" << *tempNum
			<< "\n\t not_less" << *tempNum << ": \n\t push 	QWORD 0"
			<< "\n\t continue" << *tempNum << ": \n\t fstp QWORD [lvar"
			<< *tempNum << "] \n\t fstp QWORD [lvar" << *tempNum << "]\n";
			break;
		case 3:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jg LT" 
			<< *tempNum << " push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t LT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		default:
			break;
	}
	(*tempNum)++;
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left <= right, and 0 otherwise

types of left and right must match
*/
void lequ(int type, long* tempNum)
{
	switch(type)
	{
		case 0:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jge LE" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t LE" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		case 1:
			cout <<	"jmp LT_temp" << *tempNum << "\n\t SECTION .data\n\t"
			<<  "lvar" << *tempNum << ": dq 0.0\n\t "
			<< "rvar" << *tempNum << ": dq 0.0\n\t SECTION .text \n"
			<< "LT_temp" << *tempNum << ": \n\t pop QWORD [lvar" 
			<< *tempNum << "]\n\t pop QWORD [rvar"
			<< *tempNum << "]\n\t fld QWORD [lvar" << *tempNum
			<< "] \n\t fcomp QWORD [rvar"<< *tempNum << "] \n\t"
			<< "fstsw ax\n\t sahf \n\t jb not_l_e" << *tempNum
			<< "\n\t push QWORD 1 \n\t jmp continue" << *tempNum
			<< "\n\t not_l_e" << *tempNum << ": \n\t push 	QWORD 0"
			<< "\n\t continue" << *tempNum << ": \n\t fstp QWORD [lvar"
			<< *tempNum << "] \n\t fstp QWORD [lvar" << *tempNum << "]\n";
			break;
		case 3:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jge LE" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t LE" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		default:
			break;
	}
	(*tempNum)++;
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left >= right, and 0 otherwise

types of left and right must match
*/
void gequ(int type, long* tempNum)
{

	switch(type)
	{
		case 0:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jbe GE" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GE" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		case 1:
			cout <<	"jmp LT_temp" << *tempNum << "\n\t SECTION .data\n\t"
			<<  "lvar" << *tempNum << ": dq 0.0\n\t "
			<< "rvar" << *tempNum << ": dq 0.0\n\t SECTION .text \n"
			<< "LT_temp" << *tempNum << ": \n\t pop QWORD [lvar" 
			<< *tempNum << "]\n\t pop QWORD [rvar"
			<< *tempNum << "]\n\t fld QWORD [lvar" << *tempNum
			<< "] \n\t fcomp QWORD [rvar"<< *tempNum << "] \n\t"
			<< "fstsw ax\n\t sahf \n\t jbe _g_e" << *tempNum
			<< "\n\t push QWORD 0 \n\t jmp continue" << *tempNum
			<< "\n\t _g_e" << *tempNum << ": \n\t push 	QWORD 1"
			<< "\n\t continue" << *tempNum << ": \n\t fstp QWORD [lvar"
			<< *tempNum << "] \n\t fstp QWORD [lvar" << *tempNum << "]\n";
			break;
		case 3:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jbe GE" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GE" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		default:
			break;
	}
	(*tempNum)++;
}

void bneg()
{
	cout << "\t pop rax \n\t xor rax, 1 \n\t  push rax \n\t";
}

/*
input: two floats, longs, or boolean types
output: a void of 3 that is 1 if left > right, and 0 otherwise

types of left and right must match
*/
void greater_than(int type, long* tempNum)
{
/*
	switch(type)
	{
		case 0:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jb GT" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		case 1:
			cout <<	"jmp LT_temp" << *tempNum << "\n\t SECTION .data\n\t"
			<<  "lvar" << *tempNum << ": dq 0.0\n\t "
			<< "rvar" << *tempNum << ": dq 0.0\n\t SECTION .text \n"
			<< "LT_temp" << *tempNum << ": \n\t pop QWORD [lvar" 
			<< *tempNum << "]\n\t pop QWORD [rvar"
			<< *tempNum << "]\n\t fld QWORD [lvar" << *tempNum
			<< "] \n\t fcomp QWORD [rvar"<< *tempNum << "] \n\t"
			<< "fstsw ax\n\t sahf \n\t jae not_greater" << *tempNum
			<< "\n\t push QWORD 1 \n\t jmp continue" << *tempNum
			<< "\n\t not_greater" << *tempNum << ": \n\t push 	QWORD 0"
			<< "\n\t continue" << *tempNum << ": \n\t fstp QWORD [lvar"
			<< *tempNum << "] \n\t fstp QWORD [lvar" << *tempNum << "]\n";
			break;
		case 3:
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jb GT" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		default:
			break;
	}

	(*tempNum)++; */

	switch(type)
	{
		case 0:
			//if(left.lval > right.lval) newRecord.bval = 1;
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jb GT" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		case 1:
			//if(left.fval > right.fval) newRecord.bval = 1;
			cout <<	"jmp LT_temp" << *tempNum << "\n\t SECTION .data\n\t"
			<<  "lvar" << *tempNum << ": dq 0.0\n\t "
			<< "rvar" << *tempNum << ": dq 0.0\n\t SECTION .text \n"
			<< "LT_temp" << *tempNum << ": \n\t pop QWORD [lvar" 
			<< *tempNum << "]\n\t pop QWORD [rvar"
			<< *tempNum << "]\n\t fld QWORD [lvar" << *tempNum
			<< "] \n\t fcomp QWORD [rvar"<< *tempNum << "] \n\t"
			<< "fstsw ax\n\t sahf \n\t jae not_greater" << *tempNum
			<< "\n\t push QWORD 1 \n\t jmp continue" << *tempNum
			<< "\n\t not_greater" << *tempNum << ": \n\t push 	QWORD 0"
			<< "\n\t continue" << *tempNum << ": \n\t fstp QWORD [lvar"
			<< *tempNum << "] \n\t fstp QWORD [lvar" << *tempNum << "]\n";
			break;
		case 3:
			//if(left.bval > right.bval) newRecord.bval = 1;
			cout << "\t pop rax\n\t pop rbx\n\t cmp rax, rbx\n\t jb GT" 
			<< *tempNum << "\n\t push QWORD 0\n\t jmp continue" << *tempNum
			<< "\n\t GT" << *tempNum << ": \n\t push QWORD 1\n\t continue"
			<< *tempNum << ":\n";
			break;
		default:
			break;
	}

	(*tempNum)++;

	
}



//end logic --------------------------------------------------------------


#endif
