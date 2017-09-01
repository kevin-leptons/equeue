/*
This program shows you simple ways to use equeue:
    - Define Error Space
    - Push Error Code into Shared Error Queue
    - Dumpe Shared Error Queue

For more manual, see "man 3 equeue".
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <equeue/equeue.h>

/*
START: Define your error space, includes:
    - Error Space Name
    - Error Codes
    - Error Strings correspond with Error Codes
    - Error String function which converts Error Code to Error String
    - Error Pushing function which push Error Code into Shared Error Queue
*/

// error space name
const char LIBNAME_ERR_SPACE[] = "lib-name";

// error codes
#define LIBNAME_E001 1
#define LIBNAME_E002 2
#define LIBNAME_E003 3

// error string function
#define LIBNAME_ERR_SIZE 3
const char *LIBNAME_ERR_STRS[LIBNAME_ERR_SIZE] = {
    "First Error",
    "Second Error",
    "Third Error"
};
const char LIBNAME_EUNKNOW_STR[] = "Unkown Error";
const char *libname_errstr(size_t code)
{
    if (code == 0 || code > LIBNAME_ERR_SIZE)
        return LIBNAME_EUNKNOW_STR;
    else
        return LIBNAME_ERR_STRS[code - 1];
}

// error pushing function
#define libname_epush(code) \
    equeue_push(LIBNAME_ERR_SPACE, code, libname_errstr)
// END: Define your error space

// cause system error
int do_sys_wrong(void)
{
    equeue_spush(ENOMEM);
    return -1;
}

// handle for system error, cause library error
int do_wrong(void)
{
    if (do_sys_wrong()) {
        libname_epush(LIBNAME_E001);
        return -1;
    }
    return 0;
}

// handle for library error , cause other library error
int do_other_wrong(void)
{
    if (do_wrong()) {
        libname_epush(LIBNAME_E002);
        return -1;
    }
    return 0;
}

// do not hanlde for error, emit to up caller
int do_smt(void)
{
    if (do_other_wrong()) {
        equeue_emit();
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (do_smt()) {
        equeue_dump();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
