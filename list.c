#include "list.h"

static void list_add(tlist_head *new_node, tlist_head *prev, tlist_head *next){
    next->prev = new_node;
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
}

static void list_del(tlist_head *prev, tlist_head *next){
    next->prev = prev;
    prev->next = next;
}

void data_add_front(tlist_head *head, int key, double val){
    tdata *new_data = malloc(sizeof(tdata));

    if(new_data == NULL){
        printf("Ошибка выделения памяти!\n");
        return;
    }

    new_data->key = key;
    new_data->value = val;

    list_add(&new_data->list, head, head->next);

}

void data_add_end(tlist_head *head, int key, double val){
    tdata *new_data = malloc(sizeof(tdata));

    if(new_data == NULL){
        printf("Ошибка выделения памяти!\n");
        return;
    }
    new_data->key = key;
    new_data->value = val;

    list_add(&new_data->list, head->prev, head);

}

void data_delete(tlist_head *head, int key){
    tlist_head *curr;

    list_for_each(curr, head){
        tdata *item = container_of(curr, tdata, list);

        if(item->key == key){
            list_del(curr->prev, curr->next);
            free(item);
            printf("Элемент с ключом %d удален.\n", key);
            return;
        }
    }
    printf("Элемент с ключом %d не найден.\n", key);
}

double data_lookup(tlist_head *head, int key){
    tlist_head *curr;

    list_for_each(curr, head){
        tdata *item = container_of(curr, tdata, list);

        if(item->key == key)
            return item->value;
    }
    return -1.; // нет ключа 
}

void list_clear(tlist_head *head){
    tlist_head *curr = head->next;

    while (curr != head){
        tlist_head *next_node = curr->next;
        tdata *item = container_of(curr, tdata, list);
        free(item);
        curr = next_node;
    }

    head->next = head;
    head->prev = head;

    //printf("Список очищен.\n");
}

