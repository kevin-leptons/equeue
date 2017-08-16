#include <stdlib.h>
#include <stdio.h>

#include <equeue/equeue.h>

#define ABC_ERR_SIZE 3
#define ABC_ENO 0
#define ABC_EXX 1
#define ABC_EYY 2 // and more error codes...

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

EQUEUE_DEFINE(abcerr, abc_errstr)  // define abcerr_push(size_t code)

#define ERR_STR_SIZE 1024

int main(int argc, char *argv[])
{
    struct equeue_eitem *eitem;
    char errstr[ERR_STR_SIZE];

    abcerr_push(ABC_ENO);
    abcerr_push(ABC_EXX);
    abcerr_push(ABC_EYY);
    abcerr_push(1024);              // invalid error code

    printf("size of SEQ: %zu\n", equeue_size());
    for (; equeue_size() > 0;) {
        eitem = equeue_pop();
        equeue_errstr(eitem, errstr, ERR_STR_SIZE);
        printf("Error: %s\n", errstr);
    }
    printf("size of SEQ: %zu\n", equeue_size());

    return EXIT_SUCCESS;
}
