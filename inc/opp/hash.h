/*
 * hash.h
 *
 *  Created on: Dec 27, 2010
 *      Author: kgm212
 */

#ifndef HASH_H_
#define HASH_H_
#include "sync/config.h"
unsigned long get_hash(const char *z);
unsigned long get_hash_bin(const void*data, int size);

#ifdef SYNC_SYSTEM_TEST
int hash_test();
#endif


#endif /* HASH_H_ */
