#ifndef OPP_FACTORY_PROFILER_H
#define OPP_FACTORY_PROFILER_H

/**
 *
 * This is an implementation of object based information
 * manipulation system. Please use "opp_" prefix in the
 * variable name. And remember to OPPUNREF()
 * that object.
 */

#include "sync/config.h"

#ifdef __cplusplus
extern "C" {
#endif


struct opp_factory_profiler_info {
	char*source_file;
	int source_line;
	char*module_name;
	struct tm birth;
	struct opp_factory*obuff;
};

#define OPP_PFACTORY_CREATE_FULL(_obuff, _psize, _objsize, _tokenstart, _property, _cb) ({opp_factory_create_full_and_profile(_obuff, _psize, _objsize, _tokenstart, _property, _cb, __FILE__, __LINE__, "libsync");})
#define OPP_PFACTORY_CREATE(obuff, x, y, z) ({opp_factory_create_full_and_profile(obuff, x, y, 1, OPPF_HAS_LOCK | OPPF_SWEEP_ON_UNREF, z, __FILE__, __LINE__, "libsync");})
int opp_factory_create_full_and_profile(struct opp_factory*obuff
		, int inc
		, SYNC_UWORD16_T obj_size
		, int token_offset
		, unsigned char property
		, int (*callback)(void*data, int callback, void*cb_data, va_list ap)
		, char*source_file, int source_line, char*module_name);
#define OPP_PFACTORY_DESTROY(x) opp_factory_destroy_and_remove_profile(x)
int opp_factory_destroy_and_remove_profile(struct opp_factory*src);

int opp_factory_profiler_init();
int opp_factory_profiler_deinit();
void opp_factory_profiler_visit(int (*obj_do)(void*data, void*func_data), void*func_data);

void opp_factory_profiler_get_total_memory(int*grasped,int*really_allocated);
void*profiler_replace_malloc(size_t size);
void profiler_replace_free(void*ptr, size_t size);

#define OPP_FACTORY_PROFILER_DUMP_HEADER_FMT() "%-20.20s %-5.5s %-10.10s %-10.10s"
#define OPP_FACTORY_PROFILER_DUMP_HEADER_ARG() "Source","Line", "Module","Birth"
#define OPP_FACTORY_PROFILER_DUMP_FMT() "%-20.20s %5d %-10.10s %s"
#define OPP_FACTORY_PROFILER_DUMP_ARG(x) STR_OR((x)->source_file, ""), (x)->source_line, STR_OR((x)->module_name, ""), asctime(&(x)->birth)

#define OPP_FACTORY_PROFILER_DUMP_HEADER_FMT2() "%-20.20s %-5.5s %-10.10s"
#define OPP_FACTORY_PROFILER_DUMP_HEADER_ARG2() "Source","Line", "Module"
#define OPP_FACTORY_PROFILER_DUMP_FMT2() "%-20.20s %5d %-10.10s"
#define OPP_FACTORY_PROFILER_DUMP_ARG2(x) STR_OR((x)->source_file, ""), (x)->source_line, STR_OR((x)->module_name, "")


void opp_factory_profiler_checkleak_debug();
//#define opp_factory_profiler_checkleak() opp_factory_profiler_checkleak_debug()
#define opp_factory_profiler_checkleak()

#ifdef __cplusplus
}
#endif


#endif // OPP_FACTORY_PROFILER_H
