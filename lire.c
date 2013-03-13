#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


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

