#include <equeue/_types.h>

#include <stdio.h>

void equeue_errstr(struct equeue_eitem *eitem, char *str, size_t size)
{
    snprintf(str, size, "%s:%zu, errno=%zu:%s",
            eitem->file, eitem->line, eitem->code, eitem->errstr(eitem->code));
}
