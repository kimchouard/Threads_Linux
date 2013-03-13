#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "lire.c"

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
	
	printf("%i : ", reste);
	
	//On parcours tous les nombres necéssaire.
	while ( !is_prime(reste) )
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
	/* /Tableau de test
	int val[6] = {12923, 29872, 12923, 18152, 11953, 12923};

	pthread_t t[6];

	int i;
	for ( i = 0 ; i < 6 ; i+=2 )
	{
		//Création du thread
		int pid_thread = pthread_create( &t[i], NULL, print_prime_factors, ( void * ) val[i] );
		int pid_thread2 = pthread_create( &t[i+1], NULL, print_prime_factors, ( void * ) val[i+1] );
		printf( "Je crée le thread : %d\n", i );

		//Liaison avec le main
		pthread_join ( t[i], NULL  );
		pthread_join ( t[i+1], NULL  );
	}

	for ( i = 0 ; i < 5 ; i++ )
	{
		//Quite les threads
		pthread_exit ( &t[i] );
	}*/

	print_prime_factors(12923);
	//print_prime_factors( 84 );
}