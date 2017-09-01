#include <equeue/_rqueue.h>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void rqueue_init(struct rqueue *q, struct rqueue_item *mem, size_t max_size)
{
    q->top_border = mem;
    q->bot_border = mem + max_size - 1;
    q->top = NULL;
    q->bot = NULL;
    q->size = 0;
    q->max_size = max_size;
}

void rqueue_push(struct rqueue *q, const char *err_space, 
                 const char *fn_name, size_t code,
                 const char * (*errstr)(size_t code))
{
    if (q->size == q->max_size)
        kill(getpid(), SIGABRT);

    if (q->size == 0) {
        q->top = q->top_border;
        q->bot = q->top_border;
    } else {
        q->bot += 1;
        if (q->bot > q->bot_border)
            q->bot = q->top_border;
    }

    q->bot->value.err_space = err_space;
    q->bot->value.fn_name = fn_name;
    q->bot->value.errstr = errstr;
    q->bot->value.code = code;

    q->size += 1;
}

struct equeue_eitem * rqueue_pop(struct rqueue *q)
{
    struct rqueue_item *top;

    if (q->size == 0)
        return NULL;

    top = q->top;
    q->size -= 1;

    if (q->size == 0) {
        q->top = NULL;
        q->bot = NULL;
    } else {
        q->top += 1;
        if (q->top > q->bot_border)
            q->top = q->top_border;
    }

    return &top->value;
}

struct equeue_eitem * rqueue_top(struct rqueue *q)
{
    if (q->size == 0)
        return NULL;
    return &q->top->value;
}

void rqueue_dump(struct rqueue *q)
{
    rqueue_dumpto(STDERR_FILENO, q);
}

void rqueue_dumpto(int fd, struct rqueue *q)
{
    struct equeue_eitem *item;

    for (; q->size > 0;) {
        item = rqueue_pop(q);
        dprintf(fd, "#%zu, %s:%s():%zu\n", q->size, item->err_space, 
                item->fn_name, item->code);
        dprintf(fd, "%s\n\n", item->errstr(item->code));
    }
}

size_t rqueue_size(struct rqueue *q)
{
    return q->size;
}

void rqueue_clear(struct rqueue *q)
{
    q->top = NULL;
    q->bot = NULL;
    q->size = 0;
}

void rqueue_free(struct rqueue *q)
{
}
