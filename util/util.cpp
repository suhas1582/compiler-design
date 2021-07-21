#include "util.h"

#define INDENT indentno += 2
#define UNINDENT indentno -= 2

static int indentno = 0;

void printToken(TokenType token, const char* tokenString) {
    switch(token) {
        case IF:
        case ELSE:
        case END:
        case WHILE:
        case READ:
        case GLOBAL:
        case TRUE:
        case FALSE:
        case BOOL:
        case INT:
        case CHAR:
        case DEF:
        case AND:
        case OR:
        case PRINT:
            fprintf(listing, "reserved word: %s\n", tokenString);
            break;
        case ASSIGN:
            fprintf(listing, "=\n");
            break;
        case LT:
            fprintf(listing, "<\n");
            break;
        case EQ:
            fprintf(listing, "==\n");
            break;
        case PLUS:
            fprintf(listing, "+\n");
            break;
        case MINUS:
            fprintf(listing, "-\n");
            break;
        case TIMES:
            fprintf(listing, "*\n");
            break;
        case OVER:
            fprintf(listing, "/\n");
            break;
        case LPAREN:
            fprintf(listing, "(\n");
            break;
        case RPAREN:
            fprintf(listing, ")\n");
            break;
        case SEMICOL:
            fprintf(listing, ";\n");
            break;
        case COL:
            fprintf(listing, ":\n");
            break;
        case COMMA:
            fprintf(listing, ",\n");
            break;
        case ENDFILE:
            fprintf(listing, "EOF\n");
            break;
        case ID:
            fprintf(listing, "ID, name= %s\n", tokenString);
            break;
        case NUMBER:
            fprintf(listing, "NUM, val= %s\n", tokenString);
            break;
        case ERROR:
            fprintf(listing, "ERROR: %s\n", tokenString);
            break;
        default:
            fprintf(listing, "Unknown token: %d\n", tokenString);
        
    }
}

TreeNode* newStmtNode(StmtKind kind) {
    TreeNode* t = (TreeNode*) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL) {
        fprintf(listing, "Out of memory erroor at line %d\n", lineNo);
    }
    else {
        for(i=0;i<MAXCHILDREN;i++) {
            t->child[i] = NULL;
        }
        t->sibling = NULL;
        t->nodeKind = StmtK;
        t->kind.stmt = kind;
        t->lineNo = lineNo;
    }
    return t;
}

TreeNode* newExpNode(ExpKind kind) {
    TreeNode* t = (TreeNode*) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL) {
        fprintf(listing, "Out of memory error at line %d\n", lineNo);
    }
    else {
        for(i=0;i<MAXCHILDREN;i++) {
            t->child[i] = NULL;
        }
        t->sibling = NULL;
        t->nodeKind = ExpK;
        t->kind.exp = kind;
        t->lineNo = lineNo;
        t->type = Void;
    }
    return t;
}

TreeNode* newDeclNode(DeclKind kind) {
    TreeNode* t = (TreeNode*) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL) {
        fprintf(listing, "Out of memory error at line %d\n", lineNo);
    }
    else {
        for(i=0;i<MAXCHILDREN;i++) {
            t->child[i] = NULL;
        }
        t->sibling = NULL;
        t->nodeKind = DeclK;
        t->kind.decl = kind;
        t->lineNo = lineNo;
    }
    return t;
}

char* copyString(char* s) {
    int n;
    char* t;
    if(s == NULL) {
        return NULL;
    }
    n = strlen(s) + 1;
    t = (char*)malloc(n);
    if(t == NULL) {
        fprintf(listing, "Out of memory error at line %d\n", lineNo);
    }
    else {
        strcpy(t, s);
    }
    return t;
}

static void printSpaces() {
    int i;
    for(i=0;i<indentno;i++) {
        fprintf(listing, " ");
    }
}

void printTree(TreeNode* tree) {
    int i;
    INDENT;
    while(tree != NULL) {
        printSpaces();
        if(tree->nodeKind == StmtK) {
            switch(tree->kind.stmt) {
                case IfK:
                    fprintf(listing, "If\n");
                    break;
                case WhileK:
                    fprintf(listing, "While\n");
                    break;
                case AssignK:
                    fprintf(listing, "Assign to: %s\n", tree->attr.name);
                    break;
                case ReadK:
                    fprintf(listing, "Read: %s\n", tree->attr.name);
                    break;
                case PrintK:
                    fprintf(listing, "Print\n");
                    break;
                default:
                    fprintf(listing, "Unknown StmtNode Kind\n");
                    break;
            }
        }
        else if(tree->nodeKind == ExpK) {
            switch(tree->kind.exp) {
                case OpK:
                    fprintf(listing, "Op: ");
                    printToken(tree->attr.op, "\0");
                    break;
                case ConstK:
                    fprintf(listing, "const: %d\n", tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing, "Id: %s\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode Kind\n");
                    break;
            }
        }
        else if(tree->nodeKind == DeclK) {
            switch(tree->kind.decl) {
                case IntK:
                    fprintf(listing, "INT: %s", tree->attr.name);
                    break;
                case CharK:
                    fprintf(listing, "CHAR: %s", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unkown DeclNode kind\n");
                    break;
            }
        }
        else {
            fprintf(listing, "Unknown node kind\n");
        }
        for(i=0;i<MAXCHILDREN;i++) {
            printTree(tree->child[i]);
        }
        tree = tree->sibling;
    }
    UNINDENT;
}