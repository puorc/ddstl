#include "min_allocator.h"

size_t malloc_allocator_base::outstanding_bytes = 0;
size_t malloc_allocator_base::alloc_count = 0;
size_t malloc_allocator_base::dealloc_count = 0;
bool malloc_allocator_base::disable_default_constructor = false;