#ifndef OPP_FACTORY_UTILS_H
#define OPP_FACTORY_UTILS_H

/**
 *
 * This is an implementation of object based information
 * manipulation system. Please use "opp_" prefix in the
 * variable name. And remember to OPPUNREF()
 * that object.
 */

#include "sync/config.h"

#ifdef SYNC_HAS_ATOMIC_OPERATION
#define OPP_VOLATILE_VAR volatile
#else
#define OPP_VOLATILE_VAR
#endif

typedef SYNC_UWORD32_T opp_hash_t;
#define OPP_OBJECT_EXT_TINY() opp_hash_t hash;OPP_VOLATILE_VAR SYNC_UWORD16_T flag,token;
#define OPP_RBTREE

#ifdef OPP_RBTREE
#include "opp/opp_rbtree_internal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum {
	OPPN_ALL = 1<<15,
	OPPN_INTERNAL_1 = 1<<14,
	OPPN_INTERNAL_2 = 1<<13,
	OPPN_ZOMBIE = 1<<12,
};

enum {
	OPPF_HAS_LOCK = 1,
	OPPF_SWEEP_ON_UNREF = 1<<1,
	OPPF_EXTENDED = 1<<2,
	OPPF_SEARCHABLE = 1<<3,
	OPPF_FAST_INITIALIZE = 1<<4,
};

enum {
	OPPN_ACTION_INITIALIZE = 512,
	OPPN_ACTION_FINALIZE,
	OPPN_ACTION_REUSE,
	OPPN_ACTION_DEEP_COPY,
	OPPN_ACTION_SHRINK,
};

struct opp_pool;
//#define OPP_HAS_HIJACK // use this if you need this
//#define OPP_CAN_TEST_FLAG
#ifdef TEST_OBJ_FACTORY_UTILS
#define OPP_HAS_HIJACK
#endif
#ifndef SYNC_HAS_NO_THREAD
#define OPP_BUFFER_HAS_LOCK
#endif
//#define OPP_HAS_RECYCLING // do not use this
struct opp_factory {
	SYNC_UWORD16_T sign;
	SYNC_UWORD16_T pool_size;
	SYNC_UWORD16_T pool_count;
	OPP_VOLATILE_VAR SYNC_UWORD16_T use_count;
	OPP_VOLATILE_VAR SYNC_UWORD16_T slot_use_count;
	SYNC_UWORD16_T token_offset;
	SYNC_UWORD16_T obj_size;
	SYNC_UWORD16_T bitstring_size;
	SYNC_UWORD32_T memory_chunk_size;
	SYNC_UWORD8_T property;
#ifdef OPP_BUFFER_HAS_LOCK
	sync_mutex_t lock;
#endif
//	int (*initialize)(void*data, const void*init_data, unsigned short size);
//	int (*finalize)(void*data);
	int (*callback)(void*data, int callback, void*cb_data, va_list ap);
	struct opp_pool*pools;
	opp_lookup_table_t tree;
};

struct opp_object_ext_tiny {
	OPP_OBJECT_EXT_TINY();
};

#define OPP_FACTORY_USE_COUNT(q) ({(q)->use_count;})

#define OPP_INIT(x) \
static int opp_##x##_init(void*data, const void*init_data, unsigned short size)

#define OPP_INIT_FUNC(x) opp_##x##_init

#define OPP_FNLZ(x) \
static int opp_##x##_fnlz(void*data)

#define OPP_FNLZ_FUNC(x) opp_##x##_fnlz

#define OPP_CB(x) \
static int opp_##x##_callback(void*data, int callback, void*cb_data, va_list ap)

#define OPP_CB_FUNC(x) opp_##x##_callback

#define OPP_FACTORY_CREATE(obuff, x, y, z) ({opp_factory_create_full(obuff, x, y, 1, OPPF_HAS_LOCK | OPPF_SWEEP_ON_UNREF, z);})
int opp_factory_create_full(struct opp_factory*obuff
		, int inc
		, SYNC_UWORD16_T obj_size
		, int token_offset
		, unsigned char property
//		, int(*initialize)(void*data, const void*init_data, unsigned short size)
//		, int(*finalize)(void*data)
		, int (*callback)(void*data, int callback, void*cb_data, va_list ap)
	);
