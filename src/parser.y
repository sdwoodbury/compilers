/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/


%code requires{
	#define long_type 0
	#define float_type 1
	#define string_type 2 
	#define bool_type 3
	#define function_type 4
	#define void_type 5 /* <> */

}

%{

#define long_type 0
#define float_type 1
#define str_type 2
#define bool_type 3
#define function_type 4
#define void_type 5


#include <iostream> //for cout
#include <math.h> //for pow and fmod
#include <stdlib.h> //for exit
#include <stdio.h>
#include <string>

#include <unordered_map> //for the symbol table
#include <stack>
#include <vector>

#include "printStuff.h"
#include "math.h"
#include "logic.h"
#include "push.h"
#include "misc.h"
#include "err_check.h"


using namespace std;


//prototypes of required functions ---------------------------------

/* Parser error reporting routine */
void yyerror(const char *msg);

/* Scannar routine defined by Flex */
int yylex();

//end prototypes ----------------------------------------------------------

//GLOBAL TOOLS -----------------------------------------------

static stack<string> scope_stack; ///used to check scope for nested functions. 

//put in scope_ID, returns type if in scope
unordered_map<string, long> sym_table; 

unordered_map<string, long>::const_iterator table_iterator;   //used for finding

unordered_map<string, vector<string> > fun_table; //matches function name to parameter list,

unordered_map<string, vector<string> >::const_iterator fun_iterator; //used for finding

static vector<string> cur_fun; //holds the current parameter list

static stack< vector<string> > funs; //push cur_fun

static long cur_lst; //used for holding the current index of the current parameter list

static stack<long> lists; //push cur_lst

static string scope; //used for arbitrary name generation

static long* tempNum = (long*)malloc(sizeof(long)); //used for arbitrary label generation

static long line_count; //used for error reporting
  
static string t_var_label; //the name of the function to which the current scope applies

static bool fun_return; //if a function returned or not

//static bool error_flag; //if there was 

static stack<long> while_stack; //for break and continue

static stack<long> if_stack; //for break

static stack<long> current_control_structure; //-1 for none, 0 for if, 1 for while

//FUNCTION PROTOTYPES------------------------


//returns true if the id specified is an entry in the  current symbol table
bool in_table(string temp);

//takes a name and the scope and returns scope_name
string key(string scp, string temp);

//makes a name, type entry into sym_table
void add_key(string temp, long type);

//checks if variable has been declared and pushes it. takes scope into consideration
long check_and_push(string temp);

//checks if variable has not been declared and if not, makes an entry in the symbol table
void check_and_enter(string temp, long type);

//does what check and enter does and checks type, then pops the top of the stack into the newly created variable
void check_create_assign(string temp, long type1, long type2);

//checks if declared, checks types, then assigns
void check_and_assign(string temp, long type);

//used for input
void read_in(string temp);

//adds function into symbol table if it hasn't been decalred and adds to scope stack and changes the scope
void fn_dcl(string name, long type);

//adds a variable to the list of function variables
void add_fn_var(string name, long type);

//pops the scope stack and sets scope appropriately
void end_fn();

void lst_start(string lbl); //used to jump over .data section for declaring function local variables

void lst_end(string lbl); //used in label generation for jumping over the .data section used for decalring local variables

string fun_var_name(string name); //checks if the function has been declared and if so returns the name back

//for the end of a function body
void pop_list();

//for the start of a functino body
void push_list();

//validates return type
void check_return_type(long type);

//pushes return value of a function
void push_return_value(long type);

//checks the type of a variable in the parameter list
void check_function_parameter_type(long type);



%}


/* yylval union type */
%union {

	long Long;
	long Type;
	char* Char;	
}

//terminals


%token <Long> TYPE IF WHILE LINE BREAK CONTINUE
%token <Char> ID STRING FLOAT LONG
%token <NULL> PRINT PRINTLN INPUT RET TRUE FALSE 



/* Operators */
%right '='
%left '<' '>' //less than, greater than
%right EQU NE //equal to, not equal to
%right AND OR //conjunction, disjunction
%right LE GE //less than or equal to, greater than or equal to
%right '!'  //logical not
%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%right POW
%right '~'
%right '"'

/* Nonterminal types */
%type <Null> print declaration assignment input   
%type <Long> conditional expr_list expr_list_prime id_list id_list_prime fnctn_decl fnctn
%type <Long> stmt_list stmt expr 

%destructor {} <> //useless piece of junk

%glr-parser //boo-yah !

%%

prog: 
/*empty string*/
| nil prog {  }
| stmt prog   {  }
;

nil:
LINE {line_count += $1;}
;

