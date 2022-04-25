typedef struct NPROGRAM NPROGRAM;
typedef struct NDECLARATIONS NDECLARATIONS;
typedef struct NTYPE NTYPE;
typedef struct NSTATEMENT_SEQUENCE NSTATEMENT_SEQUENCE;
typedef struct NSTATEMENT NSTATEMENT;
typedef struct NASSIGNMENT NASSIGNMENT;
typedef struct NIF_STATEMENT NIF_STATEMENT;
typedef struct NELSE_CLAUSE NELSE_CLAUSE;
typedef struct NWHILE NWHILE;
typedef struct NWRITE_INT NWRITE_INT;
typedef struct NEXPRESSION NEXPRESSION;
typedef struct NSIMPLE NSIMPLE;
typedef struct NTERM NTERM;
typedef struct NFACTOR NFACTOR;

struct NPROGRAM{
    NDECLARATIONS *decl;
    NSTATEMENT_SEQUENCE *statement_seq;
};

struct NDECLARATIONS{
    char *str;
    const char *t;
    NTYPE *type;
    NDECLARATIONS *decl; //use linked list bc recursive (While list not empty)
};

struct NSTATEMENT_SEQUENCE{
    NSTATEMENT *state;
    NSTATEMENT_SEQUENCE *seq;            
    
};

struct NSTATEMENT{
    int type;
    NASSIGNMENT *assign;
    NIF_STATEMENT *if_state;
    NWHILE *while_state;
    NWRITE_INT *writeInt;
};

struct NASSIGNMENT{
    int type;
    char *str;
    NEXPRESSION *express;
};

struct NIF_STATEMENT{
    NEXPRESSION *express;
    NSTATEMENT_SEQUENCE *state_seq;
    NELSE_CLAUSE *else_clause;
};

struct NELSE_CLAUSE{
    NSTATEMENT_SEQUENCE *state_seq;
};

struct NWHILE{
    NEXPRESSION *express;
    NSTATEMENT_SEQUENCE *state_seq;
};

struct NWRITE_INT{
    NEXPRESSION *express;
};

struct NEXPRESSION{
    int type;
    NSIMPLE *simple_express1;
    NSIMPLE *simple_express2;
    char *op;
};

struct NSIMPLE{
    int type;
    NTERM *term1;
    NTERM *term2;
    char *op;
};

struct NTERM{
    int type;
    NFACTOR *factor1;
    NFACTOR *factor2;
    char *op;
};

struct NFACTOR{
    int type;
    int num;
    char* boollit;
    char* str;
    NEXPRESSION *express;
};

struct NTYPE{
    int type;
    int num;
    char * truth;
};



