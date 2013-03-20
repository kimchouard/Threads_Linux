#include <stdint.h>

#define MAX_FACTORS 64

//Question 8
int get_prime_factors ( uint64_t n, uint64_t *factors_tab )
{
	int index_factors = 0;
	int i = 2;
	int reste = n;
	
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

				//On sauvegarde le nombre
				factors_tab[index_factors++] =  reste;
			}
		}

		i++;
	}
	factors_tab[index_factors++] = reste;
	
	return index_factors;
}

void print_prime_factor_q8 ( uint64_t n )
{
	uint64_t factors[MAX_FACTORS];
	int j, k;
	
	k = get_prime_factors ( n, factors );
	
	printf ( "%llu : ", n );
	for ( j = 0 ; j < k ; j ++ )
	{
		printf ( "%llu ", factors[j] );	
	}
	printf ( "\n" );
}