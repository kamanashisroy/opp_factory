/*
 * hash.c
 *
 *  Created on: Dec 27, 2010
 *      Author: kgm212
 */


#include "sync/hash.h"
C_CAPSULE_START

/*********************************************************************/
/**************** copied from sqlite3 file:util.c ********************/
/*********************************************************************/
/* An array to map all upper-case characters into their corresponding
** lower-case character.
*/
static unsigned char UpperToLower[] = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17,
     18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
     36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
     54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 97, 98, 99,100,101,102,103,
    104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,
    122, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,106,107,
    108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,
    126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,
    162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
    180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,
    198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,
    216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,
    234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,
    252,253,254,255
};

#define FNV
/*
** This function computes a hash on the name of a keyword.
** Case is not significant.
*/
unsigned long get_hash(const char *z){
  unsigned long h = 0, n = 0;
#ifdef FNV
	h = 20; // FNV ofset basis
#endif
  if( n<=0 ) n = strlen(z);
  while( n > 0  ){
#ifdef FNV
		h = h * 2; // FNV prime
#endif
    h = h ^ UpperToLower[(unsigned char)*z++];
    n--;
  }

  return  h;
}


unsigned long get_hash_bin(const void*data, int size) {
	/* This code implementation is copied from static int binHash(const void *pKey, int nKey) of hash.c file of sqlite project */
	int h = 0;
	const char *z = (const char *)data;
	while( size-- > 0 ){
	h = (h<<3) ^ h ^ *(z++);
	}
	return h & 0x7fffffff;
}

/*********************************************************************/
/*********************************************************************/

#ifdef SYNC_SYSTEM_TEST
int hash_test() {
	return 0;
}
#endif

C_CAPSULE_END
