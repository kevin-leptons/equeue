#include <equeue/_types.h>

#include <stdio.h>

void equeue_eitem_errstr(struct equeue_eitem *eitem, char *str, size_t size)
{
    snprintf(str, size, "%s:%s():%zu\n%s\n",
             eitem->err_space, eitem->fn_name, eitem->code, 
             eitem->errstr(eitem->code));
}
