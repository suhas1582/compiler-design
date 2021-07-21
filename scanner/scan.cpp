#pragma once

#include "scan.h"

char Scanner::getNextChar() {
    if(!(linepos < bufsize)) {
        lineNo++;
        if(fgets(linBuf, BUFLEN-1, source)) {
            fprintf(listing, "%d: %s", lineNo, linBuf);
            bufsize = strlen(linBuf);
            linepos = 0;
            return linBuf[linepos++];
        }
        else {
            return EOF;
        }
    }
    else {
        return linBuf[linepos++];
    }
}

void Scanner::ungetNextChar() {
    linepos--;
}

TokenType Scanner::reservedLookup(char* s) {
    int i;
    for(i=0;i<MAXRESERVED;i++) {
        if(!strcmp(s, reserveWords[i].str)) {
            return reserveWords[i].token;
        }
    }
    return ID;
}

TokenType Scanner::getToken() {
    int tokenStringIndex = 0;
    TokenType currentToken;
    StateType state = START;
    int save;

    while(state != DONE) {
        char c = getNextChar();
        save = True;
        switch(state) {
            case START:
                if(isdigit(c))
                    state = INNUM;
                else if(isalpha(c)) 
                    state = INID;
                else if(c == '=')
                    state = INASSIGN;
                else if((c == ' ') || (c == '\t') || c == '\n') 
                    save = False;
                // else if(c == '{') {
                //     save = False;
                //     state = INCOMMENT;
                // }
                else {
                    state = DONE;
                    switch(c) {
                        case EOF:
                            save = False;
                            currentToken = ENDFILE;
                            break;
                        case '=':
                            currentToken = ASSIGN;
                            break;
                        case '<':
                            currentToken = LT;
                            break;
                        case '+':
                            currentToken = PLUS;
                            break;
                        case '-':
                            currentToken = MINUS;
                            break;
                        case '*':
                            currentToken = TIMES;
                            break;
                        case '/':
                            currentToken = OVER;
                            break;
                        case '(':
                            currentToken = LPAREN;
                            break;
                        case ')':
                            currentToken = RPAREN;
                            break;
                        case ';':
                            currentToken = SEMICOL;
                            break;
                        case ':':
                            currentToken = COL;
                            break;
                        default:
                            currentToken = ERROR;
                            break;
                    }

                }
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=')
                    currentToken = ASSIGN;
                else { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    currentToken = ERROR;
                }
                break;
            case INNUM:
            if (!isdigit(c)) { /* backup in the input */
                ungetNextChar();
                save = FALSE;
                state = DONE;
                currentToken = NUMBER;
            }
                break;
            case INID:
                if (!isalpha(c)) { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case DONE:
            default: /* should never happen */
                fprintf(listing,"Scanner Bug: state= %d\n",state);
                state = DONE;
                currentToken = ERROR;
                break;
        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN))
            tokenString[tokenStringIndex++] = (char) c;
        if (state == DONE) { 
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID)
                currentToken = reservedLookup(tokenString);
        }
   }
    fprintf(listing,"\t%d: ",lineNo);
    printToken(currentToken,tokenString);
    return currentToken;
                
}
