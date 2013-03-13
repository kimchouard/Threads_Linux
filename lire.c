#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static int seek_cur = 0;

int lire_nombre ( uint64_t *nombre, int reset = 0 )
{
   	FILE * file;
   	
  	file = fopen ( "gen.txt" , "r" );
   	
   	if ( reset ) 
   	{
   		seek_cur ( 0 );	
   	}
   
   	fseek ( file, seek_cur, SEEK_SET ); 	// seek to the current number of the file
   	
	char number [100];
	char buf;
   	int i = 0;
   	
  	if ( file == NULL ) 
  	{
  		perror ("Error opening file");
  	}
   	else
   	{
    	while ( ! feof ( file ) )
     	{
       		fscanf ( file, "%llu", nombre );
       		seek_cur = ftell ( file );
       		return 1;
     	}
   }
   return 0;
}

