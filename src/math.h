/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/
#ifndef MATH_H
#define MATH_H

#include <iostream>
using namespace std;

//math functions
//----------------------------------------------------------------------------------------------

//returns a record with type and value equal to the sum of left and right
/*also prints assembly to perform addittion of two longs or doubles. it assumes these values are already pushed on the x86 stack. yes, even floats. the result is pushed back onto the stack after the operands are popped off*/
void add(int type)
{
	switch(type)
	{
		case 0:
			cout << "	pop rax" << endl << "	add [rsp], rax" << endl;
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call add" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;
			break;
		default:
			break;
	}

}//end add

///returns a record with type and value equal to the difference of left and right
/*also prints assembly to perform subtraction of two floats or doubles*/
void subtract(int type)
{
	switch(type)
	{
		case 0:
			cout << "	pop rax" << endl << "sub [rsp], rax" << endl;
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call subtract" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;
			break;
		default:
			break;
	}
	
}//end subtract

///returns a record with type and value equal to the product of left and right
/*also prints assembly code to perform multiplication of two longs or doubles*/
void multiply(int type)
{

	switch(type)
	{
		case 0:
			cout << "	pop rax" << endl << "	imul rax, QWORD [rsp]\n" << "	mov QWORD [rsp], rax\n";
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call multiply" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;
			break;
		default:
			break;
	}
	
}//end multiply

///returns a record with type and value equal to the quotient of left and right
/*also prints assembly code to perform division between two longs or doubles*/
void divide(int type)
{
	switch(type)
	{
		case 0:
			cout << "	pop rcx\n	pop rax\n	cqo\n" << "	idiv QWORD rcx\n" << "	push QWORD rax\n";
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call divide" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;
			break;
		default:
			break;
	}

}//end divide


///returns a record with type and value equal to the quotient remainder of left and right
/*also prints assembly code to perform modular division between two longs or doubles*/
void mod(int type)
{
	switch(type)
	{
		case 0:
			cout << "pop rcx\n	pop rax\n	cqo\n" << "	idiv QWORD rcx\n" << "	push QWORD rdx\n";
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call fmod" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;
			break;
		default:
			break;
	}

}//end mod

///returns a record with type and value equal to left raised to the power of right
/*also prints assembly code to perform exponentiation for longs or doubles*/
void exponentiate(int type, long* tempNum)
{
	switch(type)
	{
		case 0:
			cout <<  "	pop rsi\n	pop rdi\n	call long_pow\n	push QWORD rax\n";
			break;
		case 1:
			cout << "	pop rax\n	pop rdx\n" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl; //exponent
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	cmp rdx, 0\n";
			cout << "	jge XXX" << *tempNum << endl;
			cout << "	xor rdx, rdx\n";
			cout << "	XXX"  << *tempNum << ":" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl; //base
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call pow" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;			

			break;
		default:
			break;
	}

	(*tempNum)++;
}//end exponentiate

///returns a record with type and value equal to the negation of left
/*performs negation for longs using neg and for floating point numbers by subtracting left from 0*/
void neg(int type)
{
	switch(type)
	{
		case 0:
			cout << "	neg QWORD[rsp]\n";
			break;
		case 1:
			cout << "	pop rax\n	mov rdx, 0\n" << endl;
			cout << "	mov QWORD [rbp - 8], rax" << endl;
			cout << "	movsd xmm1,  [rbp - 8]" << endl;
			cout << "	mov QWORD [rbp - 8], rdx" << endl;
			cout << "	movsd xmm0,  [rbp - 8]" << endl;
			cout << "	call subtract" << endl;
			cout << "	movsd [rbp-8], xmm0" << endl;
			cout << "	mov rax, QWORD [rbp-8]" << endl;
			cout << "	push rax" << endl;		
			break;
		default:
			break;
	}

}//end neg

//end math ---------------------------------------------------------------------------------

#endif
