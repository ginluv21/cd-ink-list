#include "list.h"
#include "ui.h"

int main(void) {
    LIST_HEAD(my_list);
    tlist_head *ptr = &my_list;
    int choice;

    srand(time(NULL)); // Инициализация генератора для эксперимента

    do {
        printf("\n====== ГЛАВНОЕ МЕНЮ ======\n");
        printf("1. Добавить элементы в конец\n");
        printf("2. Добавить элементы в начало\n");
        printf("3. Поиск элемента по ключу\n");
        printf("4. Удалить элемент по ключу\n");
        printf("5. Вывести весь список\n");
        printf("6. Загрузить данные из файла\n");
        printf("7. Очистить список\n");
        printf("8. Провести эксперимент\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        // Защита от ввода букв вместо цифр
        if (scanf("%d", &choice) != 1) {
            printf("[ОШИБКА] Введите число.\n");
            while(getchar() != '\n'); // чистка буфера
            continue;
        }

        int k, n;
        double v;
        char filename[256];

        switch (choice) {
            case 1:
                printf("Сколько элементов добавить? ");
                if (scanf("%d", &n) == 1 && n > 0) {
                    for (int i = 0; i < n; i++) {
                        printf("Элемент %d (введите ключ и значение через пробел): ", i + 1);
                        scanf("%d %lf", &k, &v);
                        data_add_end(ptr, k, v);
                    }
                } else {
                    printf("[ОШИБКА] Неверный ввод количества.\n");
                    while(getchar() != '\n');
                }
                break;
            case 2:
                printf("Сколько элементов добавить в начало? ");
                if (scanf("%d", &n) == 1 && n > 0) {
                    for (int i = 0; i < n; i++) {
                        printf("Элемент %d (введите ключ и значение через пробел): ", i + 1);
                        scanf("%d %lf", &k, &v);
                        data_add_front(ptr, k, v);
                    }
                } else {
                    printf("[ОШИБКА] Неверный ввод количества.\n");
                    while(getchar() != '\n');
                }
                break;
            case 3:
                printf("Введите ключ для поиска: ");
                scanf("%d", &k);
                v = data_lookup(ptr, k);
                if (v != -1.0) printf("Найдено значение: %.2f\n", v);
                else printf("Ключ не найден.\n");
                break;
            case 4:
                printf("Введите ключ для удаления: ");
                scanf("%d", &k);
                data_delete(ptr, k);
                break;
            case 5:
                print_all(ptr);
                break;
            case 6:
                printf("Введите имя файла (например, data.txt): ");
                scanf("%255s", filename);
                load_from_file(ptr, filename);
                break;
            case 7:
                list_clear(ptr);
                printf("Список очищен.\n");
                break;
            case 8:
                run_experiment(ptr, 1);
                break;
            case 0:
                list_clear(ptr);
                printf("Память очищена. Выход.\n");
                break;
            default:
                printf("Неверный пункт меню.\n");
        }
    } while (choice != 0);

    return 0;
}