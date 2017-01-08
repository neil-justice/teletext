/* Utility module.  This lookup table is used in several places in the control 
 * flow, so was put here. It can return values based on index or code, depending
 * on the lookup mode. */
#include "utility.h"

lookup *controlCodeLookup(myUint8 code, unsigned int index, lookupMode mode)
{ 
  /* Can be referenced by either array index or control code - lookupMode
   * determines which. */
  int i;
  static lookup l[CODENUM] = {
    { "Red Alphanumeric",    0x81},
    { "Green Alphanumeric",  0x82},
    { "Yellow Alphanumeric", 0x83},
    { "Blue Alphanumeric",   0x84},
    { "Magenta Alphanumeric",0x85},
    { "Cyan Alphanumeric",   0x86},
    { "White Alphanumeric",  0x87},
    { "Red Graphics",        0x91},
    { "Green Graphics",      0x92},
    { "Yellow Graphics",     0x93},
    { "Blue Graphics",       0x94},
    { "Magenta Graphics",    0x95},
    { "Cyan Graphics",       0x96},
    { "White Graphics",      0x97},
    { "Contiguous Graphics", 0x99},
    { "Separated Graphics",  0x9a},
    { "Black Background",    0x9c},
    { "New Background",      0x9d},
    { "Single Height",       0x8c},
    { "Double Height",       0x8d},
    { "Hold Graphics",       0x9e},
    { "Release Graphics",    0x9f} };
  
  if (mode == codelookup) {
    for (i = 0; i < CODENUM; i++) {
      if (code == l[i].code) {
        return &l[i];
      }
    }
  }
  else if (mode == indexlookup) {
    return &l[index];
  }

  throwError(warning,"Invalid lookup mode\n");
  return NULL;
}