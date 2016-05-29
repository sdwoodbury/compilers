/*
STUART WOODBURY
yr45570@umbc.edu
comiplers

i am sick and tired of updating comments for ten files every time i upgrade my project. so see the readme
*/

%{

using namespace std;
#include "parser.tab.h" 

long TW = 0; //while loop counter for arbitrary label generation
long TI = 0; //if statement counter for arbitrary label generation


%}

%%

\>\:\(.* {
	//commeent
}

[0-9]*\.[0-9]+ {
	/*Float*/
	yylval.Char = strdup(yytext);
	return FLOAT;
}

[0-9]+ {
    /* Integers */
   yylval.Char = strdup(yytext);
	return LONG;
}

"**" {
    /* Exponentiation operator */
    return POW;
}

"==" {
	return EQU;
}

"&&" {
	return AND;
}

"||" {
	return OR;
}

"<=" {
	return LE;
}

">=" {
	return GE;
}

"!=" {
	return NE;
}

"true" {
	return TRUE;
}

"false" {
	return FALSE;
}

"if" {
	yylval.Long = TI++;
	return IF;
}

"while" {
	yylval.Long = TW++;
	return WHILE;
}

"bool" {
	//declare a boolean
	yylval.Type = bool_type;
	return TYPE;
}

"string" {
	//declare a string
	yylval.Type = string_type;
	return TYPE;
}

"float" {
	//declar a float
	yylval.Type = float_type;
	return TYPE;
}

"long" {
	//declare an integer
	yylval.Type = long_type;
	return TYPE;
	
}

"<>" {
	yylval.Long = void_type;
	return TYPE;
}

"return" {
	return RET;
}

"println" {
	return PRINTLN;
}

"print" {
	return PRINT;
}

"input" {
	return INPUT;
}

"break" {
	yylval.Long = -1;
	return BREAK;
}

"continue" {
	yylval.Long = -2;
	return CONTINUE;
}


[a-zA-Z]+ {
	/* variable*/
	yylval.Char = strdup(yytext);
	return ID;
	
}

'.*' {
	//quoted st\"[^"\n]*["\n]ring

	int temp = strlen(yytext);
	
	char* quotes = strdup(yytext);
	char* noquotes = (char*) malloc(sizeof(char*) * (temp) - 1);

	for(int i = 0; i < temp - 2; i++)
	{
		noquotes[i] = quotes[i + 1];
	}

	noquotes[temp - 2] = '\0';

	yylval.Char = strdup(noquotes);
	free(quotes);
	free(noquotes);
	return STRING;
}

\n {
	yylval.Long = 1;
	return LINE;
}

[ \t]+ {
    /* Eat whitespace */
}

. {
    /* Return any unmatched character as is */
    return (int)(*yytext);
}


%%
