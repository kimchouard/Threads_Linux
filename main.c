#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//#include "lire.c"

int is_prime( uint64_t p )
{
	if (p <= 2)
	{
		return 1;
	}
	else
	{
		int i;

		for ( i = 2; i < p; i++)
		{
			//Si il est divisible par le nombre en cours.
			if (p%i == 0)
			{
				//Il n'est pas premier
				return 0;
			}
		}

		return 1;
	}
}

void print_prime_factors( uint64_t n )
{
	int i = 2;
	int reste = n;
	
	printf("%i : ", reste);
	
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

				//On affiche le nombre
				printf("%i ", i);
			}
		}

		i++;
	}

	printf("%i \n", reste);	
}

void dual_thread(int val[], int nb_valeurs)
{
	pthread_t t[nb_valeurs];

	int i;
	for ( i = 0 ; i < nb_valeurs ; i+=2 )
	{
		//Création du thread
		int pid_thread = pthread_create( &t[i], NULL, print_prime_factors, ( void * ) val[i] );
		int pid_thread2 = pthread_create( &t[i+1], NULL, print_prime_factors, ( void * ) val[i+1] );

		//Liaison avec le main
		pthread_join ( t[i], NULL  );
		pthread_join ( t[i+1], NULL  );
	}

	for ( i = 0 ; i < nb_valeurs ; i++ )
	{
		//Quite les threads
		pthread_exit ( &t[i] );
	}
}

void dual_thread_optimise(int val[], int nb_valeurs)
{
	pthread_t t[nb_valeurs];

	int i;
	for ( i = 0 ; i < nb_valeurs ; i+=2 )
	{
		//Création du thread
		int pid_thread = pthread_create( &t[i], NULL, print_prime_factors, ( void * ) val[i] );
		int pid_thread2 = pthread_create( &t[i+1], NULL, print_prime_factors, ( void * ) val[i+1] );

		//Liaison avec le main
		pthread_join ( t[i], NULL  );
		pthread_join ( t[i+1], NULL  );
	}

	for ( i = 0 ; i < nb_valeurs ; i++ )
	{
		//Quite les threads
		pthread_exit ( &t[i] );
	}
}

main(int argc, char* argv[])
{
	int methode = 0;

	//Quel methode ?	
	if (argc > 1) methode=atoi(argv[1]);

	//Tableau de test
	int val[4] = {27166, 1804289, 168150, 8469308};

	//Sans thread
	if (methode == 0)
	{
		int j;
		for ( j = 0 ; j < 4 ; j++ )
		{
			print_prime_factors(val[j]);
		}
	}
	//Avec thread simple
	else if (methode == 1)
	{
		dual_thread(val, 4);
	}
	//Avec
	else if (methode == 2)
	{
		dual_thread_optimise(val, 4);
	}

	//print_prime_factors(29872);
}
