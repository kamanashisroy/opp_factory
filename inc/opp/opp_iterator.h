/*
 * obj_iterator.h
 *
 *  Created on: Jun 19, 2011
 *      Author: ayaskanti
 */

#ifndef OPP_INTERNAL_H
#define OPP_INTERNAL_H

#include "opp/opp_factory.h"

struct opp_iterator {
	struct opp_factory*fac;
	unsigned int if_flag;
	unsigned int if_not_flag;
	opp_hash_t hash;
	unsigned char k;
	struct opp_pool*pool;
	int bit_idx;
	void*data;
};

int opp_iterator_create(struct opp_iterator*iterator, struct opp_factory*fac, unsigned int if_flag, unsigned int if_not_flag, opp_hash_t hash);
void*opp_iterator_next(struct opp_iterator*iterator);
int opp_iterator_destroy(struct opp_iterator*iterator);
void opp_factory_do_full(struct opp_factory*obuff, int (*obj_do)(void*data, void*func_data), void*func_data, unsigned int if_flag, unsigned int if_not_flag, opp_hash_t hash);
void opp_factory_list_do_full(struct opp_factory*obuff, int (*obj_do)(void*data, void*func_data), void*func_data
		, unsigned int if_list_flag, unsigned int if_not_list_flag, unsigned int if_flag, unsigned int if_not_flag
		, opp_hash_t list_hash, opp_hash_t hash);
void opp_factory_do_pre_order(struct opp_factory*obuff, int (*obj_do)(void*data, void*func_data), void*func_data, unsigned int if_flag
		, unsigned int if_not_flag);
#define OPP_FACTORY_DO(x, y, z) ({opp_factory_do_full(x, y, z, OPPN_ALL, 0, 0);})

// find api
#define OPP_FIND_NOREF(x, y, z) ({opp_find_full(x, y, z, OPPN_ALL, 0, 0, 0);})
#define OPP_FIND(x, y, z) ({opp_find_full(x, y, z, OPPN_ALL, 0, 0, 1);})
void*opp_find_full(struct opp_factory*obuff, int (*compare_func)(const void*data, const void*compare_data), const void*compare_data, unsigned int if_flag, unsigned int if_not_flag, opp_hash_t hash, unsigned int shouldref);
#define OPP_FIND_LIST_DO_NOT_USE(x,y,z) ({opp_find_list_full_donot_use(x,y,z, OPPN_ALL, 0x00, 0, 1);})
void*opp_find_list_full_donot_use(struct opp_factory*obuff, int (*compare_func)(const void*data, const void*compare_data)
		, const void*compare_data, unsigned int if_flag, unsigned int if_not_flag, opp_hash_t hash, int shouldref);

void*opp_search(struct opp_factory*obuff, opp_hash_t hash, int (*compare_func)(const void*data, const void*compare_data), const void*compare_data);

#endif /* OPP_INTERNAL_H */
