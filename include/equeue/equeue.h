/*
NAME
====

    equeue - Error Queue.

COMPLEXITY
==========

    fn                              best    notes
    --------------------------------------------------------------------------
    equeue_push()                   O(1)
    equeue_spush()                  O(1)
    equeue_cspush()                 O(1)
    equeue_emit()                   O(1)
    equeue_pop()                    O(1)
    equeue_top()                    O(1)
    equeue_dump()                   O(n)
    equeue_dumpto()                 O(n)
    equeue_clear()                  O(1)
    equeue_size()                   O(1)
    equeue_eitem_errstr()           O(1)    from <equeue/_type.h>

DESCRIPTION
===========

    Public intefaces for this library.

AUTHORS
=======

    Kevin Leptons <kevin.leptons@gmail.com>
*/

#ifndef __EQUEUE_EQUEUE_H__
#define __EQUEUE_EQUEUE_H__

#include <errno.h>

#include <equeue/_types.h>
#include <equeue/_rqueue.h>

#define EQUEUE_RQUEUE_MAX_SIZE 1024

#define EQUEUE_ENONE 0
#define EQUEUE_EEMIT 1

extern const char EQUEUE_ERR_SPACE[];
extern const char EQUEUE_SERR_SPACE[];
extern struct rqueue_item shared_rqueue_items[EQUEUE_RQUEUE_MAX_SIZE] ;
extern struct rqueue shared_rqueue;

const char *equeue_errstr(size_t code);
const char *equeue_sys_errstr(size_t code);

#define equeue_push(err_space, code, errstr_fn) \
    rqueue_push(&shared_rqueue, err_space, __FUNCTION__, code, errstr_fn)
#define equeue_emit() \
    rqueue_push(&shared_rqueue, EQUEUE_ERR_SPACE, __FUNCTION__, \
                EQUEUE_EEMIT, equeue_errstr)
#define equeue_spush(code) \
    rqueue_push(&shared_rqueue, EQUEUE_SERR_SPACE, __FUNCTION__, code, \
                equeue_sys_errstr)
#define equeue_cspush() equeue_spush(errno)
#define equeue_pop() rqueue_pop(&shared_rqueue)
#define equeue_top() rqueue_top(&shared_rqueue)
#define equeue_size() rqueue_size(&shared_rqueue)
#define equeue_clear() rqueue_clear(&shared_rqueue)
#define equeue_dump() rqueue_dump(&shared_rqueue)
#define equeue_dumpto(fd) rqueue_dumpto(fd, &shared_rqueue)

#endif
