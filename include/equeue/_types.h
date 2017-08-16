/*
NAME
====

    type - Shared types

DESCRIPTION
===========

    Types which share between module in internal library and with other
    library.

AUTHORS
=======

    Kevin Leptons <kevin.leptons@gmail.com>
*/

#ifndef __EQUEUE_TYPES_H__
#define __EQUEUE_TYPES_H__

#include <stdlib.h>

struct equeue_eitem
{
    const char *file;
    const char *fname;
    const char *(*errstr)(size_t code);
    size_t line;
    size_t code;
};

void equeue_errstr(struct equeue_eitem *eitem, char *str, size_t size);

#endif
