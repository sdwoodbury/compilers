/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/
#ifndef MISC_H
#define MISC_H

/*takes a float and treats it as an int and converts it to a float. why? because of some 
troublesome error where x.0 reads as zero. so i'm gonna try this way*/
void convert_to_float(string temp)
{

	cout << "	mov QWORD [rbp - 8], " << temp << endl;
	cout << "	movsd xmm0,  [rbp - 8]" << endl;
	cout << "	call subtract" << endl;
	cout << "	movsd [rbp-8], xmm0" << endl;
	cout << "	mov rax, QWORD [rbp-8]" << endl;
	cout << "	push rax" << endl;			

}


/*reads in a float or a long value into a variable. value is entered by user*/
void read(string temp, long type, long line_count)
{
	
	switch(type)
	{
		case 0:
			cout << "	mov rsi, " << temp << endl;
			cout << "	mov rdi, scan_decimal\n";
			cout << "	push rsi\n	push rdi\n";
			cout << "	mov rax, 0\n";
			cout << "	call scanf;\n";
			cout << "	add rsp, 16\n";
			break;
		case 1:
			cout << "	mov rsi, " << temp << endl;
			cout << "	mov rdi, scan_float\n";
			cout << "	push rsi\n	push rdi\n";
			cout << "	mov rax, 0\n";
			cout << "	call scanf;\n";
			cout << "	add rsp, 16\n";
			break;
		case 2:
			cout << "	you can't read in a string. error. line: " << line_count << endl;
			exit(1);
			break;
		default:
			break;
	}

}
#endif
