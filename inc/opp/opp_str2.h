/*
 * opp_str2.h
 *
 *  Created on: Mar 2, 2011
 *      Author: Kamanashis Roy
 */

#ifndef OPP_STR2_H_
#define OPP_STR2_H_

#include "sync/config.h"
#include "opp/opp_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

char*opp_str2_reuse(char*string);
void opp_str2_reuse2(char**dest, char*string);
char*opp_str2_dup(const char*string);
void opp_str2_dup2(char**dest, const char*string);
char*opp_str2_alloc(int size);

void opp_str2system_verb(void (*log)(void *log_data, const char*fmt, ...), void*log_data);
void opp_str2system_init();
void opp_str2system_deinit();

#ifdef __cplusplus
}
#endif

#endif /* OPP_STR2_H_ */
