#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

#include "posixmem_lib.h"


typedef struct {
	int id;
	long long time_ms;
} Test;

/* Get current time in milliseconds. */
long long get_time_ms(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}


int
main(void)
{
	posixmem_libHandle *shm;
	posixmem_libSharedMemoryConfig config = {
		.name = "/shm-test-1",
		.size = sizeof(Test),
		.readonly = false,
		.create = true,
		.unlink = false
	};
	shm = posixmem_lib_shared_memory_initialize_from_config(&config);
	
	Test data = {
		.id = 3,
		.time_ms = get_time_ms()
	};
	// Test *data = sincere_shared_memory_get(shm);
	//data->id += 2;

	posixmem_lib_shared_memory_set(shm, &data);

	posixmem_lib_finalize(shm);

	return 0;
}
