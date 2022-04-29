#include "gencode.h"
int typeErrorFlag = 0;
void genprogram(struct NDECLARATIONS *decl, struct NSTATEMENT_SEQUENCE *state_seq)
{
    
    printf("#include <stdio.h>\n");
    printf("#include <stdbool.h>\n\n");
	printf("int main() {\n");
    genDecl(decl);
    genStateSeq(state_seq);
    printf("\n return 0;");
    printf("\n}\n");
    
    // print out the symbol table
    //printTable();
}
void genDecl(struct NDECLARATIONS *decl)
{
    if(decl == NULL)
    {
        return;
    }
    // look at the declarations, using linked list
    while(decl != NULL)
    {
        const char * type = genType(decl->type);
        printf(" %s = ", decl->str);
        if(strcmp(type, "bool") == 0)
        {
            printf("false;\n");
        }
         if(strcmp(type, "int") == 0)
        {
            printf("0;\n");
        }
        int identRedec = identRedecl(decl->str);
        if(identRedec != 1)
        {
            addEntry(type, decl->str);
        }
        decl = decl->decl;
    }
    printf("\n");
}
const char * genType(struct NTYPE *type)
{
    switch(type->type)
    {
        case 1:
            printf("int");
            return("int");
            break;
        case 2:
            printf("bool");
            return("bool");
            break;
    }
}
void genStateSeq(struct NSTATEMENT_SEQUENCE *state_seq)
{
   if(state_seq == NULL)
    {
        return;
    }
    genState(state_seq->state);
    if(state_seq->seq != NULL)
    {
        state_seq = state_seq->seq;
        genStateSeq(state_seq);
    }
}
void genState(struct NSTATEMENT *statement)
{
    //4 different types of statements
    switch(statement->type)
    {
        case 1:
            genAssignment(statement->assign);
            break;
        case 2:
            genIf(statement->if_state);
            break;
        case 3:
            genWhile(statement->while_state);
            break;
        case 4:
            genWriteInt(statement->writeInt);
            break;
    }
}
void genAssignment(struct NASSIGNMENT *assign)
{
    int present = verifyIdent(assign->str);
    if(present == 1)
    {
         switch(assign->type)
        {
            case 1:
            {
                updateInit(assign->str);
               int lType = getType(assign->str);
                printf("%s = ", assign->str);
                const char *rType = genExpression(assign->express);
                compareType(lType, rType);
                printf(";\n");
                break;
            }
            case 2:
            {
                updateInit(assign->str);
                printf("scanf(\"%%d\", &%s);\n", assign->str);
                break;
            }
        }
    }
}
void genIf(struct NIF_STATEMENT *if_state)
{
    printf("if (");
        genExpression(if_state->express);
    printf(")\n");
    printf("{\n");
    genStateSeq(if_state->state_seq);
    printf("}\n");
    if(if_state->else_clause != NULL)
    {
        genElseClause(if_state->else_clause);
    }
}
void genWhile(struct NWHILE *while_state)
{
    printf("while (");
    genExpression(while_state->express);
    printf(") \n{\n");
    genStateSeq(while_state->state_seq);
    printf("}\n");
}
void genWriteInt(struct NWRITE_INT *writeInt)
{
    printf("printf(\"%%d\\n\", ");
    genExpression(writeInt->express);
    printf(");\n");
}
void genElseClause(struct NELSE_CLAUSE *elseClause)
{
    printf("else \n{\n");
    genStateSeq(elseClause->state_seq);
    printf("}\n");
}
const char*  genExpression(struct NEXPRESSION *expression)
{
    struct returnSimple * simple1;
    struct returnSimple * simple2;
    switch(expression->type)
    {
        case 1:
            simple1 = genSimple(expression->simple_express1);
            if(simple1 != NULL)
            {
                if(simple1->s1 != NULL)
                {
                    if(simple1->s1->f1 != NULL)
                    {
                        if(simple1->s1->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s1->f1->ident);
                            }
                        }
                    }
                    if(simple1->s1->f2 != NULL)
                    {
                        if(simple1->s1->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s1->f2->ident);
                            }
                        }
                    }
                }
                if(simple1->s2 != NULL)
                {
                    if(simple1->s2->f1 != NULL)
                    {
                        if(simple1->s2->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s2->f1->ident);
                            }
                        }
                    }
                    if(simple1->s2->f2 != NULL)
                    {
                        if(simple1->s2->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                verifyTypeInt(simple1->s2->f2->ident);
                            }
                        }
                    }
                }

            }
            const char* type = "int";
            return type;
            break;
        case 2:
        {
            simple1 = genSimple(expression->simple_express1);
            if(simple1 != NULL)
            {
                if(simple1->s1 != NULL)
                {
                    if(simple1->s1->f1 != NULL)
                    {
                        if(simple1->s1->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s1->f1->ident);
                            }
                            
                        }
                    }
                    if(simple1->s1->f2 != NULL)
                    {
                        if(simple1->s1->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s1->f2->ident);
                            }
                        }
                    }
                }
                if(simple1->s2 != NULL)
                {
                    if(simple1->s2->f1 != NULL)
                    {
                        if(simple1->s2->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s2->f1->ident);
                            }
                        }
                    }
                    if(simple1->s2->f2 != NULL)
                    {
                        if(simple1->s2->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple1->s2->f2->ident);
                            }
                        }
                    }
                }

            }
            if(strcmp(expression->op, "=") == 0)
            {
                printf(" == ");
            }
            else
            {
                printf(" %s ",expression->op);
            }
            simple2 = genSimple(expression->simple_express2);
            if(simple2 != NULL)
            {
                if(simple2->s1 != NULL)
                {
                    if(simple2->s1->f1 != NULL)
                    {
                        if(simple2->s1->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple2->s1->f1->ident);
                            }
                        }
                    }
                    if(simple2->s1->f2 != NULL)
                    {
                        if(simple2->s1->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple2->s1->f2->ident);
                            }
                        }
                    }
                }
                if(simple2->s2 != NULL)
                {
                    if(simple2->s2->f1 != NULL)
                    {
                        if(simple2->s2->f1->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple2->s2->f1->ident);
                            }
                        }
                    }
                    if(simple2->s2->f2 != NULL)
                    {
                        if(simple2->s2->f2->ident != NULL)
                        {
                            if(!typeErrorFlag)
                            {
                                typeErrorFlag = verifyTypeInt(simple2->s2->f2->ident);
                            }
                        }
                    }
                }

            }
            const char* type = "bool";
            return type;
            break;
        }
        }
    typeErrorFlag = 0;
}
struct returnSimple* genSimple(struct NSIMPLE *simple)
{
    returnSimple * s = malloc(sizeof(returnSimple));
    struct returnTerm *term1;
    struct returnTerm *term2;
    switch(simple->type)
    {
        case 1:
            term1 = genTerm(simple->term1);
            if(term1 != NULL)
            {
                if(term1->f1 != NULL)
                {
                    if(term1->f1->ident != NULL)
                    {
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term1->f1->ident);
                        }
                    }
                }
                if(term1->f2 != NULL)
                {
                    if(term1->f2->ident != NULL)
                    {
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term1->f2->ident);
                        }
                    }
                }
            }
            printf(" %s ", simple->op);
            term2 = genTerm(simple->term2);
            if(term2 != NULL)
            {
                if(term2->f1 != NULL)
                {
                    if(term2->f1->ident != NULL)
                    {
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term2->f1->ident);
                        }
                    }
                }
                if(term2->f2 != NULL)
                {
                    if(term2->f2->ident != NULL)
                    {
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term2->f2->ident);
                        }
                    }
                }
            }
            s->s1 = term1;
            s->s2 = term2;
            return s;
            break;
        case 2:
        
            term1 = genTerm(simple->term1);
            if(term1 != NULL)
            {
                if(term1->f1 != NULL)
                {
                    if(term1->f1->ident != NULL)
                    {
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term1->f1->ident);
                        }
                    }
                }
                if(term1->f2 != NULL)
                {
                    if(term1->f2->ident != NULL)
                    {   
                        if(!typeErrorFlag)
                        {
                            typeErrorFlag = verifyTypeInt(term1->f2->ident);
                        }
                    }
                }
            }
            s->s1 = term1;
            return s;
            break;
        
    }
}
struct returnTerm* genTerm(struct NTERM *term)
{  
    returnTerm * s = malloc(sizeof(returnTerm));
    struct returnFactor *factor1;
    struct returnFactor *factor2;
    if(term->type == 1)
    {
        factor1 = genFactor(term->factor1);
        if(factor1->ident != NULL)
        {
            if(!typeErrorFlag)
            {
                typeErrorFlag = verifyTypeInt(factor1->ident);
            }
        }
        if(strcmp(term->op, "div") == 0)
        {
            printf(" / ");
        }
        else if(strcmp(term->op, "mod") == 0)
        {
            printf(" %% ");
        }
        else
        {
            printf(" %s ",term->op);
        }
        factor2 = genFactor(term->factor2);
        if(factor2->ident != NULL)
        {
            if(!typeErrorFlag)
            {
                typeErrorFlag = verifyTypeInt(factor2->ident);
            }
        }
        s->f1 = factor1;
        s->f2 = factor2;
        return s;  
    }
    else
    {
        factor1 = genFactor(term->factor1);
        if(factor1->ident != NULL)
        {
            if(!typeErrorFlag)
            {
                typeErrorFlag = verifyTypeInt(factor1->ident);
            }
        }
        s->f1 = factor1;
        return s;
    }
}
struct returnFactor* genFactor(struct NFACTOR *factor)
{
    returnFactor * s = malloc(sizeof(returnTerm));
    switch(factor->type)
    {
        case 1:
        {
            //ensure that all variables on right side have been declared
            int identInTable = verifyIdent(factor->str);
            if(identInTable == 1)
            {
                int identInitialalized = verifyInit(factor->str);
                if(identInitialalized == 1)
                {
                    printf("%s",factor->str);
                    const char * ident= factor->str;

                    int strLength = strlen(factor->str) + 1;
                    s->ident = malloc(strLength);
                    memset(s->ident, strLength, 0);
                    strcpy(s->ident, factor->str);
                }
            }
            break;
        }
        case 2:
        {
            int intInRange = verifyInt(factor->num);
            if(intInRange == 1)
            {
                printf("%d", factor->num);
                s->num = factor->num;
            }
            else
            {
                exit(1);
            }
            break;
        }
        case 3:
            printf("%s", factor->boollit);
            s->boollit = factor->boollit;
            break;
        case 4:
            printf("(");
            genExpression(factor->express);
            printf(")");
            break;
    }
    return s;
}


