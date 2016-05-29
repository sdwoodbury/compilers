
FOR THIS PROJECT, I CLAIM THE FOLLOWING: 
	BETTER ERROR REPORTING: 20 POINTS
	STRING TYPE: 10 POINTS
	COMMENTS: 1 POINTS
	BREAK AND CONTINUE STATEMENTS: 20 POINTS
	TYPE PROMOTOIN: 50 POINTS
	BEST CASE TOTAL: 101 POINTS

1)this compiler needs the following file setup:

	parser.y, scanner.l, boiler.txt, errcheck.h, logic.h, math.h, misc.h, printstuff.h, and push.h all need 
	to be in the same file

2)the compiler prints to cout, and the makefile redirects the output to the file, data.asm
	this compiler generates output errors. the output errors are also written to data.asm
	errors provide line number, the line number refers to the line number of the input file, not 
	the line number of data.asm

3) functions provided by the files: 
	-math.h: add, subtract, multiply, divide, neg, and mod. does this for doubles and longs
	-push.h: add_variable, push_int, push_var, push_string, push_float -->all are self explanatory except for 
		add_variable. that function adds the variable name to the .data section but does this a nasty hacky 
		way. 
	-misc.h: read, convert_to_float --> read uses scanf to take user input. types of user input are not 	
		validated and you can read longs into float types and it works at first glance.
	-err_check.h: functions for type checking, checking if an undeclared variable has been used, if a
		variable has been redeclared, or if the size of a parameter list is incorrect.
	-logic.h: == != <= >= < > ! boolean functions. == != and ! are for boolean types and return boolean
		types. <= >= < > are for long to long or float to float comparisons and the result is a boolean
	-printStuff.h: prints out boiler.txt, this is to be done before the parsing starts. also has print 
		functinos for longs and floats, with and without new line

ADDITTIONAL NOTES
DONT PUT MULTIPLE PRINTSTATEMENTS WITH QUOTES ON THE SAME LINE
-also, don't put double quoted inside of strings. nasm will bitch about commas. 
