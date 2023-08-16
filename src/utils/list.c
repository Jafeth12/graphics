#include "list.h"

list* list_new(void *data) {
    list *l = malloc(sizeof(list));
    l->data = data;
    l->next = NULL;
    l->prev = NULL;

    return l;
}

void list_append(list *l, void *data) {
    list *new = list_new(data);
    list *last = l;

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new;
    new->prev = last;
}

void list_prepend(list *l, void *data) {
    list *new = list_new(data);
    list *first = l;

    while (first->prev != NULL) {
        first = first->prev;
    }

    first->prev = new;
    new->next = first;
}

void list_pop(list *l) {
    list *last = l;

    while (last->next != NULL) {
        last = last->next;
    }

    last->prev->next = NULL;
    free(last);
}

// void list_insert(list *l, void *data, int index) {
//     list *new = list_new(data);
//     list *current = l;
//
//     for (int i = 0; i < index; i++) {
//         current = current->next;
//     }
//
//     new->next = current->next;
//     new->prev = current;
//     current->next = new;
// }

void list_remove(list *l, int index) {
    list *current = l;

    for (int i = 0; i < index; i++) {
        if (current == NULL) return;
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
}

void list_destroy(list *l) {
    list *current = l;
    list *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void list_print(list *l) {
    list *current = l;

    while (current != NULL) {
        printf("%p\n", current->data);
        current = current->next;
    }
}
