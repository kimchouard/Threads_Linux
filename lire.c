#include <stdio.h>
#include <stdint.h>


static long seek_curr;

int lire_nombre ( uint64_t *nombre )
{
   	FILE * file;
   	
  	file = fopen ( "gen.txt" , "r" );
   
   	fseek ( file, 0, seek_curr); 	// seek to the current number of the file
   	
	char number [100];
	char buf;
   	int i = 0;
   	
  	if (pFile == NULL) 
  	{
  		perror ("Error opening file");
  	}
   	else
   	{
    	while ( ! feof ( pFile ) )
     	{
       		while ( fgets ( buf , 1 , pFile ) != NULL && buf != '\n' ) 
       		{
       			number[i++] += buf;	
       		}
       		nombre = _atoi64 ( number );
     	}
   }
   return 0;
}

