#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <equeue/equeue.h>

#define ABC_ERR_SIZE 3
#define ABC_ENONE 0
#define ABC_E001 1
#define ABC_E002 2 // and more error codes...

const char *ABC_ERR_STRS[ABC_ERR_SIZE] = {
    "No Error",
    "First Error Code",
    "Second Error Code"
};

const char * abc_errstr(size_t code)
{
    if (code >= ABC_ERR_SIZE)
        return "Unknow Error";
    else
        return ABC_ERR_STRS[code];
}

#define abcerr_push(code) equeue_push(EQUEUE_ERR_SPACE, code, abc_errstr)

#define ERR_STR_SIZE 1024

int do_sys_wrong(void)
{
    equeue_spush(ENOMEM);
    return -1;
}

int do_wrong(void)
{
    if (do_sys_wrong()) {
        abcerr_push(ABC_E001);
        return -1;
    }
    return 0;
}

int do_other_wrong(void)
{
    if (do_wrong()) {
        abcerr_push(ABC_E002);
        return -1;
    }

    return 0;
}

int do_unknow(void)
{
    if (do_other_wrong()) {
        abcerr_push(ABC_ENONE);
        return -1;
    }

    return 0;
}

int do_smt(void)
{
    if (do_unknow()) {
        equeue_emit();
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (do_smt())
        equeue_dump();

    return EXIT_SUCCESS;
}
