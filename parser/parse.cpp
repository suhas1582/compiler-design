// #include "scan.h"
// #include "parse.h"

//  /* holds current token */

// /* function prototypes for recursive calls */
// // TreeNode * parse(void);

// // TreeNode * declList(void);
// // TreeNode * stmtList(void);
// // TreeNode * decl(void);
// // TreeNode * typeList(void);
// // TreeNode * varList(void);
// // TreeNode * stmt(void);
// // TreeNode * ifStmt(void);
// // TreeNode * elsePart(void);
// // TreeNode * whileStmt(void);
// // TreeNode * assignmentStmt(void);
// // TreeNode * readStmt(void);
// // TreeNode * printStmt(void);
// // TreeNode * bexp(void);
// // TreeNode * exp(void);

// void Parser::syntaxError(char * message) { 
//     fprintf(listing,"\n>>> ");
//     fprintf(listing,"Syntax error at line %d: %s", lineNo, message);
// }

// void Parser::match(TokenType expected) { 
//     if (token == expected) token = scanner.getToken();
//     else {
//         syntaxError("unexpected token -> ");
//         printToken(token, scanner.tokenString);
//         fprintf(listing,"      ");
//     }
// }

// TreeNode* Parser::stmtList(void) { 
//     TreeNode* t = statement();
//     TreeNode* p = t;
//     while ((token!=ENDFILE) && (token!=END) &&
//             (token!=ELSE) && (token!=WHILE)) { 
//         TreeNode * q;
//         match(SEMICOL);
//         q = statement();
//         if (q!=NULL) {
//         if (t==NULL) t = p = q;
//         else /* now p cannot be NULL either */
//         { p->sibling = q;
//             p = q;
//         }
//         }
//     }
//     return t;
// }

// TreeNode * statement(void)
// { TreeNode * t = NULL;
//   switch (token) {
//     case IF : t = if_stmt(); break;
//     case REPEAT : t = repeat_stmt(); break;
//     case ID : t = assign_stmt(); break;
//     case READ : t = read_stmt(); break;
//     case WRITE : t = write_stmt(); break;
//     default : syntaxError("unexpected token -> ");
//               printToken(token,tokenString);
//               token = getToken();
//               break;
//   } /* end case */
//   return t;
// }

// TreeNode * if_stmt(void)
// { TreeNode * t = newStmtNode(IfK);
//   match(IF);
//   if (t!=NULL) t->child[0] = exp();
//   match(THEN);
//   if (t!=NULL) t->child[1] = stmt_sequence();
//   if (token==ELSE) {
//     match(ELSE);
//     if (t!=NULL) t->child[2] = stmt_sequence();
//   }
//   match(END);
//   return t;
// }

// TreeNode * repeat_stmt(void)
// { TreeNode * t = newStmtNode(RepeatK);
//   match(REPEAT);
//   if (t!=NULL) t->child[0] = stmt_sequence();
//   match(UNTIL);
//   if (t!=NULL) t->child[1] = exp();
//   return t;
// }

// TreeNode * assign_stmt(void)
// { TreeNode * t = newStmtNode(AssignK);
//   if ((t!=NULL) && (token==ID))
//     t->attr.name = copyString(tokenString);
//   match(ID);
//   match(ASSIGN);
//   if (t!=NULL) t->child[0] = exp();
//   return t;
// }

// TreeNode * read_stmt(void)
// { TreeNode * t = newStmtNode(ReadK);
//   match(READ);
//   if ((t!=NULL) && (token==ID))
//     t->attr.name = copyString(tokenString);
//   match(ID);
//   return t;
// }

// TreeNode * write_stmt(void)
// { TreeNode * t = newStmtNode(WriteK);
//   match(WRITE);
//   if (t!=NULL) t->child[0] = exp();
//   return t;
// }

// TreeNode * exp(void)
// { TreeNode * t = simple_exp();
//   if ((token==LT)||(token==EQ)) {
//     TreeNode * p = newExpNode(OpK);
//     if (p!=NULL) {
//       p->child[0] = t;
//       p->attr.op = token;
//       t = p;
//     }
//     match(token);
//     if (t!=NULL)
//       t->child[1] = simple_exp();
//   }
//   return t;
// }

// TreeNode * simple_exp(void)
// { TreeNode * t = term();
//   while ((token==PLUS)||(token==MINUS))
//   { TreeNode * p = newExpNode(OpK);
//     if (p!=NULL) {
//       p->child[0] = t;
//       p->attr.op = token;
//       t = p;
//       match(token);
//       t->child[1] = term();
//     }
//   }
//   return t;
// }

// TreeNode * term(void)
// { TreeNode * t = factor();
//   while ((token==TIMES)||(token==OVER))
//   { TreeNode * p = newExpNode(OpK);
//     if (p!=NULL) {
//       p->child[0] = t;
//       p->attr.op = token;
//       t = p;
//       match(token);
//       p->child[1] = factor();
//     }
//   }
//   return t;
// }

// TreeNode * factor(void)
// { TreeNode * t = NULL;
//   switch (token) {
//     case NUM :
//       t = newExpNode(ConstK);
//       if ((t!=NULL) && (token==NUM))
//         t->attr.val = atoi(tokenString);
//       match(NUM);
//       break;
//     case ID :
//       t = newExpNode(IdK);
//       if ((t!=NULL) && (token==ID))
//         t->attr.name = copyString(tokenString);
//       match(ID);
//       break;
//     case LPAREN :
//       match(LPAREN);
//       t = exp();
//       match(RPAREN);
//       break;
//     default:
//       syntaxError("unexpected token -> ");
//       printToken(token,tokenString);
//       token = getToken();
//       break;
//     }
//   return t;
// }

// /****************************************/
// /* the primary function of the parser   */
// /****************************************/
// /* Function parse returns the newly 
//  * constructed syntax tree
//  */
// TreeNode * parse(void)
// { TreeNode * t;
//   token = getToken();
//   t = stmt_sequence();
//   if (token!=ENDFILE)
//     syntaxError("Code ends before file\n");
//   return t;
// }