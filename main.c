#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



//---------------------------------------------------------------
//			 		Main
//---------------------------------------------------------------

main(int argc, char* argv[])
{
	int methode = 3;
	char * file_path;

	//WARNING: le fichier doit se finir par un retour à la ligne, soit une ligne vide !!

	//Quel methode ?	
	if ( argc > 2 )
	{
		file_path = argv[1];
		if ( !open_file ( file_path ) )
		{
			printf("The file cannot be found !");
			exit ( 0 );
		}
		methode = atoi ( argv[2] );
		init_print ( );
	} 
	else
	{
		printf("Wrong parameters !\nYou should first indicate the file where to find the numbers and then the computing methode.");
		exit ( 0 );
	}


	//Création de la version protégé du fichier
	//protected_file pfile;
	//pfile.path = filePath;
	//pfile.mutex = NULL; //Pour la methode 0, pas besoin de mutex

	//Tableau de test
	//int val[4] = {27166, 1804289, 168150, 8469308};

	//Sans thread
	if (methode == 0)
	{
		one_thread ( );
	}
	//Avec thread simple
	else if (methode == 1)
	{
		dual_thread (  );
	}
	//Avec
	else if (methode == 2)
	{
		dual_thread_optimise( );
	}
	else if ( methode == 3 )
	{
		dual_thread_optimise_q9 ( );
	}

	close_file ( );
	end_print ( );

	exit ( 0 );
}
