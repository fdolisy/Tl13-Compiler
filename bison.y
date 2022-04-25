%{
#include <stdio.h>
#include "ParseTree.h"

void yyerror(const char *s);
int yylex();
%}

%union
{
    unsigned int number;
    char *var;
	struct NPROGRAM *prog;
	struct NDECLARATIONS *decl;
	struct NTYPE *type;
	struct NSTATEMENT_SEQUENCE *state_seq;
	struct NSTATEMENT *state;
	struct NASSIGNMENT *assignment;
	struct NIF_STATEMENT *if_state;
	struct NELSE_CLAUSE *else_clause;
	struct NWHILE *while_state;
	struct NWRITE_INT *writeInt;
	struct NEXPRESSION *expression;
	struct NSIMPLE *simple;
	struct NTERM *term;
	struct NFACTOR *factor;
}

%token IF THEN ELSE BEGINS END WHILE DO PROGRAM VAR INT BOOL AS
%token WRITEINT READINT
%token LP RP ASGN SC OP2 OP3 OP4
%token num boollit ident

%type <prog> Program
%type <decl> Declarations
%type <type> Type
%type <state_seq> StatementSequence
%type <state> Statement
%type <assignment> Assignment
%type <if_state> IfStatement
%type <else_clause> ElseClause
%type <while_state> WhileStatement
%type <writeInt> WriteInt
%type <expression> Expression
%type <simple> SimpleExpression
%type <term> Term
%type <factor> Factor

%type <var> ident BOOL OP2 OP3 OP4 boollit
%type <number> INT num

%start Program
%%

Program:
       PROGRAM Declarations BEGINS StatementSequence END
	   {  
		NPROGRAM* nprogram = malloc(sizeof(NPROGRAM));
	    nprogram->decl = $2;
	    nprogram->statement_seq = $4; 
		$$ = genprogram($2, $4);
	   };

Declarations:
	/* empty */ 
	{
		NDECLARATIONS *ndeclarations = NULL;
		$$ = ndeclarations;
	}
	| VAR ident AS Type SC Declarations
	{ 
		NDECLARATIONS *ndeclarations = malloc(sizeof(NDECLARATIONS));
		ndeclarations->str = $2;
	    ndeclarations->type = $4;
	    ndeclarations->decl = $6; 
		$$ = ndeclarations;
	};
Type:
    INT
	{
		NTYPE *ntype = malloc(sizeof(NTYPE));
		ntype->num = $1;
		ntype->type = 1;
		$$ = ntype;
	}
	| BOOL
	{
		NTYPE *ntype = malloc(sizeof(NTYPE));
		ntype->truth = $1;
		ntype->type = 2;
		$$ = ntype;
	}
	;

StatementSequence:
		/* empty */ 
		{
			NSTATEMENT_SEQUENCE *nstate_seq = NULL;
			$$ = nstate_seq;
		}
		| Statement SC StatementSequence
		{
			NSTATEMENT_SEQUENCE *nstate_seq = malloc(sizeof(NSTATEMENT_SEQUENCE));
			nstate_seq->state = $1;
			nstate_seq->seq = $3;
			$$ = nstate_seq;
	   };
Statement:
		Assignment
		{
			NSTATEMENT *nstate = malloc(sizeof(NSTATEMENT));
			nstate->type = 1;
			nstate->assign = $1;
			$$ = nstate;
		}
		| IfStatement
		{
			NSTATEMENT *nstate = malloc(sizeof(NSTATEMENT));
			nstate->type = 2;
			nstate->if_state = $1;
			$$ = nstate;
		}
		| WhileStatement
		{
			NSTATEMENT *nstate = malloc(sizeof(NSTATEMENT));
			nstate->type = 3;
			nstate->while_state = $1;
			$$ = nstate;
		}
		| WriteInt
		{
			NSTATEMENT *nstate = malloc(sizeof(NSTATEMENT));
			nstate->type = 4;
			nstate->writeInt = $1;
			$$ = nstate;
		}
		;

