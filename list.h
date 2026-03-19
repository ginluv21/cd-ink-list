#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// узел списка (только связи)
typedef struct list_head {
    struct list_head *next;
    struct list_head *prev;
} tlist_head;

// структура с данными
typedef struct data {
    int key;
    double value;
    tlist_head list; // Встроенный узел списка
} tdata;

// исправленный container_of (упрощенная версия без typeof для лучшей совместимости)
// просто берем указатель ptr, приводим его к char* (чтобы считать в байтах)
// и вычитаем смещение поля member внутри структуры type.
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

//инициализация (тут всё верно, адрес самой переменной)
#define LIST_HEAD_INIT(name) { &(name), &(name) }

// исправленный LIST_HEAD (используем правильное имя типа tlist_head)
#define LIST_HEAD(name) \
    tlist_head name = LIST_HEAD_INIT(name)

// удобный цикл для обхода (тут всё отлично)
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)


void data_add_front(tlist_head *head, int key, double val);
void data_add_end(tlist_head *head, int key, double val);
void data_delete(tlist_head *head, int key);
void list_clear(tlist_head *head);
double data_lookup(tlist_head *head, int key);

#endif