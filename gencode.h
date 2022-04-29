#ifndef GENCODE_H_   /* Include guard */
#define GENCODE_H_
#include "ParseTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct returnFactor{
    const char *ident;
    int num;
    const char *boollit;
}returnFactor;
typedef struct returnTerm{
    struct returnFactor *f1;
    struct returnFactor *f2;
}returnTerm;

typedef struct returnSimple{
    struct returnTerm *s1;
    struct returnTerm *s2;
}returnSimple;
void genprogram(struct NDECLARATIONS *decl, struct NSTATEMENT_SEQUENCE *state_seq);
void genDecl(struct NDECLARATIONS *decl);
void genStateSeq(struct NSTATEMENT_SEQUENCE *state_seq);
const char * genType(struct NTYPE *NTYPE);
void genState(struct NSTATEMENT *state);
void genAssignment(struct NASSIGNMENT *assign);
void genIf(struct NIF_STATEMENT *if_state);
void genWhile(struct NWHILE *while_state);
void genWriteInt(struct NWRITE_INT *writeInt);
void genElseClause(struct NELSE_CLAUSE *elseClause);
const char* genExpression(struct NEXPRESSION *expression);
struct returnSimple * genSimple(struct NSIMPLE *simple);
struct returnTerm * genTerm(struct NTERM *term);
struct returnFactor* genFactor(struct NFACTOR *factor);
// for the symbol table functions
void addEntry(const char* type, const char* ident);
int identRedecl(const char* ident);
int verifyIdent(const char* ident);
void updateInit(const char* ident);
int verifyInit(const char* ident);
int verifyInt(int num);
int verifyTypeInt(const char* ident);
int getType(const char* ident);
void compareType(int lType, const char *rType);

void printTable();
#endif