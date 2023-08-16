#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    void *data;
    struct list *next;
    struct list *prev;
} list;

list* list_new(void *data);

void list_append(list *l, void *data);

void list_pop(list *l);

void list_prepend(list *l, void *data);

void list_insert(list *l, void *data, int index);

void list_remove(list *l, int index);

void list_destroy(list *l);

void list_print(list *l);

// ------

#define list_for_each(_e, _l) \
    for (list *_e = _l; _e != NULL; _e = _e->next)

#endif
