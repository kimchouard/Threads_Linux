#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//---------------------------------------------------------------
//			 		Lire dans le fichier
//---------------------------------------------------------------

static int seek_cur = 0;

int lire_nombre ( uint64_t *nombre, char * filePath, int reset )
{
 	FILE * file;
 	
	file = fopen ( filePath , "r" );
 	
 	if ( reset ) 
 	{
 		seek_cur = 0;	
 	}
 
 	fseek ( file, seek_cur, SEEK_SET ); 	// seek to the current number of the file
 	
  char number [100];
  char buf;
 	int i = 0;
 	
	if ( file == NULL ) 
	{
		perror ("Error opening file");
    return 0;
	}
 	else
 	{
 		fscanf ( file, "%llu", nombre );
 		seek_cur = ftell ( file );

    //Si on est à la fin du fichier
    if ( feof ( file ) )
    {
      return 0;
   	}
   }

   return 1;
}

//---------------------------------------------------------------
//			 		Main
//---------------------------------------------------------------

main(int argc, char* argv[])
{
	int methode = 0;
	char * filePath = "gen.txt";

	//Quel methode ?	
	if (argc > 1) methode=atoi(argv[1]);

	//Tableau de test
	//int val[4] = {27166, 1804289, 168150, 8469308};

	//Sans thread
	if (methode == 0)
	{
		display_simple( filePath );
	}
	//Avec thread simple
	else if (methode == 1)
	{
		dual_thread( filePath );
	}
	//Avec
	else if (methode == 2)
	{
		dual_thread_optimise( filePath );
	}

	//print_prime_factors(29872);
}
