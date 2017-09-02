#include <equeue/equeue.h>

#include <errno.h>
#include <string.h>

const char EQUEUE_ERR_SPACE[] = "equeue";
const char EQUEUE_SERR_SPACE[] = "system";

#define EQUEUE_ERROR_SIZE 2
#define EQUEUE_EUNKNOW_STR "Unknow Error"
const char *EQUEUE_ERROR_STRS[EQUEUE_ERROR_SIZE] = {
    "No Error",
    "Emit Error To Caller"
};

struct rqueue_item shared_rqueue_items[EQUEUE_RQUEUE_MAX_SIZE];
struct rqueue shared_rqueue = {
    shared_rqueue_items,                                    // top_border
    shared_rqueue_items + EQUEUE_RQUEUE_MAX_SIZE - 1,       // bot_border
    NULL, NULL,                                             // top, bot
    0, EQUEUE_RQUEUE_MAX_SIZE                               // size, max_size
};

const char *equeue_errstr(size_t code)
{
    if (code >= EQUEUE_ERROR_SIZE)
        return EQUEUE_EUNKNOW_STR;
    else
        return EQUEUE_ERROR_STRS[code];
}

const char *equeue_sys_errstr(size_t code)
{
    return strerror(code);
}
