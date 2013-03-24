#include "array.h"
#include <stdint.h>
#include <stdio.h>

#include <pthread.h>

#define MAX_FACTORS 64


//Renvoie 1 si premier, 0 sinon.
int is_prime_saved( uint64_t p )
{
	if ( p <= 2 )
	{
		prime_factors_insert ( p );
		return 1;
	}
	else if ( prime_factors_is_in( p ) )
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
		prime_factors_insert ( p );
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
	while ( i <= array->last )
	{
		//Tant qu'il est divisible par le premier
		while ( reste % array->at[i] == 0 )
		{
			//On stocke le resultat de la division dans reste
			reste = reste / array->at[i];
			//On sauvegarde le nombre
			factors_tab[index_factors++] = array->at[i];
		}
		tester = array->at[i];
        i++;
        
        if ( prime_factors_is_in( reste ) )
        {
            factors_tab[index_factors++] = reste;
            return index_factors;   
        }
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
				reste = reste / ( uint64_t ) tester;
				//On sauvegarde le nombre
				factors_tab[index_factors++] =  tester;
			}
		}
        
		tester++;
	}
	factors_tab[index_factors++] = reste;
    return index_factors;

}


void print_prime_factor_q8 ( uint64_t n )
{
	uint64_t factors[64];
	int j, k;
	
	k = get_prime_factors ( n, factors );
	
	printf ( "%llu : ", n );
	for ( j = 0 ; j < k ; j ++ )
	{
		printf ( "%llu ", factors[j] );	
	}
	printf ( "\n" );
}