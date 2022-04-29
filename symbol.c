#include "uthash.h"
#include <string.h>
#include <stdio.h>
/*
    Errors I identify:
        1) Identifier not declared
        2) Enforce int range
        3) Identifier redeclaration
        4) Type Constraints (in assignments and in expressions)

        TYPE CONSTRAINTS FOR ASSIGNMENT
*/
struct symbol {
    const char *ident;
    const char *type;
    char initial;
    UT_hash_handle hh;
};
struct symbol *symbols = NULL;
void printTable()
{
    printf("/*\n");
    struct symbol *s;
    printf("identifier | Type | Initialized \n");
    for (s = symbols; s != NULL; s = s->hh.next) {
        printf("%s | %s | %c\n", s->ident, s->type, s->initial);
    }
     printf("*/");
}
void addEntry(const char* type, const char* ident)
{
    struct symbol *s;
    s = malloc(sizeof(struct symbol));
   // strcpy(s->ident,ident);
    s->ident = ident;
    s->type = type;
    //strcpy(s->type,type);
    s->initial = 'T';
    HASH_ADD_STR(symbols, ident, s);  //ident is key
    
}
int verifyIdent(const char* ident)
{
    struct symbol *s;
    HASH_FIND_STR(symbols, ident, s);  /* s: output pointer */
    if(s)
    {
        // ident is present
        return 1;
    }
    else
    {
        // ident is not present
        printf("//ERROR: %s, has not yet been declared\n", ident);
        return 0;
    }
}
void updateInit(const char* ident)
{
    struct symbol *s;
    HASH_FIND_STR(symbols,ident, s);
    s->initial = 'T';
}
int verifyInit(const char* ident)
{
    struct symbol *s;
    HASH_FIND_STR(symbols,ident, s);
    if(s->initial == 'T')
    {
        return 1;
    }
    else
    {
        printf("//ERROR: %s, has not yet been initialized\n", ident);
    }
}
int verifyInt(int num)
 {
    if( num > 2147483647 || num < 0)
    {
        printf("//Error: %u is not a valid number\n", num);
    }
    else
    {
        return 1;
    }
 }
int identRedecl(const char* ident)
 {
    struct symbol *s;
    HASH_FIND_STR(symbols,ident, s);  /* s: output pointer */
    if(s)
    {
        printf("//Error: Identifier, %s, is being redeclared\n", ident);
        return 1;
    }
    else
    {
        return 0;
    }
 }
int verifyTypeInt(const char* ident)
 {
    struct symbol *s;
    HASH_FIND_STR(symbols,ident, s);
    if(strcmp(s->type, "bool") == 0)
    {
        printf("//ERROR: %s, is not of type int\n", ident);
        return 1;
    }
    else
    {
        return 0;
    }
 } 
 int getType(const char* ident)
 {
    struct symbol *s;
    HASH_FIND_STR(symbols,ident, s);
    if(strcmp(s->type, "bool") == 0)
    {
        printf("//ERROR: %s, is not of type int\n", ident);
        return 0;
    }
    else if(strcmp(s->type, "int") == 0)
    {
        return 1;
    }
 }
 void compareType(int lType, const char *rType)
 {
    if((lType == 0 && strcmp(rType, "int") == 0) || (lType == 1 && strcmp(rType, "bool") == 0))
    {
        printf("//ERROR: Left hand side type, does not match right hand side type, %s",rType);
    }
 }
