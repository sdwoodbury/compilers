/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/

#ifndef ERR_CHECK_H
#define ERR_CHECK_H

/*used for return type error*/
void return_type_err(long line_count)
{
	cout << "ERROR: return type mismatch at line: " << line_count << endl;
	exit(1);
}

//used for type mismatch and type promotion
long type_err(long left, long right, long line_count)
{
	if(left != right)
	{
		if( (left == long_type && right == bool_type) || (left == bool_type && right == long_type) ) {
			return long_type;}//all good
		else if(left == float_type && (right == long_type || right == bool_type) ){cout << "pop rax\n\t"
			<< "mov rdi, rax\n\t call toFloat\n\t push rax\n\t"; return float_type;} //fuck with this
		else if( (left == long_type || left == bool_type) && right == float_type){cout << "pop rbx\n\t pop rax\n\t"
			<< "mov rdi, rax\n\t call toFloat\n\t push rbx\n\t push rax\n\t"; return float_type;} //fuck with this
		else{ //now you really done it
			cout << "ERROR: type mismatch at line: " << line_count << endl; 
			exit(1);}
	}

	return left;
}

//used for type being used before declaration
void not_decl_err(string temp, long line_count)
{
	cout << "ERROR: variable, " << temp << ", not declared. line: " << line_count << endl; 
	exit(1);
}


//used for re-declaring a variable within the same scope
void re_decl_err(string temp, long line_count)
{
	cout << "ERROR: variable, " << temp << ", re-declared. line: " << line_count << endl; 
	exit(1);
}

///used if parameter list is not of correct length
void param_err(int fun, long expr, long line_count)
{

	if(fun != expr)
	{
		cout << ";you frucked up the number of parameters, you mother frucker! line: " << line_count << ", number of parameters: " << expr << ", should be: " << fun << endl;
	exit(1);
	}
}

//gives detailed description of what's going wrong with function parameters if their types are wrong
void function_parameter_type_mismatch(string fun, string var_name, long func_type, long param_type, long line_count)
{
	cout << "function parameter type mismatch. line: " << line_count << ", function name: " << fun << ", variable name (from function declaration): " << var_name << ", variable type: " << param_type << ", and the type of the mismatched variable is: " << func_type << endl;
	exit(1);
}

//thrown if a non void function does not return a value. 
void no_return_err(string fun, long line_count, long func_type)
{
	cout << "didn't return from a non-void function. name of function: " << fun << ", return type: " << func_type << ", function ends on line: " << line_count << endl;
	exit(1);	
}

void break_continue_err(long flag, long if_stack, long while_stack,  long line_count) //flag is -1 for break, -2 for continue
{

	if(if_stack == -1 && while_stack == -1){ //you fucked up
		if(flag == -1) {cout << "break ";}
		else if(flag == -2) {cout << "continue ";}
		cout << "staement outside of a while loop or if statement. line: " << line_count << endl;
		exit(1);
	}

	if(while_stack == -1){ //now we must be inside of an if statement
		if(flag == -1) {cout << "break ";}
		else if(flag == -2) {cout << "continue ";}
		cout << "staement outside of a while loop. line: " << line_count << endl;
		exit(1);
	}

}

#endif