stmt_list_prime:
stmt stmt_list_prime {}
| LINE stmt_list_prime {line_count += $1;}
| '}' { if(fun_return == false && sym_table[t_var_label] != 5 && if_stack.top() == -1 && while_stack.top() == -1) {
		no_return_err(t_var_label,line_count, sym_table[t_var_label]);
		}
		fun_return = false;}
;

stmt_list:
'{' stmt stmt_list_prime {cout << endl;}
;


expr_list:
'(' expr ')'  {
	check_function_parameter_type($2);
	cout << "pop QWORD [" << cur_fun[cur_lst] << "]\n"; 
	cur_lst++; /*param_err(cur_fun.size(), cur_lst, line_count);*/
	}
| '('expr ',' {
	check_function_parameter_type($2);
	cout << "pop QWORD [" << cur_fun[cur_lst] << "]\n";
	 cur_lst++;
	} 
expr_list_prime
;


expr_list_prime:
expr ',' {
	check_function_parameter_type($1);
	cout << "pop QWORD [" << cur_fun[cur_lst] << "]\n"; 
	cur_lst++;
	} 
expr_list_prime 
| expr ')' {
	check_function_parameter_type($1);
	cout << "pop QWORD [" << cur_fun[cur_lst] << "]\n"; 
	cur_lst++;
	}
;

id_list:
'('  TYPE ID {add_fn_var($3, $2);} id_list_prime 
;

id_list_prime:
',' TYPE ID {add_fn_var($3, $2); } id_list_prime 
| ')' { lst_end(t_var_label); fun_table[t_var_label] = cur_fun;}
;

fnctn_decl: 
TYPE ID {cur_fun.clear(); t_var_label = $2; fn_dcl($2, $1); lst_start($2);} id_list stmt_list {end_fn(); cout << "pop rbp\n ret\nfun_" << $2 << "_end:\n";}  
| TYPE ID  '(' ')' {cur_fun.clear(); fun_table[$2] = cur_fun; fn_dcl($2, $1); cout << "jmp fun_" << $2 << "_end\n fun_" << $2 << ":\n push rbp\n mov rbp, rsp\n";} stmt_list {end_fn(); cout << "pop rbp\n ret\nfun_" << $2 << "_end:\n";}  
;

fnctn: 
ID { /*push cur_lst and push cur_fun onto lists and funs*/
	lists.push(cur_lst); cout << ";list size before push: " << cur_lst << endl;
	funs.push(cur_fun);
	cur_lst = 0; 
	cur_fun = fun_table[fun_var_name($1)];
	cout << ";print list\n"; 
	push_list(); } 
expr_list { 
	param_err(cur_fun.size(), cur_lst, line_count); 
	cout << "call fun_" << $1 << endl; 
	cout << ";pop list\n"; 
	pop_list(); 
	push_return_value(sym_table[$1]); 
	$$ = sym_table[$1]; cout << ";list size before pop: " << cur_lst << endl;
	/*pop cur_lst and pop cur_fun from lists and funs*/
	cur_lst = lists.top();
	lists.pop();
	cur_fun = funs.top(); cout << ";list size after pop: " << cur_lst << endl;
	funs.pop();}
| ID '(' ')' {
	/*push*/
	lists.push(cur_lst); cout << ";list size before push: " << cur_lst << endl;
	funs.push(cur_fun);
	cur_fun = fun_table[fun_var_name($1)];
	cur_lst = 0; 
	param_err(cur_fun.size(), 0, line_count); 
	cout << "call fun_" << $1 << endl; 
	push_return_value(sym_table[$1]); $$ = sym_table[$1];
	/*pop*/
	cur_lst = lists.top();
	lists.pop();
	cur_fun = funs.top(); cout << ";list size after pop: " << cur_lst << endl;
	funs.pop();}
;

stmt:
 declaration ';'
| assignment ';'
| print ';' 
| input ';'
| conditional
| fnctn_decl
| fnctn ';' {
	if($1 != void_type){/*yyerror("fuckoff");*/ cout << "treated a function like a procedure, line: " << line_count << "\n"; exit(1);}}/*what to do if it has a non void return type?*/
| RET ';' {check_return_type(void_type); cout << "pop rbp\nret\n";}
| RET expr ';' {check_return_type($2); cout << "pop rax\n pop rbp\n ret\n"; fun_return = true;}
| BREAK ';' {break_continue_err($1, if_stack.top(), while_stack.top(), line_count);
	cout << "jmp exit_while" << while_stack.top() << endl; } 
| CONTINUE ';' {break_continue_err($1, if_stack.top(), while_stack.top(), line_count); 
	cout << "jmp while" << while_stack.top() << endl;} 
