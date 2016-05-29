#Stuart Woodbury
#yr45570@umbc.edu
#february 2015
#cmsc431
#PROJ7
#src makefile


all:
	bison -d -v --report=state,solved  parser.y
	flex scanner.l
	g++ lex.yy.c parser.tab.c -lm -lfl -std=c++0x -o PROJ7

	#cat "test.txt" | ./PROJ7 > data.asm
	#nasm -f elf64 -g data.asm
	#gcc -o Executable.out data.o -lm

	#./Executable.out

	mv PROJ7 ..

assembly:
	cat "test.txt" | ./PROJ7 > data.asm
	nasm -f elf64 -g data.asm
	gcc -o Executable.out data.o -lm
	mv PROJ7 ..
	mv "test.txt" ..
	
run:
	./Executable.out

clean:
	rm -rf lex.yy.c parser.tab.c parser.tab.h *.out *.o *~ data.asm text.asm

