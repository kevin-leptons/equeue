/*
NAME
====

    rqueue - Ring Queue

COMPLEXITY
==========

    fn                              best
    ==========================================
    rqueue_init()                   O(1)
    rqueue_push()                   O(1)
    rqueue_pop()                    O(1)
    rqueue_top()                    O(1)
    rqueue_size()                   O(1)
    rqueue_clear()                  O(1)
    rqueue_free()                   O(1)

DESCRIPTION
===========

    Ring Queue is queue which implements by ring array to store 
    "struct equeue_eitem".

AUTHORS
=======

    Kevin Leptons <kevin.leptons@gmail.com>
*/

#ifndef __EQUEUE_RQUEUE__
#define __EQUEUE_RQUEUE__

#include <stdlib.h>

#include <equeue/_types.h>

struct rqueue_item
{
    struct equeue_eitem value;
    struct requeue_item *next;
};

struct rqueue
{
    struct rqueue_item *top_border;
    struct rqueue_item *bot_border;
    struct rqueue_item *top;
    struct rqueue_item *bot;
    size_t size;
    size_t max_size;
};

void rqueue_init(struct rqueue *q, struct rqueue_item *mem, size_t max_size);
void rqueue_push(struct rqueue *q, const char *err_space, 
                 const char *fn_name, size_t code,
                 const char * (*errstr)(size_t code));
struct equeue_eitem * rqueue_pop(struct rqueue *q);
struct equeue_eitem * rqueue_top(struct rqueue *q);
void rqueue_dump(struct rqueue *q);
void rqueue_dumpto(int fd, struct rqueue *q);
size_t rqueue_size(struct rqueue *q);
void rqueue_clear(struct rqueue *q);
void rqueue_free(struct rqueue *q);

#endif
