#include "list.h"

void print_all(tlist_head *head) {
    tlist_head *curr;
    int count = 0;
    printf("\n==Состояние списка==\n");
    if (head->next == head) {
        printf("Список пуст.\n");
    } else {
        list_for_each(curr, head) {
            tdata *item = container_of(curr, tdata, list);
            printf("[%d] Ключ: %d, Значение: %.2f\n", ++count, item->key, item->value);
        }
    }
    printf("------------------------\n");
}

int main() {
    LIST_HEAD(my_list);
    tlist_head *ptr = &my_list;
    print_all(ptr);

    printf("1. Добавляем элементы...\n");
    data_add_end(ptr, 10, 100.5);
    data_add_end(ptr, 20, 200.5);
    data_add_front(ptr, 5, 50.5); // Станет первым
    print_all(ptr);

    printf("\n2. Тестируем поиск (Lookup)...\n");
    double val = data_lookup(ptr, 20);
    if(val != -1.0)
        printf("Найден ключ 20, значение: %.2f\n", val);
    else
        printf("Ключ 20 не найден!\n");

    printf("\n3. Тестируем удаление (Delete ключ 10)...\n");
    data_delete(ptr, 10);
    print_all(ptr);

    printf("\n4. Проверка цикличности после удаления...\n");
    if(ptr->prev->next == ptr) 
        printf("Цикл в порядке!\n");

    printf("\n5. Полная очистка списка (Clear)...\n");
    list_clear(ptr);
    print_all(ptr);

    return 0;
}