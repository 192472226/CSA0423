/*
 * mem_strategies.c
 *
 * Demonstrates various memory allocation strategies in C.
 * Dev-C++ (MinGW) friendly.
 *
 * Compile:
 *   gcc -o mem_strategies.exe mem_strategies.c
 *
 * Run:
 *   mem_strategies.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ========== 1) Static allocation (global) ========== */
#define STATIC_BUF_SIZE 64
static char g_static_buffer[STATIC_BUF_SIZE]; /* lives for program lifetime */

/* ========== 2) Stack allocation (local array) ========== */
void demo_stack_allocation(void) {
    char stack_buf[64]; /* allocated on the function's stack frame */
    memset(stack_buf, 0, sizeof(stack_buf));
    snprintf(stack_buf, sizeof(stack_buf), "Stack buffer demo: size = %zu", sizeof(stack_buf));
    printf("%s\n", stack_buf);
}

/* ========== 3) malloc / free demo ========== */
void demo_malloc_free(void) {
    size_t n = 5;
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    for (size_t i = 0; i < n; ++i) arr[i] = (int)(i + 1);
    printf("malloc: allocated %zu ints ->", n);
    for (size_t i = 0; i < n; ++i) printf(" %d", arr[i]);
    printf("\n");
    free(arr);
    printf("malloc: freed memory\n");
}

/* ========== 4) calloc demo (zero initialized) ========== */
void demo_calloc(void) {
    size_t n = 6;
    int *arr = (int *)calloc(n, sizeof(int));
    if (!arr) {
        fprintf(stderr, "calloc failed\n");
        return;
    }
    printf("calloc: allocated %zu ints (should be zero-initialized):", n);
    for (size_t i = 0; i < n; ++i) printf(" %d", arr[i]);
    printf("\n");
    free(arr);
}

/* ========== 5) realloc demo ========== */
void demo_realloc(void) {
    size_t n = 3;
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    for (size_t i = 0; i < n; ++i) arr[i] = (int)(i + 1);

    printf("realloc: before resize:");
    for (size_t i = 0; i < n; ++i) printf(" %d", arr[i]);
    printf("\n");

    /* Grow */
    size_t new_n = 7;
    int *tmp = (int *)realloc(arr, new_n * sizeof(int));
    if (!tmp) {
        fprintf(stderr, "realloc failed (grow)\n");
        free(arr);
        return;
    }
    arr = tmp;
    /* Initialize new region */
    for (size_t i = n; i < new_n; ++i) arr[i] = (int)(i + 1);

    printf("realloc: after grow to %zu:", new_n);
    for (size_t i = 0; i < new_n; ++i) printf(" %d", arr[i]);
    printf("\n");

    /* Shrink */
    size_t shrink_n = 4;
    tmp = (int *)realloc(arr, shrink_n * sizeof(int));
    if (!tmp) {
        fprintf(stderr, "realloc failed (shrink)\n");
        free(arr);
        return;
    }
    arr = tmp;

    printf("realloc: after shrink to %zu:", shrink_n);
    for (size_t i = 0; i < shrink_n; ++i) printf(" %d", arr[i]);
    printf("\n");

    free(arr);
}

/* ========== 6) Bump (arena) allocator ========== */
/* Simple linear allocator: fast allocations, free only by resetting the arena. */
typedef struct {
    uint8_t *buffer;
    size_t size;
    size_t offset;
} BumpArena;

int bump_init(BumpArena *arena, size_t size) {
    if (!arena) return 0;
    arena->buffer = (uint8_t *)malloc(size);
    if (!arena->buffer) return 0;
    arena->size = size;
    arena->offset = 0;
    return 1;
}

void bump_destroy(BumpArena *arena) {
    if (!arena) return;
    free(arena->buffer);
    arena->buffer = NULL;
    arena->size = 0;
    arena->offset = 0;
}

/* Align to 8 bytes for better alignment */
static size_t align8(size_t x) {
    const size_t a = 8;
    return (x + (a - 1)) & ~(a - 1);
}

void *bump_alloc(BumpArena *arena, size_t n) {
    if (!arena || !arena->buffer) return NULL;
    size_t aligned = align8(n);
    if (arena->offset + aligned > arena->size) return NULL;
    void *p = arena->buffer + arena->offset;
    arena->offset += aligned;
    return p;
}

void bump_reset(BumpArena *arena) {
    if (!arena) return;
    arena->offset = 0;
}

void demo_bump_arena(void) {
    BumpArena arena;
    size_t arena_size = 256;
    if (!bump_init(&arena, arena_size)) {
        fprintf(stderr, "Failed to initialize bump arena\n");
        return;
    }
    printf("Bump arena: size=%zu\n", arena_size);

    char *a = (char *)bump_alloc(&arena, 20);
    char *b = (char *)bump_alloc(&arena, 40);
    if (a) snprintf(a, 20, "arena-A: %s", "hello");
    if (b) snprintf(b, 40, "arena-B: %s", "world-from-arena");
    printf("Bump arena allocated: \"%s\", \"%s\"\n", a ? a : "(NULL)", b ? b : "(NULL)");

    printf("Bump arena offset before reset: %zu\n", arena.offset);
    bump_reset(&arena);
    printf("Bump arena offset after reset: %zu\n", arena.offset);

    /* After reset, allocations reuse space */
    char *c = (char *)bump_alloc(&arena, 30);
    if (c) snprintf(c, 30, "arena-C reuse");
    printf("Bump arena allocated after reset: \"%s\"\n", c ? c : "(NULL)");

    bump_destroy(&arena);
}

