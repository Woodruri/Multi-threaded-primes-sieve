#pragma once

#include "primesMT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <pthread.h>
#include <values.h>
#include <math.h>
#include <stdint.h>

//bitblock struct
typedef struct BitBlock_s {
    uint32_t bits;
    pthread_mutex_t mutex;
} BitBlock_t;

#ifndef MAX_NUM
# define MAX_NUM UINT32_MAX
#endif // MAX_DIM

#ifndef DEF_NUM
# define DEF_NUM 10240
#endif // DEF_DIM

#ifndef FALSE
# define FALSE 0
#endif // FALSE

#ifndef TRUE
# define TRUE 1
#endif // TRUE


#define OPTIONS "t:u:hv"


static int num = DEF_NUM;
static int num_threads = 1;


int 
main( int argc, char *argv[] )
{
    //vars
    pthread_t *threads = NULL;
    long tid = 0;

    //inner workings
    {
        int opt = -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1){
            switch (opt){
                case 't':
                    //threads option
                    num_threads = atoi(optarg);
                    break;

                case 'u':
                    //upper bounds option
                    num = atoi(optarg);
                    break;

                case 'h':
                    //put a help page thing in here
                    break;

                case 'v':
                    // figure out how to make a verbose output here
                    break;

                default:  /* ? */
                    exit(EXIT_FAILURE);
                    break;
            }

        }   
    }

    // allocate memory for threads
    // allocate memory for BitBlock_t array

    // initialize the data members of BitBlock_t array

    // create all the threads

    // join with all the threads

    // output all prime numbers

    // deallocate memory

    // replace with
    // pthread_exit(EXIT_SUCCESS);
}
