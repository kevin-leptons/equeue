#include <stdlib.h>
#include <stdio.h>

#include <equeue/_rqueue.h>

#define RQUEUE_MAX_SIZE 1024
#define ERRSTR_SIZE 1024

const char *sample_errstr(size_t code);

int main(int argc, char *argv[])
{
    struct rqueue q;
    struct rqueue_item mem[RQUEUE_MAX_SIZE];
    size_t values[RQUEUE_MAX_SIZE];
    char errstr[ERRSTR_SIZE];
    size_t i;
    struct equeue_eitem *item;

    for (i = 0; i < RQUEUE_MAX_SIZE; i++)
        values[i] = i;

    // push 1/2 of max size items
    rqueue_init(&q, mem, RQUEUE_MAX_SIZE);
    for (i = 0; i < RQUEUE_MAX_SIZE / 2; i++) {
        rqueue_push(&q, __FILE__, __LINE__, __FUNCTION__,
                    sample_errstr, values[i]);
    }

    // pop all
    for (; q.size > 0;) {
        item = rqueue_pop(&q);
        equeue_errstr(item, errstr, ERRSTR_SIZE);
        printf("%s\n", errstr);
    }

    // push of max size items
    for (i = 0; i < RQUEUE_MAX_SIZE; i++) {
        rqueue_push(&q, __FILE__, __LINE__, __FUNCTION__,
                    sample_errstr, values[i]);
    }

    // pop all
    for (; q.size > 0;) {
        item = rqueue_pop(&q);
        equeue_errstr(item, errstr, ERRSTR_SIZE);
        printf("%s\n", errstr);
    }

    return EXIT_SUCCESS;
}

const char *sample_errstr(size_t code)
{
    return "This is sample error string";
}
