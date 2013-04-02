#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "io.h"

#define OUT

//---------------------------------------------------------------
//	Fonctions utiles
//---------------------------------------------------------------

//Renvoie 1 si entier, 0 sinon.
int is_prime( uint64_t p )
{
	if ( p <= 2 )
	{
		return 1;
	}
	else
	{
		int i;

		for ( i = 2 ; i < p ; i++ )
		{
			//Si il est divisible par le nombre en cours.
			if ( p%i == 0 )
			{
				//Il n'est pas premier
				return 0;
			}
		}
		return 1;
	}
}

//Affiche la factoriasation en nombre premier
void * print_prime_factors ( void * n )
{
	int i = 2;
	uint64_t reste = *((uint64_t *) n);

#ifdef OUT
	//printf ( "%llu : ", reste );
	print_safe_number ( reste );
#endif
	
	//On parcours tous les nombres jusqu'à ce que le reste soit premier.
	while ( ! is_prime(reste) )
	{
		//Si c'est un nombre premier
		if ( is_prime( i ) )
		{
			//Tant qu'il est divisible par le premier
			while ( reste % i == 0 )
			{
				//On stocke le resultat de la division dans reste
				reste = reste/i;

#ifdef OUT
				//On affiche le nombre
				//printf("%i ", i);
				print_safe_factor ( i );

#endif
			}
		}

		i++;
	}

#ifdef OUT
	//printf("%llu \n", reste);
	print_safe_factor ( reste );
	print_safe_eol ( );
#endif	
}

//---------------------------------------------------------------
//	Question 3 : one thread
//---------------------------------------------------------------
void * one_thread ( )
{
	uint64_t number;
	while( ( number = read_number ( ) ) )
	{
		print_prime_factors( &number );

	}
}
//Version thread safe
void * one_thread_safe ( )
{
	uint64_t number;
	while( ( number = read_number_safe ( ) ) )
	{
		print_prime_factors( &number );

	}
}

//---------------------------------------------------------------
//	Question 4 : two threads
//---------------------------------------------------------------
void dual_thread ( )
{
	int stop = 0;
	uint64_t num1, num2;
	pthread_t t1, t2;
	while ( !stop )
	{
		num1 = read_number ( );
		num2 = read_number ( );
		if ( num1 )
		{
			pthread_create( &t1, NULL, &print_prime_factors, &num1 );
			if ( num2 )
			{
				pthread_create( &t2, NULL, &print_prime_factors, &num2 );
				//print_prime_factors ( &num2 );
			}
			else
			{
				stop = 1;
			}
			//Liaison avec le main
			pthread_join ( t1, NULL );
			pthread_join ( t2, NULL );
			//?????Quite les threads?????
			//pthread_exit ( &t1 );
		}
		else 
		{
			stop = 1;
		}
	}
}

//---------------------------------------------------------------
//	Parcours avec 2 threads optimisé
//---------------------------------------------------------------

void dual_thread_optimise ( )
{
	pthread_t t1;
	pthread_create( &t1, NULL, &one_thread_safe, NULL );
	one_thread_safe ( );

	//Liaison avec le main
	pthread_join ( t1, NULL );
	
	//Quite les threads
	//pthread_exit ( &t1 );
}