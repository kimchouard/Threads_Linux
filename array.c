#include "array.h"


void array_init ( )
{
	if ( pthread_mutex_init( &mutex, NULL ) != 0 )
    {
        printf("\nError while initializing the mutex\n");
        exit ( 0 );
    }
	array = ( table * ) malloc ( sizeof ( table ) );
    
	array->size = PAGE_SIZE;
	array->at = ( uint64_t * ) malloc (  sizeof ( uint64_t ) * array->size );
	array->at[0] = 2;
	array->last = 0;
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
