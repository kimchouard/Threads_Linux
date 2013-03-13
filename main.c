#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define MAX_FACTORS 64

#include "lire.c"
#include "factorisation_screen.c"
#include "factorisation_file.c"

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
	int val[4] = {27166, 1804289, 168150, 8469308};

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
		dual_thread_optimise( val, 4 );
	}

	//print_prime_factors(29872);
}
