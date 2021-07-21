#pragma once

#include "../util/util.h" 

#ifndef _SCAN_H_
#define _SCAN_H_

class Scanner {

    public:
        #define MAXTOKENLEN 50
        #define BUFLEN 256
        
        char tokenString[MAXTOKENLEN+1];

        TokenType getToken(void); 

        typedef enum {START, INASSIGN, INCOMMENT, INNUM, INID, DONE} StateType;

        static char linBuf[BUFLEN];
        static int linepos;
        static int bufsize;

        static char getNextChar();

        static void ungetNextChar();

    private:
        TokenType reservedLookup(char*); 
        
};

typedef struct {
    char* str;
    TokenType token;
} ResWordsStore;

static ResWordsStore reserveWords[MAXRESERVED] = {
    {"global", GLOBAL}, {"end", END}, {"def", DEF}, {"bool", BOOL}, {"else", ELSE}, {"false", FALSE}, {"if", IF}, {"int", INT}, {"true", TRUE}, {"while", WHILE}, {"print", PRINT}, {"or", OR}, {"and", AND}, {"char", CHAR}, {"read", READ}
};

#endif