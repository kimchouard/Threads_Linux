

//---------------------------------------------------------------
//					Fonctions utiles
//---------------------------------------------------------------

//Renvoie 1 si entier, 0 sinon.
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

//Affiche la factoriasation en nombre premier
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

//---------------------------------------------------------------
//				Parcours simple sans threads
//---------------------------------------------------------------

void display_simple ( char * filePath )
{
	int j;
	uint64_t *out = malloc(sizeof(uint64_t));

	while( lire_nombre(out, filePath, 0) != 0 )
	{
		print_prime_factors( (int) *out );
	}
}

//---------------------------------------------------------------
//				Parcours avec 2 threads
//---------------------------------------------------------------

void dual_thread(char * filePath)
{
	pthread_t t[100];
	int fin1 = 1;
	int fin2 = 1;
	uint64_t *out1 = malloc(sizeof(uint64_t));
	uint64_t *out2 = malloc(sizeof(uint64_t));

	int i;
	for ( i = 0 ; ((fin1 != 0) || (fin2 != 0)) && (i < 100) ; i+=2 )
	{
		//Création du thread
		fin1 = lire_nombre(out1, filePath, 0);
		int pid_thread = pthread_create( &t[i], NULL, print_prime_factors, ( void * ) out1 );
		fin2 = lire_nombre(out2, filePath, 0);
		int pid_thread2 = pthread_create( &t[i+1], NULL, print_prime_factors, ( void * ) out2 );

		//Liaison avec le main
		pthread_join ( t[i], NULL  );
		pthread_join ( t[i+1], NULL  );
	}

	int j;
	for ( j = 0 ; j < i ; j++ )
	{
		//Quite les threads
		pthread_exit ( &t[j] );
	}
}

//---------------------------------------------------------------
//			 Parcours avec 2 threads optimisé
//---------------------------------------------------------------

void dual_thread_optimise(int val[], int nb_valeurs)
{
	pthread_t t1, t2;

	//Création du thread
	int pid_thread = pthread_create( &t1, NULL, display_simple, ( void * ) val, ( void * ) nb_valeurs, ( void * ) 1);
	int pid_thread2 = pthread_create( &t2, NULL, display_simple, ( void * ) val, ( void * ) nb_valeurs, ( void * ) 2);

	//Liaison avec le main
	pthread_join ( t1, NULL  );
	pthread_join ( t2, NULL  );

	//Quite les threads
	pthread_exit ( &t1 );
	pthread_exit ( &t2 );
}