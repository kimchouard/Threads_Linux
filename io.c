#include "io.h"

int init_print ( )
{
  if ( pthread_mutex_init( &mutex_print, NULL) != 0 )
    {
        printf("\nError while initializing the mutex\n");
        exit ( 0 );
    }
}

int end_print ( )
{
  pthread_mutex_destroy ( &mutex_print );
}

int print_safe ( uint64_t n, uint64_t *factors_tab, int factors_tab_size )
{
  int i;
  pthread_mutex_lock ( &mutex_print );
  printf ( "%llu : ", n );
  for ( i = 0 ; i < factors_tab_size ; i ++ )
  {
    printf ( "%llu ", factors_tab[i] ); 
  }
  printf ( "\n" );
  pthread_mutex_unlock ( &mutex_print );
}

int print_safe_number ( uint64_t n )
{
  pthread_mutex_lock ( &mutex_print );
  printf ( "%llu : ", n );
  pthread_mutex_unlock ( &mutex_print );
}
int print_safe_factor ( uint64_t n )
{
  pthread_mutex_lock ( &mutex_print );
  printf ( "%llu ", n );
  pthread_mutex_unlock ( &mutex_print );
}
int print_safe_eol ( )
{
  pthread_mutex_lock ( &mutex_print );
  printf ( "\n" );
  pthread_mutex_unlock ( &mutex_print );
}



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
