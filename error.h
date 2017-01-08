#include "base.h"

/* In testing mode, when the function being tested attempts to call exit, this 
 * string is written to the ERRORLOGFILE */
#define EXITATTEMPT "exit attempt logged\n" 

/* max length for EXITATTEMPT string */
#define ERRORSTRLEN 64

/* In testing mode, when the function being tested attempts to write to stderr 
 * or call exit, these are written here instead. */
#define ERRORLOGFILE "testfiles/errorlog.txt"

typedef enum errorType { fatal, warning } errorType;

void throwError(errorType e, char *s);
void mock_throwError(errorType e, char *s);
int checkErrorThrown(char *error);