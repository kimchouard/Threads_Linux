#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#define OUT

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
void * print_prime_factors( void * n )
{
	int i = 2;
	uint64_t reste = *((uint64_t *) n);

#ifdef OUT
	printf("%llu : ", reste);
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
				printf("%i ", i);
#endif
			}
		}

		i++;
	}

#ifdef OUT
	printf("%llu \n", reste);
#endif	
}

//---------------------------------------------------------------
//				Parcours simple sans threads
//---------------------------------------------------------------

//Structure utile pour lire dans un fichier en sécurité (merci les mutex !)
struct protected_file {
	char * path;
	pthread_mutex_t * mutex;
};
typedef struct protected_file protected_file;

//temp_file.mutex à NULL pour désactiver la protection par mutex
void * display_simple ( void * temp_file )
{
	int j;
	int file_end = 0;
	uint64_t *out = malloc(sizeof(uint64_t));

	//Précision du void *
	protected_file *pfile = (protected_file *) temp_file;

	while( file_end != 1 )
	{
		//Gère le cas ou on n'as pas besoin de mutex
		if (pfile->mutex != NULL) 
		{
			pthread_mutex_lock(pfile->mutex);
		}

		file_end = lire_nombre(out, pfile->path, 0);

		if ( file_end != 1 )
		{
			print_prime_factors( out );
		}

		if (pfile->mutex != NULL) 
		{
			pthread_mutex_unlock(pfile->mutex);
		}

	};

	free (out);
}

//---------------------------------------------------------------
//				Parcours avec 2 threads
//---------------------------------------------------------------

void dual_thread(char * aFilePath)
{
	pthread_t t[100];
	int fin1 = 0;
	int fin2 = 0;
	int fin_boucle = 0;
	//Pas besoin de malloc car même contexte
	uint64_t out1;
	uint64_t out2;
	int pid_thread, pid_thread2;

	int i;
	for ( i = 0 ; (fin_boucle != 1) && (i < 100) ; i+=2 )
	{
		//Récupération dans le fichier
		fin1 = lire_nombre(&out1, aFilePath, 0);
		fin2 = lire_nombre(&out2, aFilePath, 0);
		//printf("Boucle n°%i, fin du le fichier: {1: %i, 2: %i}\n", i/2, fin1, fin2);

		//Création du thread si le fichier n'est pas terminé
		(!fin1) ? (pid_thread = pthread_create( &t[i], NULL, &print_prime_factors, &out1 )) : (fin_boucle = 1);
		(!fin2) ? (pid_thread2 = pthread_create( &t[i+1], NULL, &print_prime_factors, &out2 )) : (fin_boucle = 1);

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

void dual_thread_optimise(char * afile_path)
{
	pthread_t t1, t2;

	//Création du fichier protégé
	protected_file *pfile = malloc(sizeof(protected_file));
	pfile->path = afile_path;
	pfile->mutex = malloc(sizeof(pthread_mutex_t));

	//Création du mutex
	if ( pthread_mutex_init(pfile->mutex, NULL) != 0 )
	{
		printf("\nErreur dans l'initialisation du mutex\n");
	}

	//Création du thread
	int pid_thread = pthread_create( &t1, NULL, &display_simple, pfile);
	int pid_thread2 = pthread_create( &t2, NULL, &display_simple, pfile);

	//Liaison avec le main
	pthread_join ( t1, NULL  );
	pthread_join ( t2, NULL  );

	//Quite les threads
	pthread_exit ( &t1 );
	pthread_exit ( &t2 );

	//Et on oublie pas de détruire le mutex et la structure :)
	pthread_mutex_destroy(pfile->mutex);
	free(pfile->mutex);
	free(pfile);
}