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


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void array_init ( )
{
	array = ( table * ) malloc ( sizeof ( table ) );
    
	array->size = PAGE_SIZE;
	array->at = ( uint64_t * ) malloc (  sizeof ( uint64_t ) * array->size );
	array->last = -1;
}

void array_insert ( uint64_t prime_factor )
{
	pthread_mutex_lock ( &mutex );
	if ( array->last == array->size - 1 )
	{
		array->size += PAGE_SIZE;
		array->at = ( uint64_t * ) realloc ( array->at, array->size * sizeof ( uint64_t ) );
	}
	array->at[++(array->last)] = prime_factor;
	pthread_mutex_unlock ( &mutex );
}

uint64_t array_at ( int i )
{
	pthread_mutex_lock ( &mutex );
	uint64_t res;
	if ( i > array->last || i < 0 )
	{
		res = 0;
	}
	else
	{
		res = array->at[i];
	}
	pthread_mutex_unlock ( &mutex );
	return res;
}

int array_is_in ( uint64_t nombre )
{
	pthread_mutex_lock ( &mutex );
	int i;
    int succes = 0;
	for ( i = 0 ; i <= array->last ; i++ )
	{
		if ( nombre == array->at[i] )
		{
			succes = 1;
		}
	}
	pthread_mutex_unlock ( &mutex );
	return succes;
}

void array_destroy ( )
{
	free ( array->at );
	free ( array );
	pthread_mutex_destroy ( &mutex );
}

#endif