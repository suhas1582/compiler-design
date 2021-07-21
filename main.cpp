// #include "globals.h"
// #include "./util/util.h"
#include "./scanner/scan.h"
#include "./parser/parse.h"

using namespace std;

/* Allocate the global variables */
int lineNo;
FILE* sourceFile;
FILE* listingFile;

int error = False;

int main(int argc, char* argv[]) {
    cout << "Hello World!" << endl;
    return 0;
}