Assignment:
	  	ident ASGN Expression
		{
			NASSIGNMENT *nassignment = malloc(sizeof(NASSIGNMENT));
			nassignment->type = 1;
			nassignment->str = $1;
			nassignment->express = $3;
			$$ = nassignment;
		}
		  
	  	| ident ASGN READINT
		{
			NASSIGNMENT *nassignment = malloc(sizeof(NASSIGNMENT));
			nassignment->type = 2;
			nassignment->str = $1;
			$$ = nassignment;
		}
	  	;

IfStatement:
	   	IF Expression THEN StatementSequence ElseClause END
		{
			NIF_STATEMENT *nif_statement = malloc(sizeof(NIF_STATEMENT));
			nif_statement->express = $2;
			nif_statement->state_seq = $4;
			nif_statement->else_clause = $5;
			$$ = nif_statement;
		}
	   	;

ElseClause:
		/* empty */ 
		{
			NELSE_CLAUSE *nelse_clause = NULL;
			$$ = nelse_clause;
		}
	  	| ELSE StatementSequence
		{
			NELSE_CLAUSE *nelse_clause = malloc(sizeof(NELSE_CLAUSE));
			nelse_clause->state_seq = $2;
			$$ = nelse_clause;
		}
	  	;
WhileStatement:
	    WHILE Expression DO StatementSequence END
		{
			NWHILE *nwhile = malloc(sizeof(NWHILE));
			nwhile->express = $2;
			nwhile->state_seq = $4;
			$$ = nwhile;
		}
	    ;
WriteInt:
		WRITEINT Expression
		{
			NWRITE_INT *nwrite_int = malloc(sizeof(NWRITE_INT));
			nwrite_int->express = $2;
			$$ = nwrite_int;
		}
		;

Expression:
	   	SimpleExpression
		{
			NEXPRESSION *nexpression = malloc(sizeof(NEXPRESSION));
			nexpression->type = 1;
			nexpression->simple_express1 = $1;
			$$ = nexpression;
		}
	   	| SimpleExpression OP4 SimpleExpression
		{
			NEXPRESSION *nexpression = malloc(sizeof(NEXPRESSION));
			nexpression->type = 2;
			nexpression->simple_express1 = $1;
			nexpression->op = $2;
			nexpression->simple_express2 = $3;
			$$ = nexpression;
		} 
	   	;
SimpleExpression:
		Term OP3 Term
		{
			NSIMPLE *nsimple = malloc(sizeof(NSIMPLE));
			nsimple->type = 1;
			nsimple->term1 = $1;
			nsimple->op = $2;
			nsimple->term2 = $3;
			$$ = nsimple;
		} 
		| Term
		{
			NSIMPLE *nsimple = malloc(sizeof(NSIMPLE));
			nsimple->type = 2;
			nsimple->term1 = $1;
			$$ = nsimple;
		} 
		;
Term:
    	Factor OP2 Factor
		{
			NTERM *nterm = malloc(sizeof(NTERM));
			nterm->type = 1;
			nterm->factor1 = $1;
			nterm->op = $2;
			nterm->factor2 = $3;
			$$ = nterm;
		} 
    	| Factor
		{
			NTERM *nterm = malloc(sizeof(NTERM));
			nterm->type = 2;
			nterm->factor1 = $1;
			$$ = nterm;
		} 
    	;

Factor: 
      	ident
		{
			NFACTOR *nfactor = malloc(sizeof(NFACTOR));
			nfactor->type = 1;
			nfactor->str = $1;
			$$ = nfactor;
		} 
		| num
		{
			NFACTOR *nfactor = malloc(sizeof(NFACTOR));
			nfactor->type = 2;
			nfactor->num = $1;
			//printf("GOT BISON NUM %u", nfactor->num);
			$$ = nfactor;
		} 
		| boollit
		{
			NFACTOR *nfactor = malloc(sizeof(NFACTOR));
			nfactor->type = 3;
			nfactor->boollit = $1;
			$$ = nfactor;
		} 
		| LP Expression RP
		{
			NFACTOR *nfactor = malloc(sizeof(NFACTOR));
			nfactor->type = 4;
			nfactor->express = $2;
			$$ = nfactor;
		} 
%%
 void yyerror (char const *s) 
 {
   	fprintf (stderr, "%s\n", s);
 }
int main(int argc, char *argv[])
{
	yyparse();
	return 0;
}
