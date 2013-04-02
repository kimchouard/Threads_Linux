#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "io.h"
#include "array.h"

#define MAX_FACTORS 64


//Renvoie 1 si premier, 0 sinon.
int is_prime_saved ( uint64_t p )
{
    if ( array_is_in ( p ) )
     {
         return 1;
     }
     else if ( p < 2 )
     {
        return 1;
     }
     else
     {
         int i;
         
         for ( i = 2 ; i < p ; i++ )
         {
             //Si il est divisible par le nombre en cours.
             if ( p % i == 0 )
             {
                 //Il n'est pas premier
                 return 0;
             }
         }
         array_insert ( p );
         return 1;
     }
}


//Question 8 : Mémorisation des résultats intermediaires
//Attention : La fonction is_prime_saved permet de sauver les nombres premiers
// Ce n'est donc pas la fonction get_prime_factors
int get_prime_factors ( uint64_t n, uint64_t *factors_tab )
{
	int index_factors = 0;
	uint64_t tester = 2;
	int i = 0;
    
	uint64_t reste = n;
    
	//Question 9 : utilisation des résultats intermediaires
	while ( ( tester = array_at ( i ) ) != 0 )
	{
		//Tant qu'il est divisible par le premier
		while ( reste % tester == 0 )
		{
			//On stocke le resultat de la division dans reste
			reste = reste / tester;
			//On sauvegarde le nombre
			factors_tab[index_factors++] = tester;
		}
        i++;
        
        if ( array_is_in ( reste ) )
        {
            factors_tab[index_factors++] = reste;
            return index_factors;
        }
	}
	if ( index_factors >  0 )
	{
		tester = factors_tab[index_factors - 1];
	}
	else
	{
		tester = 2;
	}
	//On parcours tous les nombres jusqu'à ce que le reste soit premier.
	while ( ! is_prime_saved ( reste ) )
	{
		//Si c'est un nombre premier
		if ( is_prime_saved ( tester ) )
		{
			//Tant qu'il est divisible par le premier
			while ( reste % tester == 0 )
			{
				//On stocke le resultat de la division dans reste
				reste = reste / tester;
				//On sauvegarde le nombre
				factors_tab[index_factors++] =  tester;
			}
		}
		tester++;
	}
	factors_tab[index_factors++] = reste;
    return index_factors;
    
}


void print_prime_factors_q8 ( uint64_t n )
{
	uint64_t factors[64];
	int j, k;
	
	k = get_prime_factors ( n, factors );
	
	print_safe ( n, factors, k );
}


//---------------------------------------------------------------
//	Question 9 : one thread
//---------------------------------------------------------------
void * one_thread_q9 ( )
{
	uint64_t number;
	while( ( number = read_number_safe ( ) ) )
	{
		print_prime_factors_q8 ( number );
	}
    return 0;
}

void dual_thread_optimise_q9 ( )
{
	array_init ( );
    
	pthread_t t1;
	pthread_create( &t1, NULL, &one_thread_q9, NULL );
	//pthread_create( &t2, NULL, &one_thread_q9, NULL );
	one_thread_q9 ( );
    
	//Liaison avec le main
	pthread_exit ( &t1 );
	//pthread_join ( t2, NULL );
	
	array_destroy ( );
	//Quite les threads
	//pthread_exit ( &t1 );
}

