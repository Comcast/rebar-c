#include <stdlib.h>
#include <string.h>
#include "test_queue.h"
#include "../src/queue.h"
#include "../src/rebar-xxd.h"


void create_queue(void)
{
    queue_t *q1 = init_queue();
    queue_t *q2 = init_queue();
    
    CU_ASSERT (q1 != NULL);
    CU_ASSERT (q2 != NULL);
    CU_ASSERT (q2 != q1);
    
    delete_queue(q1);
    delete_queue(q2);
}

#define NUMBER_OF_ELEMENTS 8
#define SIZE_OF_DATA 32
void do_the_works(void)
{
    int element;
    queue_t *q = init_queue();
    
    for (element = 0; element < NUMBER_OF_ELEMENTS; element++) {
        char *data = (char *) malloc(sizeof(char) * SIZE_OF_DATA);
        sprintf(data, "Element %d in queue", element);
        printf("push(%s, q)\n", data);
        push(data, q);
    }
 
    for (element = 0; element < NUMBER_OF_ELEMENTS; element++) {
        void *data = pop (q);
        printf("pop() element %d: %s\n", element, (char *) data);
        free(data);
    }
    
    for (element = 0; element < NUMBER_OF_ELEMENTS; element++) {
        char *data = (char *) malloc(sizeof(char) * SIZE_OF_DATA);
        sprintf(data, "Element %d in queue", element);
        printf("push(%s, q)\n", data);
        push(data, q);
    }
    
    queue_print(q, SIZE_OF_DATA);

    void *queue_data = peek(q);
    char test_data[SIZE_OF_DATA];
    
    rebar_xxd( queue_data, SIZE_OF_DATA, 80, true );  
    element = 0;
    sprintf(test_data, "Element %d in queue", element);
    CU_ASSERT (0 == memcmp(test_data, queue_data, strlen(queue_data)));    

    queue_data = pop(q);
    
    CU_ASSERT(NULL != queue_data);
    element = 0;
    sprintf(test_data, "Element %d in queue", element);
    CU_ASSERT (0 == memcmp(test_data, queue_data, strlen(queue_data)));
    
    free(queue_data);
    
     for (element = 1; element < NUMBER_OF_ELEMENTS; element++) {
        queue_data = pop(q);
        sprintf(test_data, "Element %d in queue", element);
        printf("Element being removed %s\n", test_data);
        CU_ASSERT (0 == memcmp(test_data, queue_data, strlen(queue_data)));
        free(queue_data);
    }

    delete_queue(q);
}



void add_queue_tests(CU_pSuite *suite)
{
    CU_add_test(*suite, "create_queue", create_queue);
    CU_add_test(*suite, "do_the_works", do_the_works);
}