;


//no more than 1 operator per expression for a conditional
//need functions to make arbitrary lables and to make jump/comparisons
conditional:
IF '(' expr ')' { cout << "\t pop rax \n\t cmp rax, 1\n\t jb if" << $1 << endl;
	 if_stack.push($1);
	 current_control_structure.push(0);} 
stmt_list {cout << "if" << $1 << ":\n";
	if_stack.pop(); current_control_structure.pop();}
| WHILE { cout << "\t while" << $1 << ":\n";} 
'(' expr ')' { 
	cout << "\t pop rax \n\t and rax, 1\n\t ja continue_while" << $1 << "\n\t jmp exit_while" << $1 
	<< "\n\t continue_while" << $1 << ": \n"; 
	while_stack.push($1);
	current_control_structure.push(1);}  
stmt_list {cout << "\t jmp while" << $1 << "\n\t exit_while" << $1 << ":\n"; 
	while_stack.pop();
	current_control_structure.pop();}
;
declaration:
TYPE ID {check_and_enter($2, $1);}
| TYPE ID '=' expr {check_create_assign($2, $1, $4); }
;

assignment:
ID '=' expr {check_and_assign($1, $3);/* cout << "pop QWORD [" << scope << "_" << ID << "]\n";*/}
;

print:
PRINT expr {print($2, 0, scope);}
| PRINTLN expr {print($2, 1, scope);}
;

input:
INPUT ID {read_in($2);}
;


expr:
 fnctn {$$ = $1; if($1 == void_type){/*yyerror("fuckoff");*/ cout << "treated a procedure like a function, line: " << line_count << "\n"; exit(1);}}
| ID {$$ = check_and_push($1);} 
| TRUE {push_int("1"); $$ = bool_type;}
| FALSE {push_int("0"); $$ = bool_type;}
| LONG {push_int($1); $$ = long_type;}
| FLOAT {push_float($1, tempNum); $$ = float_type;}
| STRING { push_string($1, tempNum); $$ = str_type;}
| expr EQU expr {type_err($1, $3, line_count); equ(tempNum); $$ = bool_type;}
| expr NE expr {type_err($1, $3, line_count); nequ($1, tempNum); $$ = bool_type;}
| expr AND expr {type_err($1, $3, line_count); conjunction(tempNum); $$ = bool_type;}
| expr OR expr  {type_err($1, $3, line_count); disjunction(tempNum); $$ = bool_type;}
| expr '<' expr {type_err($1, $3, line_count); less_than($1, tempNum); $$ = bool_type;}
| expr LE expr {type_err($1, $3, line_count); lequ($1, tempNum); $$ = bool_type;}
| expr '>' expr {type_err($1, $3, line_count); greater_than($1, tempNum); $$ = bool_type;}
| expr GE expr{type_err($1, $3, line_count); gequ($1, tempNum); $$ = bool_type;}
| '!' expr { bneg(); $$ = bool_type;}
| expr '+' expr {$$ = type_err($1, $3, line_count); add($$);}
| expr '-' expr {$$ = type_err($1, $3, line_count); subtract($$);}
| expr '*' expr {$$ = type_err($1, $3, line_count); multiply($$);}
| expr '/' expr {$$ = type_err($1, $3, line_count); divide($$);}
| expr '%' expr {$$ = type_err($1, $3, line_count); mod($$);}
| '~' expr {neg($2); $$ = $2;}
| expr POW expr {$$ = type_err($1, $3, line_count); exponentiate($$, tempNum); }
| '(' expr ')' {$$ = $2;}
;
 

%%

void yyerror(const char *msg)
{
    cerr << "Parser error:\n" << msg << endl;
    exit(1);
}


int main (int argc, char** argv)
{
	scope = "global";
	scope_stack.push(scope);
	*tempNum = 0;
	line_count = 1;
	cur_lst = -1;
	fun_return = false;
	while_stack.push(-1);
	if_stack.push(-1);
	current_control_structure.push(-1);

	print_boiler();	
   int temp = yyparse();  
	print_end();
	
	free(tempNum);

	//if(error_flag){exit(1);}

	return temp; 
}

//returns true if the id specified is an entry in the  current symbol table
bool in_table(string temp)
{
	table_iterator = sym_table.find(temp);
	if(table_iterator != sym_table.end()) return true;
	else return false;
}

//scope_ID
string key(string scp, string temp)
{
	string name = scp + "_" + temp;
	return name;
}

//insert variable to symbol table
void add_key(string temp, long type)
{
	sym_table.insert(make_pair(temp, type));
}

