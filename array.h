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


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void prime_factors_init ( )
{
	array = ( table * ) malloc ( sizeof ( table ) );
    
	array->size = PAGE_SIZE;
	array->at = ( uint64_t * ) malloc (  sizeof ( uint64_t ) * array->size );
	array->last = -1;
    
	//Création du mutex
	/*if ( pthread_mutex_init ( &mutex, NULL ) != 0 )
	{
		printf ( "\nError while initializing the mutex\n" );
		exit ( 0 );
	}*/
}

void prime_factors_insert ( uint64_t prime_factor )
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

uint64_t prime_factors_at ( int i )
{
	if ( i > array->last || i < 0 )
	{
		return 0;
	}
	else
	{
		pthread_mutex_lock ( &mutex );
		return array->at[i];
		pthread_mutex_unlock ( &mutex );
	}
}

int prime_factors_is_in ( uint64_t nombre )
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

void prime_factors_destroy ( )
{
	free ( array->at );
	free ( array );
	pthread_mutex_destroy ( &mutex );
}

#endif