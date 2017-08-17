#include <equeue/equeue.h>

struct rqueue_item shared_rqueue_items[EQUEUE_RQUEUE_MAX_SIZE];
struct rqueue shared_rqueue = {
    shared_rqueue_items,                                    // top_border
    shared_rqueue_items + EQUEUE_RQUEUE_MAX_SIZE - 1,       // bot_border
    NULL, NULL,                                             // top, bot
    0, EQUEUE_RQUEUE_MAX_SIZE                               // size, max_size
};
