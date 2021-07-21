#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

#define MAXRESERVED 15

typedef enum {
    // BOOK KEEPING TOKENS
    ENDFILE, ERROR,
    // RESERVED WORDS
    GLOBAL, END, DEF, BOOL, ELSE, FALSE, IF, INT, TRUE, WHILE, PRINT, OR, AND, CHAR, READ,
    // MULTICHARACTER TOKENS
    ID, NUMBER,
    // SPECIAL SYMBOLS
    SEMICOL, COL, COMMA, ASSIGN, LPAREN, RPAREN, PLUS, MINUS, TIMES, OVER, LT, EQ
} TokenType;

extern FILE* source;
extern FILE* listing;

extern int lineNo;

typedef enum {StmtK, ExpK, DeclK} NodeKind;

typedef enum {AssignK, ReadK, PrintK, IfK, WhileK} StmtKind;

typedef enum {OpK, ConstK, IdK} ExpKind;

typedef enum {IntK, CharK} DeclKind;

typedef enum {Void, Integer, Boolean} ExpType;


#define MAXCHILDREN 3

typedef struct treeNode {
    struct treeNode* child[MAXCHILDREN];
    struct treeNode* sibling;
    int lineNo;
    NodeKind nodeKind;
    union {StmtKind stmt; ExpKind exp; DeclKind decl;} kind;
    union {
        TokenType op;
        int val;
        char* name;
        
    } attr;
    DeclKind dtype;
    ExpType type;
} TreeNode;
