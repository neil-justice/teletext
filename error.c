/*  This module deals with error handling.  It has been created primarily to
 *  allow calls to the throwError function to be replaced during the 
 *  preprocessor stage if the program has been compiled in testing mode.
 *  It is also useful to have two different test-related modules for module
 *  dependency reasons, and to avoid circular dependencies.
 */ 

#include "error.h"

void throwError(errorType e, char *s)
{
  fprintf(stderr, "%s", s);
  if (e == fatal) {
    exit(EXIT_FAILURE);
  }
}

void mock_throwError(errorType e, char *s)
{
  /* the normal version of this prints a message to stderr,
   * and if (e == fatal) calls exit(EXIT_FAILURE)
   * This one prints to a file, where the output can be checked,
   * and doesn't call exit().  */
  FILE *errorlog = fopen(ERRORLOGFILE, "w");
  
  if (e == fatal) {
    fprintf(errorlog, "%s", EXITATTEMPT);
  }
  fprintf(errorlog, "%s", s);
  
  fclose(errorlog);
}

int checkErrorThrown(char *error)
{
  /* used in conjunction with mock_throwError, this function is used to check 
   * that the error type was passed properly. */
  FILE *errorlog = fopen(ERRORLOGFILE, "r");
  char s[ERRORSTRLEN];
  
  fgets(s, ERRORSTRLEN, errorlog);
  fclose(errorlog);
  
  if (strcmp(error,s) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}