//push variable
long check_and_push(string temp)
{
	string name1 = key(scope, temp);
	string name2 =  key("global", temp);
	if(in_table(name1)) 
	{
		push_var(name1);
		return sym_table[name1];
	}
	else if(in_table(name2)) 
	{
		push_var(name2);
		return sym_table[name2];
	}
	else
	{
		not_decl_err(temp, line_count);
		return -1;
	}	
}

//adds variable to .asm file
void check_and_enter(string temp, long type)
{
	string name = key(scope, temp);
	if(in_table(name))
	{
		re_decl_err(temp, line_count);
	}

	sym_table[name] = type;

	add_variable(name, tempNum, type);
}

//adds and initalizes variable to .asm file
void check_create_assign(string temp, long type1, long type2)
{
	string name = key(scope, temp);
	if(in_table(name))
	{
		re_decl_err(temp, line_count);
	}

	sym_table[name] = type1;

	add_variable(name, tempNum, type1);

	type_err(type1, type2, line_count);
	cout << "\t pop QWORD [" << name << "]\n"; 
}

//used for assignment to a variable
void check_and_assign (string temp, long type)
{
	string name = key(scope, temp);
	if(!in_table(name))
	{
		name = key("global", temp);
		if(!in_table(name))
		{  
			not_decl_err(temp, line_count);
		}
	}

	type_err(sym_table[name], type, line_count);
	cout << "\t pop QWORD [" << name << "]\n"; 
}

//used for user input
void read_in(string temp)
{
	string name = key(scope, temp);
	if(!in_table(name))
	{
		name = key("global", temp);
		if(!in_table(name))
		{  
			not_decl_err(temp, line_count);
		}
	}

	read(name, sym_table[name], line_count);
}

//used for declaring a function. changes scope and adds function to list
void fn_dcl(string temp, long type)
{
	if(in_table(temp))
	{
		cout << "ERROR: function name, " << temp << ", re-declared. line: " << line_count << endl; 
	exit(1);
	}

	sym_table[temp] = type;
	scope = temp;
	scope_stack.push(scope);
}

//declares function's local variable in .data and makes note of it in cur_fun vector, which will later be put into a hash table
void add_fn_var(string name, long type)
{
	string nm; nm = key(scope, name);
	sym_table[nm] = type;
	cout << nm << ": dq 0\n";

	cur_fun.push_back(nm);
}

//print out lable for declaring function's local variables
void lst_start(string lbl)
{
	cout << "jmp fun_" << lbl << "_end\n SECTION .data\n";
}

//prints out end label for decalring function's local variables
void lst_end(string lbl)
{
	cout << "SECTION .text\n fun_" << lbl << ":\n push rbp\n mov rbp, rsp\n";
}

//returns scope to previous state after exiting a function
void end_fn()
{
	scope_stack.pop();
	scope = scope_stack.top();
}

//checks if a function has been declared
string fun_var_name(string name)
{	
	fun_iterator = fun_table.find(name);
	if(fun_iterator != fun_table.end()) return name;
	else not_decl_err(name, line_count);

	return name;
}	

/*returns the local variables to their state previous to the execution of the function body*/
void pop_list()
{
	for(int i = cur_fun.size(); i > 0; i --)
	{
		cout << "pop QWORD [" << cur_fun[i-1] << "]\n";
	}
}

/*pushes a parameter list onto the stack before a function's body is executed*/
void push_list()
{	
	for(int i = 0; i < cur_fun.size(); i ++)
	{
		cout << "push QWORD [" << cur_fun[i] << "]\n";
	}
}

/*verifies the return value of a function*/
void check_return_type(long type)
{
	if(sym_table[scope] != type)
	{
		return_type_err(line_count);
	}

}

/*verifies that a function is not void type ( a procedure) and if it isn't, it pushes the returnes value*/
void push_return_value(long type)
{
	if(type != void_type) cout << "push rax\n";
}

//uses sym_table[cur_fun[cur_lst]] and the type to determine if the parameter is of the correct type. if not, call an error
void check_function_parameter_type(long type)
{
	string name = cur_fun[cur_lst];

	//function_parameter_type_mismatch(string fun, string var_name, long func_type, long param_type, long line_count)

	if(sym_table[name] != type) {

		if(sym_table[name] == long_type && type == bool_type) {}//no problem
		else if(sym_table[name] == float_type && (type == long_type || type == bool_type) ){ //conversion
			cout << "pop rax\n\t mov rdi, rax\n\t call toFloat\n\t push rax\n\t";}
		else{ //you are in trouble
		function_parameter_type_mismatch(t_var_label, name, type, sym_table[name], line_count);}
	}
}

