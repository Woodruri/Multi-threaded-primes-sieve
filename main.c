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


#ifndef DEF_NUM
# define DEF_NUM 10240
#endif // DEF_DIM

#ifndef MAX_NUM
# define MAX_NUM UINT32_MAX
#endif // MAX_DIM

#ifndef DEF_THREADS
# define DEF_THREADS 1
#endif // DEF_THREADS

#ifndef MAX_THREADS
# define MAX_THREADS 30
#endif // MAX_THREADS


#ifndef FALSE
# define FALSE 0
#endif // FALSE

#ifndef TRUE
# define TRUE 1
#endif // TRUE


#define OPTIONS "t:u:hv"


static uint32_t upper = DEF_NUM;
static int num_threads = 1;
static BitBlock_t *bit_array = NULL;
static int is_verbose = FALSE;
//make the bit array here or smth idk

void init_bit_array(void);
int get_next_spot(void);
void output_array(void);
void* thread_manager(void *);


//0 is prime, 1 is composite
void
init_bit_array(void)
{
    int i = -1;
    int no_blocks = ((upper / 32) + 1);

    bit_array = (BitBlock_t*)calloc(no_blocks, sizeof(BitBlock_t) );
    for (i = 0 ; i < no_blocks ; i++){
        bit_array[i].bits = 0;
        pthread_mutex_init(&bit_array[i].mutex, NULL);
    }
}

int 
get_next_spot(void)
{
    static int next_spot = 0;
    static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int cur_spot = 0;

    pthread_mutex_lock(&lock);
    cur_spot = next_spot++;
    pthread_mutex_unlock(&lock);

    return cur_spot;
}

void* 
thread_manager(void *arg){

    int tid = (int)tid;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t mask = 0x1;
    int start_pos = 3 + (tid * 2);
    uint32_t upper_sqrt = sqrt(upper);


    for (i = start_pos ; i <= upper_sqrt ; i += (num_threads * 2)){

        for (j = i * 2 ; j <= upper ; j += i) {
            uint32_t index = (j / 32);
            uint32_t bit = (j % 32);
            mask = 1 << bit;

            //lock the thing 
            pthread_mutex_lock(&bit_array[index].mutex);
            
            //setting the mask bit to 1
            bit_array[index].bits |= mask;

            //unlock the hting
            pthread_mutex_unlock(&bit_array[index].mutex);
        }
    }

    pthread_exit(EXIT_SUCCESS);

}

void 
output_array(void)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t mask = 0x0;
    uint32_t mask_limit = 0x1 << 31;


    for (i = 0 ; i <= upper; i += (num_threads * 2)){

        for (mask = 1 ; mask <= mask_limit ; mask << 1) {
            uint32_t index = (j / 32);
            uint32_t bit = (j % 32);
            mask = 1 << bit;

            //lock the thing 
            pthread_mutex_lock(&bit_array[index].mutex);
            
            //setting the mask bit to 1
            bit_array[index].bits |= mask;

            //unlock the hting
            pthread_mutex_unlock(&bit_array[index].mutex);
        }
    }
}

/*void 
op_primes()
{
    FILE *op = NULL;
    int i = -1;
    int no_blocks = ((upper/32)+1);
    uint32_t mask = 0x1;


#define FILE_NAME "primesMT.txt"

    op = fopen(FILE_NAME, "w");
    if (op == NULL){
        perror("could not open file: " FILE_NAME);
        exit(17);
    }

    for (i = 0 ; i < no_blocks ; i++){
        for ( mask = 1 ; mask <= sizeof(uint32_t) ; mask << 1){
            if (mask & bit_array[i].bits){
                fprintf(op, "%d ", );
                fprintf(op, "\n");
            }
        }

    }
    fclose(op);
}*/


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
                    if (num_threads > MAX_THREADS){
                    num_threads = MAX_THREADS;
                    }
                    else if (num_threads < DEF_THREADS){
                        num_threads = DEF_THREADS;
                    }
                    break;

                case 'u':
                    //upper bounds option
                    upper = ((uint32_t)atoi(optarg));
                    if (upper > MAX_NUM){
                        upper = MAX_NUM;
                    }
                    if (upper < DEF_NUM){
                        upper = DEF_NUM;
                    }
                    break;

                case 'h':
                    //put a help page thing in here
                    printf("%s: -t # -d #\n", argv[0]);
                    printf("\t-t #: number of threads\n");
                    printf("\t-d #: upper limit requested\n");
                    exit(0);
                    break;

                case 'v':
                    is_verbose = TRUE;
                    // figure out how to make a verbose output here
                    break;

                default:  /* ? */
                    exit(EXIT_FAILURE);
                    break;
            }

        }   
    }

    // allocate memory for threads
    threads = malloc(num_threads * sizeof(pthread_t));

    // allocate memory for BitBlock_t array
    // initialize the data members of BitBlock_t array
    init_bit_array();

    // create all the threads
    for (tid = 0 ; tid < num_threads ; tid++){
        pthread_create(&threads[tid], NULL, thread_manager, (void *) tid);
    }

    // join with all the threads
    for (tid = 0 ; tid < num_threads ; tid++){
        pthread_join(threads[tid], NULL);
    }
    free(threads);

    // output all prime numbers
    output_array();

    // deallocate memory

    // replace with
    pthread_exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}