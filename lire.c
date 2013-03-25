#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

//static int seek_cur = 0;
static FILE *file;

pthread_mutex_t mutex;


int open_file ( char * filePath )
{
    file = fopen ( filePath , "r" );
    if ( file == NULL )
    {
        perror ("Error opening file");
        return 0;
    }
    //Création du mutex
    if ( pthread_mutex_init( &mutex, NULL) != 0 )
    {
        printf("\nError while initializing the mutex\n");
        exit ( 0 );
    }
    return 1;
}

void reset_file ( )
{
    fseek ( file, 0, SEEK_SET );
}

uint64_t read_number_safe (  )
{
    uint64_t number;
    pthread_mutex_lock ( &mutex );
    fscanf ( file, "%llu", &number );
    //Si on est à la fin du fichier
    if ( feof ( file ) )
    {
        number = 0;
    }
    pthread_mutex_unlock ( &mutex );
    return number;
}

uint64_t read_number (  )
{
    uint64_t number;
    fscanf ( file, "%llu", &number );
    //Si on est à la fin du fichier
    if ( feof ( file ) )
    {
        number = 0;
    }
    return number;
}

int close_file ( )
{
    fclose ( file );
    pthread_mutex_destroy ( &mutex );
}


/*
 int lire_nombre ( uint64_t *nombre, char * filePath, int reset )
 {
 FILE * file;
 
 file = fopen ( filePath , "r" );
 
 if ( reset )
 {
 seek_cur = 0;
 }
 
 fseek ( file, seek_cur, SEEK_SET );  // seek to the current number of the file
 
 char buf;
 int i = 0;
 
 if ( file == NULL )
 {
 perror ("Error opening file");
 return 1;
 }
 else
 {
 fscanf ( file, "%llu", nombre );
 seek_cur = ftell ( file );
 
 //Si on est à la fin du fichier
 if ( feof ( file ) )
 {
 return 1;
 }
 }
 
 return 0;
 }
 
 */