void opp_factory_gc_donot_use(struct opp_factory*obuff);
void opp_factory_lock_donot_use(struct opp_factory*obuff);
void opp_factory_unlock_donot_use(struct opp_factory*obuff);
void opp_factory_destroy(struct opp_factory*obuff);
struct opp_pool*opp_factory_create_pool_donot_use(struct opp_factory*obuff, struct opp_pool*addpoint, void*nofreememory);

#if 0 // useful to check memory corruption
#define OPP_FACTORY_CHECK(x) ({opp_factory_do_full(x, NULL, NULL, OBJ_ITEM_FLAG_ALL, 0, 0);})
#else
#define OPP_FACTORY_CHECK(x)
#endif
void opp_factory_verb(struct opp_factory*obuff, int (*verb_obj)(const void*data, const void*func_data), const void*func_data, void (*log)(void*log_data, const char*fmt, ...), void*log_data);

// obj api
#define OPP_ALLOC1(x) ({opp_alloc4(x, 0, 0, NULL);})
#define OPP_ALLOC2(x, y) ({opp_alloc4(x, 0, 0, y);})
void*opp_alloc4(struct opp_factory*obuff, SYNC_UWORD16_T size, int doubleref, const void*init_data);
void opp_shrink(void*data, int size);
void opp_set_hash(void*data, opp_hash_t hash);
void opp_set_flag(void*data, unsigned int flag);
void opp_unset_flag(void*data, unsigned int flag);
#ifdef OPP_CAN_TEST_FLAG
int opp_test_flag(const void*data, unsigned int flag);
#endif
#define OPPREF(x) ({opp_ref(x, __FILE__, __LINE__);})
void*opp_ref(void*data, const char*filename, int lineno);
#define OPP_ASSERT_REF_COUNT(x,rc) ({opp_assert_ref_count(x, rc, __FILE__, __LINE__);})
int opp_assert_ref_count(void*data, int refcount, const char*filename, int lineno);
#define OPPUNREF2(x) ({opp_unref((void**)(x), __FILE__, __LINE__);})
#define OPPUNREF(x) opp_unref((void**)&(x), __FILE__, __LINE__)
void opp_unref(void**data, const char*filename, int lineno);
//#ifdef OPP_BUFFER_HAS_LOCK
#define OPPUNREF_UNLOCKED(x) ({opp_unref_unlocked((void**)&(x), __FILE__, __LINE__);})
void opp_unref_unlocked(void**data, const char*filename, int lineno);
//#endif
#ifdef OPP_HAS_HIJACK
#define OPP_FACTORY_HIJACK(x,y) ({opp_hijack((void**)&x, y, __FILE__, __LINE__);})
int opp_hijack(void**src, void*dest, const char*filename, int lineno);
#endif
// token api
void*opp_get(struct opp_factory*obuff, int token);
void opp_unset_flag_by_token(struct opp_factory*obuff, int token, unsigned int flag);
void opp_set_flag_by_token(struct opp_factory*obuff, int token, unsigned int flag);

int opp_count_donot_use(const struct opp_factory*obuff);
int opp_exists(struct opp_factory*obuff, const void*data);
int opp_callback(void*data, int callback, void*cb_data);
int opp_callback2(void*data, int callback, void*cb_data, ...);

#ifdef TEST_OBJ_FACTORY_UTILS
int opp_utils_test(void (*log)(void *log_data, const char*fmt, ...), void*log_data);
int opp_utils_multithreaded_test();
int opp_dump(const void*data, void (*log)(void *log_data, const char*fmt, ...), void*log_data);
#endif

#define EXTOBJ_TEST_FLAG(o,f) ((o)->_ext.flag & f)

#define OPP_FACTORY_DUMP_HEADER_FMT() "%-10.10s %-10.10s %-10.10s %-10.10s %-10.10s %-10.10s %-10.10s"
#define OPP_FACTORY_DUMP_HEADER_ARG() "pools","allocated","used","objects","slots","bitstring size","pool size"
#define OPP_FACTORY_DUMP_FMT() "%10d %10d %10d %10d %10d %10d %10d"
#define OPP_FACTORY_DUMP_ARG(x) (x)->pool_count, (int)((x)->pool_count*(x)->memory_chunk_size), (int)((x)->slot_use_count*(x)->obj_size) \
	, (x)->use_count , (x)->slot_use_count , (int)(x)->bitstring_size , (int)(x)->pool_size

#ifdef __cplusplus
}
#endif


#endif // OPP_FACTORY_UTILS_H
