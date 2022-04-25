%{
#include <stdlib.h>
#include "bison.tab.h"
%}

white		[ \t\n]+
comment		"%".*\n
num     	[1-9][0-9]*|0
boollit 	false|true
ident   	[A-Z][A-Z0-9]*

%%

"if"		{return IF; }
"then" 		{return THEN;}
"else" 		{return ELSE; }
"begin" 	{return BEGINS; }
"end" 		{return END; }
"while" 	{return WHILE; }
"do" 		{return DO; }
"program"	{return PROGRAM; }
"var" 		{return VAR; }
"as" 		{return AS; }
"int" 		{return INT; }
"bool" 		{return BOOL; }

"writeInt" 	{return WRITEINT; }
"readInt" 	{return READINT; }

{white} 	{/* Ignore whitespace */}
{comment}	{/*Ignore comment */}
{num}		{ yylval.number = atoi(strdup(yytext)); return num; }
{ident}		{ yylval.var = strdup(yytext); return ident; }
{boollit}	{ yylval.var = strdup(yytext); return boollit; }

"*"|"div"|"mod"			{ yylval.var = strdup(yytext); return OP2; }
"+"|"-"      {yylval.var = strdup(yytext); return OP3; }
"="|"!="|"<"|">"|"<="|">="		{yylval.var = strdup(yytext); return OP4; }
"("      { return LP; }		
")"      { return RP; }	
":="      { return ASGN; }
";"      { return SC; }					

.		   { printf("Unrecognized character"); }

%%

int yywrap()
{
	return 1;
}


