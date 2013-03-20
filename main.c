#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "factorisation.c"

//---------------------------------------------------------------
//			 		Main
//---------------------------------------------------------------

main(int argc, char* argv[])
{
	int methode = 0;
	char * filePath = "gen.txt";

	//WARNING: le fichier doit se finir par un retour à la ligne, soit une ligne vide !!

	//Quel methode ?	
	if (argc > 1) methode=atoi(argv[1]);

	//Création de la version protégé du fichier
	protected_file pfile;
	pfile.path = filePath;
	pfile.mutex = NULL; //Pour la methode 0, pas besoin de mutex

	//Tableau de test
	//int val[4] = {27166, 1804289, 168150, 8469308};

	//Sans thread
	if (methode == 0)
	{
		display_simple( &pfile );
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
}
