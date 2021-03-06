#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static int
get_policy(char p, int *policy)
{
    switch (p) {
        case 'f': *policy = SCHED_FIFO;     return 1;
        case 'r': *policy = SCHED_RR;       return 1;
        case 'b': *policy = SCHED_BATCH;    return 1;
        case 'o': *policy = SCHED_OTHER;    return 1;
        default:  return 0;
    }
}

int main(){

    int rtn, policy;
    pthread_t thread;
    struct sched_param param;

    // select policies
    get_policy('b', &policy);
    param.sched_priority = strtol("0", NULL, 0);

    rtn = pthread_setschedparam(pthread_self(), policy, &param);
    if (rtn != 0)
        handle_error_en(rtn, "pthread_setschedparam");

    // fork mutliple processes
    for(int i=0; i<3; i++){
        fork();
    }

    while(1){
        sleep(1);
    };

    exit(EXIT_SUCCESS);
}
