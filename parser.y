%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST1.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

extern int yyparse();

void yyerror(const char* s);

ASTNode* root = NULL; 
%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}

/*
Program		{VarDecl}{Block}
VarDeclList {VarDecl}+
VarDecl		({Type}{ID}{SEMICOLON})
Type		{int}|{char}
Block		{StmtList}
StmtList	{Stmt}+
Stmt		{ID}{ASSIGN}{Expr}{SEMICOLON} | {write}{ID}
Expr		{ID}{Op}{ID}
Op			{PLUS}|{MINUS}|{ASSIGN}

PLUS        [+]
MINUS       [-]
ASSIGN      [=]
int         int
char        char
write       write

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
SEMICOLON   [;]
ws          {delim}+
*/

%token <string> TYPE
%token <string> ID
%token <character> SEMICOLON
%token <operator> ASSIGN
%token <character> PLUS
%token <character> MINUS
%token <number> NUMBER
%token <string> WRITE

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList Stmt StmtList Expr BinOp
%start Program

%%

Program: VarDeclList StmtList   { printf("The PARSER has started\n"); 
									root = malloc(sizeof(ASTNode));
									root->type = NodeType_Program;
									root->program.varDeclList = $1;
									root->program.stmtList = $2;
									// Set other fields as necessary
								}

;

VarDeclList:  {/*empty, i.e. it is possible not to declare a variable*/}
	| VarDecl VarDeclList 	{  	printf("PARSER: Recognized variable declaration list\n"); 
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_VarDeclList;
								$$->varDeclList.varDecl = $1;
								$$->varDeclList.varDeclList = $2;
								printASTNode($$);
								// Set other fields as necessary
							
							}
;

VarDecl: TYPE ID SEMICOLON { printf("PARSER: Recognized variable declaration: %s\n", $2);
							    $$ = malloc(sizeof(ASTNode));
    							$$->type = NodeType_VarDecl;
    							$$->varDecl.varType = strdup($1);
    							$$->varDecl.varName = strdup($2);
    							// Set other fields as necessary
							 }
		| TYPE ID {
                  printf ("Missing semicolon after declaring variable: %s\n", $2);
             }

StmtList:  {/*empty, i.e. it is possible not to have any statement*/}
	| Stmt StmtList { printf("PARSER: Recognized statement list\n");
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_StmtList;
						$$->stmtList.stmt = $1;
						$$->stmtList.stmtList = $2;
						// Set other fields as necessary
					}
;

Stmt: ID ASSIGN Expr SEMICOLON { /* code TBD */
								printf("PARSER: Recognized assignment statement\n");
								$$ = malloc(sizeof(ASTNode));
								$$->type = NodeType_Stmt;
								$$->stmt.varName = strdup($1);
								$$->stmt.operator = $2;
								$$->stmt.expr = $3;
								// Set other fields as necessary
 }
	| WRITE ID SEMICOLON { printf("PARSER: Recognized write statement\n"); }
;

Expr: ID BinOp ID { 
						printf("PARSER: Recognized binary operation\n");
						/**/
						$$ = malloc(sizeof(ASTNode));
						$$->type = NodeType_Expr;
						$$->expr.left = $1;
						$$->expr.right = $3;
						$$->expr.operator = $2;
						// $$->expr.operator = strdup($2);
						// printf("%c\n", $$->expr.operator);
						// printf($2);
						// printf($$->expr.operator);
						// printf('P');
						/**/
						// Set other fields as necessary
 					}
	| ID { printf("ASSIGNMENT statement \n"); }
	| NUMBER { 
				printf("PARSER: Recognized number\n");
				$$ = malloc(sizeof(ASTNode));
				$$->type = NodeType_SimpleExpr;
				$$->simpleExpr.number = $1;
				// Set other fields as necessary
			 }
;

BinOp: PLUS { 
				// printf("PARSER: Recognized addition statement\n");
				// $$ = malloc(sizeof(ASTNode));
				// $$->type = NodeType_BinOp;
				// $$->binOp.operator = $1;
    			// Set other fields as necessary
				printf("PARSER: Recognized PLUS\n");
			}

	|MINUS { 
				// printf("PARSER: Recognized addition statement\n");
				// $$ = malloc(sizeof(ASTNode));
				// $$->type = NodeType_BinOp;
				// $$->stmt.operator = $1;
    			// Set other fields as necessary
				printf("PARSER: Recognized MINUS\n");
			}
;

%%

int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");

    // Start parsing
    if (yyparse() == 0) {
        // Successfully parsed
		/* printf("Parsing successful!\n"); */
        traverseAST(root, 0);
		/* printf("	traverseAST successful!\n"); */
        freeAST(root);
		/* printf("	freeAST successful!\n"); */
    } else {
        fprintf(stderr, "Parsing failed\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
