all: parser

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h AST1.c
	gcc -o parser parser.tab.c lex.yy.c AST1.c SymbolTable1.c
	./parser testProg.cmm

# table:
# 	gcc -o tableTest SymbolTable1.c SymbolTable1.h
# 	./tableTest

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h  lex.yy.o parser.tab.o AST1.o
	ls -l
