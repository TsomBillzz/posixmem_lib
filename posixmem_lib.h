#ifndef POSIXMEM_LIB_H
#define POSIXMEM_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>  /* for file access modes (O_* flags) */
#include <sys/stat.h>  /* for symbolic constants for `shm_open`'s `mode` */
#include <sys/mman.h>

/* TODO(McCoyChisom): add explicit `typedef`s for `real32`, `real64`, `int64`, and `uint64` */
/* TODO(McCoyChisom): move these common `typedef`s to their own library with other common code */
typedef signed char	int8;
typedef unsigned char	uint8;
typedef signed short	int16;
typedef unsigned short	uint16;
typedef signed int	int32;
typedef unsigned int	uint32;

/* TODO(McCoyChisom): check all bool cases ("stdbool.h" availability, C++, etc.) */
#if !defined(bool)
	typedef enum {
		false = 0,
		true = !false
	} bool;
#endif

/* ---------- Handle ---------- */
typedef enum {
	p_HANDLE_TYPE_UNASSIGNED = 0,
	p_HANDLE_TYPE_POSIX_SHARED_MEMORY
} posixmem_libHandleType;

typedef struct {
	posixmem_libHandleType type;
	const char *name;
	off_t size;

	/* POSIX shared memory */
	bool readonly;
	bool unlink;

	void *data;
} posixmem_libHandle;

/* ---------- POSIX Shared Memory ---------- */
typedef struct {
	const char *name;
	off_t		size;
	bool		readonly;
	bool		create;
	bool		unlink;
	/* unimplemented:
	mode_t		user_mode;
	mode_t		group_mode;
	mode_t		others_mode;
	*/
} posixmem_libSharedMemoryConfig;

/* management functions */
posixmem_libHandle *posixmem_lib_shared_memory_initialize(const char *name, off_t size, bool readonly, bool create, bool unlink);
/*---posixmem_lib *posixmem_lib_shared_memory_initialize_from_config(posixmem_libSharedMemoryConfig *config);------------*/
posixmem_libHandle *posixmem_lib_shared_memory_initialize_from_config(posixmem_libSharedMemoryConfig *config);


/* usage/utility functions */
void *posixmem_lib_shared_memory_get(posixmem_libHandle* handle);
void  posixmem_lib_shared_memory_set(posixmem_libHandle* handle, void *data);

/* ---------- Core Functionalities ---------- */
void posixmem_lib_finalize(posixmem_libHandle* handle); 


#endif
