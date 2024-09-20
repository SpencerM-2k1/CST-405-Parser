%option noyywrap
%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0; //Char starts at 0, as char count will incremenet before displaying syntax error
int lines = 1; //Text editors start from Line 1, reflect this in error
%}

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

%%
{int}               { words++; chars += strlen(yytext);
                      printf("TYPE: %s\n", yytext);
			                yylval.string = strdup(yytext); 
                      return TYPE;
                    }
{char}              { words++; chars += strlen(yytext);
                      printf("TYPE: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return TYPE;
                    }
{write}             { words++; chars += strlen(yytext);
                      printf("KEYWORD: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return WRITE;
                    }
{ID}                { words++; chars += strlen(yytext);
                      printf("IDENTIFIER: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return ID;
                    }
{NUMBER}            { words++; chars += strlen(yytext);
                      printf("NUMBER: %s\n", yytext);
			                yylval.string = atoi(strdup(yytext));
                      return NUMBER;
                    }  // Floating point numbers
{SEMICOLON}         { chars += strlen(yytext);
                      printf("SEMICOLON: %s\n", yytext); 
			                yylval.string = strdup(yytext);
                      return SEMICOLON;
                    }
{ASSIGN}            { chars += strlen(yytext);
                      printf("ASSIGN: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return ASSIGN;
                    }
{PLUS}              { chars += strlen(yytext);
                      printf("PLUS: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return PLUS;
                    }
{MINUS}             { chars += strlen(yytext);
                      printf("MINUS: %s\n", yytext);
			                yylval.string = strdup(yytext);
                      return MINUS;
                    }
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*/"  { /* Ignore multi-line comments */ }
[\n]                {lines++; chars=0;} //Newline takes priority over whitespace
{ws}                {chars++;}
.                   {chars += strlen(yytext);
                       printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars); }
%%

// int main(int argc, char **argv) {
//     ++argv, --argc;  /* Skip over program name */
//     if (argc > 0)
//         yyin = fopen(argv[0], "r");
//     else
//         yyin = stdin;

//     yylex();

//     if (errorFound)
//         printf("Errors detected! Program will fail to compile.\n");
//     else
//         printf("No errors detected.\n");
//     return 0;
// }

