#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int is_prime( uint64_t p )
{
	int i;

	for ( i = 2; i < p; i++)
	{
		//Si il est divisible par le nombre en cours.
		if (p%i == 0)
		{
			return 0;
		}
	}

	return 1;
}

void print_prime_factors( uint64_t n )
{
	int i = 2;
	int reste = n;
	
	//On parcours tous les nombres necéssaire.
	while ( i < reste )
	{
		//Si c'est un nombre premier
		if ( is_prime( i ) )
		{
			//Tant qu'il est divisible par le premier
			while ( reste%i == 0 )
			{
				//On stocke le resultat de la division dans reste
				reste = reste/i;

				//On affiche le nombre
				printf("%i ", i);
			}
		}

		i++;
	}

	printf("%i \n", i);	
}

main()
{
	print_prime_factors( 84 );
}