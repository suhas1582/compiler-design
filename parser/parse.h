#ifndef _PARSE_H_
#define _PARSE_H_

class Parser {

    public:

        TokenType token;

        Scanner scanner = Scanner();

        TreeNode* parse(void);
        TreeNode* declList(void);
        TreeNode* stmtList(void);
        TreeNode* decl(void);
        TreeNode* typeList(void);
        TreeNode* varList(void);
        TreeNode* stmt(void);
        TreeNode* ifStmt(void);
        TreeNode* elsePart(void);
        TreeNode* whileStmt(void);
        TreeNode* assignmentStmt(void);
        TreeNode* readStmt(void);
        TreeNode* printStmt(void);
        TreeNode* bexp(void);
        TreeNode* exp(void);
        void syntaxError(char* message);
        void match(TokenType expected);

};

#endif