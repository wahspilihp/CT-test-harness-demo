#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
int (*old_rand)() = &rand;

#include <stdio.h>
#include "test.h"


unsigned call_counter = 0;
FILE *choices = NULL;

void blow_up(){
    fprintf(stderr, "\n\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n");
    perror("The error was");
    fprintf(stderr, "Maybe you've called rand() too many times for that sample\n");
    fprintf(stderr, "I give up, goodbye!\n");
    exit(1);
}

int test_rand_impl(){
    char choice;


    if(!choices) {
        char *filename = getenv("STEAL_DEAL_CHOICES");
        fprintf(stderr, "Using test_rand with the file %s\n", filename);

        if (!filename) {
        	fprintf(stderr, "No input file specified, using the real RNG\n");
        	fprintf(stderr, "set the environment variable STEAL_DEAL_CHOICES\n");
            test_rand = old_rand;
            return old_rand();
        }
        choices = fopen(filename, "r");
    }
    do {
        if(1 != fscanf(choices, " %c", &choice)) {
            //If we don't read a single character, something went wrong
            blow_up();
        }
    } while(choice != 's' && choice != 'd');
    return choice == 'd';
}


int (*test_rand)() = &test_rand_impl;

// int test_rand(char *choices, size_t max_calls){
//  if (call_counter >= max_calls)
//      blow_up();
//  printf("call_counter = %u\n", call_counter);
//  return choices[call_counter++];
// }
