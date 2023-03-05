#pragma once

//bitblock struct
typedef struct BitBlock_s {
    uint32_t bits;
    pthread_mutex_t mutex;
} BitBlock_t;



//funcs
