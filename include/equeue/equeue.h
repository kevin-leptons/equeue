/*
NAME
====

    equeue - Error Queue.

COMPLEXITY
==========

    fn                              best
    ==========================================
    <prefix>_push()                 O(1)
    equeue_pop()                    O(1)
    equeue_top()                    O(1)
    equeue_size()                   O(1)
    equeue_clear()                  O(1)
    equeue_errstr()                 O(n)        // from <equeue/_type.h>

DESCRIPTION
===========

    Public intefaces for this library.

AUTHORS
=======

    Kevin Leptons <kevin.leptons@gmail.com>
*/

#ifndef __EQUEUE_EQUEUE_H__
#define __EQUEUE_EQUEUE_H__

#include <equeue/_types.h>
#include <equeue/_rqueue.h>

#define EQUEUE_RQUEUE_MAX_SIZE 1024

extern struct rqueue_item shared_rqueue_items[EQUEUE_RQUEUE_MAX_SIZE] ;
extern struct rqueue shared_rqueue;

#define EQUEUE_DECLARE(prefix, errstr_fn) \
    void prefix##_push(size_t code);

#define EQUEUE_DEFINE(prefix, errstr_fn) \
    void prefix##_push(size_t code) { \
        rqueue_push(&shared_rqueue, __FILE__, __LINE__, __FUNCTION__, \
                    errstr_fn, code); \
    }

#define equeue_pop() rqueue_pop(&shared_rqueue)
#define equeue_top() rqueue_top(&shared_rqueue)
#define equeue_size() rqueue_size(&shared_rqueue)
#define equeue_clear() rqueue_clear(&shared_rqueue)

#endif
