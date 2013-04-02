#ifndef IO_H
#define IO_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

static FILE *file;

static pthread_mutex_t mutex;
static pthread_mutex_t mutex_print;


int init_print ( );
int end_print ( );

int print_safe ( uint64_t n, uint64_t *factors_tab, int factors_tab_size );
int print_safe_number ( uint64_t n );
int print_safe_factor ( uint64_t n );
int print_safe_eol ( );


int open_file ( char * filePath );
void reset_file ( );
int close_file ( );

uint64_t read_number_safe (  );
uint64_t read_number (  );

#endif