/* ========== 7) Simple fixed-size block memory pool ========== */
/*
 * This pool allocates a single large block and subdivides it into equal-sized
 * chunks. Freed chunks are pushed onto a free-list; allocation pops from it.
 * This is suitable for many small objects of identical size.
 */

typedef struct PoolBlock {
    struct PoolBlock *next;
} PoolBlock;

typedef struct {
    uintptr_t base_addr;
    size_t block_size;
    size_t block_count;
    PoolBlock *free_list;
    void *raw_mem; /* pointer to the raw allocated memory for cleanup */
} FixedPool;

int pool_init(FixedPool *pool, size_t block_size, size_t block_count) {
    if (!pool || block_size < sizeof(PoolBlock) || block_count == 0) return 0;
    size_t total = block_size * block_count;
    void *mem = malloc(total);
    if (!mem) return 0;
    pool->raw_mem = mem;
    pool->base_addr = (uintptr_t)mem;
    pool->block_size = block_size;
    pool->block_count = block_count;
    pool->free_list = NULL;

    /* build free list */
    for (size_t i = 0; i < block_count; ++i) {
        uintptr_t addr = pool->base_addr + i * block_size;
        PoolBlock *blk = (PoolBlock *)addr;
        blk->next = pool->free_list;
        pool->free_list = blk;
    }
    return 1;
}

void pool_destroy(FixedPool *pool) {
    if (!pool) return;
    free(pool->raw_mem);
    pool->raw_mem = NULL;
    pool->free_list = NULL;
    pool->base_addr = 0;
    pool->block_size = 0;
    pool->block_count = 0;
}

void *pool_alloc(FixedPool *pool) {
    if (!pool || pool->free_list == NULL) return NULL;
    PoolBlock *blk = pool->free_list;
    pool->free_list = blk->next;
    return (void *)blk;
}

void pool_free(FixedPool *pool, void *ptr) {
    if (!pool || !ptr) return;
    PoolBlock *blk = (PoolBlock *)ptr;
    blk->next = pool->free_list;
    pool->free_list = blk;
}

void demo_fixed_pool(void) {
    FixedPool pool;
    size_t block_size = 32;
    size_t block_count = 8;

    if (!pool_init(&pool, block_size, block_count)) {
        fprintf(stderr, "Failed to init pool\n");
        return;
    }

    printf("Fixed pool: block_size=%zu block_count=%zu\n", block_size, block_count);

    void *objs[10];
    for (size_t i = 0; i < block_count; ++i) {
        objs[i] = pool_alloc(&pool);
        printf("pool_alloc -> %p\n", objs[i]);
        if (objs[i]) {
            /* write a string into the block to show it's usable */
            snprintf((char *)objs[i], block_size, "obj-%zu", i);
        }
    }

    /* attempt to allocate beyond capacity -> should return NULL */
    objs[block_count] = pool_alloc(&pool);
    printf("pool_alloc beyond capacity -> %p (expected NULL)\n", objs[block_count]);

    /* free a couple and allocate again */
    pool_free(&pool, objs[1]);
    pool_free(&pool, objs[3]);
    printf("Freed objs[1]=%p and objs[3]=%p\n", objs[1], objs[3]);

    void *x = pool_alloc(&pool);
    void *y = pool_alloc(&pool);
    printf("After free, allocations -> %p, %p (should reuse freed blocks)\n", x, y);

    /* Print content of first few (if present) */
    for (size_t i = 0; i < 4; ++i) {
        if (objs[i]) printf("objs[%zu] content: \"%s\"\n", i, (char *)objs[i]);
    }

    pool_destroy(&pool);
}

/* ========== Helper: print header ========== */
void print_header(const char *title) {
    printf("\n------------------------\n");
    printf(" %s\n", title);
    printf("------------------------\n");
}

/* ========== Main: run demos ========== */
int main(void) {
    /* Static global buffer demo */
    print_header("Static allocation (global buffer)");
    snprintf(g_static_buffer, STATIC_BUF_SIZE, "Global static buffer demo. size=%d", STATIC_BUF_SIZE);
    printf("%s\n", g_static_buffer);

    /* Stack allocation demo */
    print_header("Stack allocation (local buffer)");
    demo_stack_allocation();

    /* malloc/free */
    print_header("Dynamic allocation with malloc/free");
    demo_malloc_free();

    /* calloc */
    print_header("Zero-initialized allocation with calloc");
    demo_calloc();

    /* realloc */
    print_header("Resizing allocated memory with realloc");
    demo_realloc();

    /* bump arena */
    print_header("Bump (arena) allocator");
    demo_bump_arena();

    /* fixed-size pool */
    print_header("Fixed-size memory pool (free-list)");
    demo_fixed_pool();

    print_header("All demos finished");
    return 0;
}

