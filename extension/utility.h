#include "../display.h"

#define CNTRLCODESTRLEN 21 /* Longest control code name + EOS char */
#define CODENUM 22 /* Number of control codes. */

/* Used in function controlCodeLookup to allow lookup by array index or code: */
typedef enum lookupMode { codelookup, indexlookup } lookupMode;

typedef struct lookup {
  char str[CNTRLCODESTRLEN];
  myUint8 code;
} lookup;

lookup *controlCodeLookup(myUint8 code, unsigned int index, lookupMode mode);
