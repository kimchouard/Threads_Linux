#ifndef ARRAY_H
#define ARRAY_H


#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define PAGE_SIZE 1000

static struct table {
	uint64_t * at;
	int size;
	int last;
    
} *array;

typedef struct table table;

static pthread_mutex_t mutex;


void array_init ( );
void array_destroy ( );

void array_insert ( uint64_t prime_factor );
uint64_t array_at ( int i );

int array_is_in ( uint64_t nombre );

#endif