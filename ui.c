#include "ui.h"

void print_all(tlist_head *head){
    tlist_head *curr;
    int count = 0;

    printf("\n ==Состояние списка== \n");

    if(head->next == head)
        printf("Список пуст.\n");
    else
        list_for_each(curr, head){
            tdata *item = container_of(curr, tdata, list);
            printf("[%d] Ключ: %d, Значение: %.2f\n", count++, item->key, item->value);
        }

    printf("-----------------------\n");
}

void load_from_file(tlist_head *head,const char *filename){
    FILE *file = fopen(filename, "r");

    if(file == NULL){
        printf("Не удалось открыть файл '%s'. Проверьте, существует ли он.\n", filename);
        return;
    }

    int k;
    double v;
    int count = 0;

    while (fscanf(file, "%d %lf", &k, &v) == 2){
        data_add_end(head, k, v);
        count++;
    }

    fclose(file);
    printf("Успешно загружено %d элементов из файла '%s'.\n", count, filename);

}
// Экспериментальное исследование с усреднением (runs передается как аргумент)
/*void run_experiment(tlist_head *head, int runs) {
    if (runs <= 0) runs = 1;

    printf("\n--- Экспериментальное исследование (Усреднение по %d прогонам) ---\n", runs);
    printf("Кол-во элементов | Время data_add_end (мкс) | Время data_lookup (мс)\n");
    printf("-----------------------------------------------------------------\n");

    for (int n = 50000; n <= 500000; n += 50000) {
        double total_time_add    = 0.0;
        double total_time_lookup = 0.0;

        for (int r = 0; r < runs; r++) {
            list_clear(head);

            // Заполняем список до N элементов
            for (int i = 0; i < n; i++)
                data_add_end(head, rand(), (double)rand());

            // Замеряем один вызов add_end на уже заполненном списке
            clock_t start = clock();
            for (int i = 0; i < 1000; i++)
                data_add_end(head, rand(), (double)rand());
            clock_t end = clock();
            total_time_add += ((double)(end - start) / CLOCKS_PER_SEC) * 1e6 / 1000.0;

            // Замеряем lookup по несуществующему ключу (обход всего списка)
            start = clock();
            data_lookup(head, -1);
            end = clock();
            total_time_lookup += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }

        double avg_time_add    = total_time_add    / runs;
        double avg_time_lookup = total_time_lookup / runs;

        printf("%16d | %24.3f | %22.2f\n", n, avg_time_add, avg_time_lookup);
    }

    list_clear(head);
    printf("-----------------------------------------------------------------\n");
};*/

static double wtime(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

void run_experiment(tlist_head *head, int runs) {
    if (runs <= 0) runs = 1;

    printf("\n--- Экспериментальное исследование (Усреднение по %d прогонам) ---\n", runs);
    printf("%-18s | %-24s | %-20s\n",
           "Кол-во элементов", "Время 1 add_end (мс)", "Время 1 lookup (мс)");
    printf("--------------------------------------------------------------------\n");

    const int ADD_ITERS    = 10000;
    const int LOOKUP_ITERS = 10000;

    for (int n = 50000; n <= 500000; n += 50000) {
        double total_time_add    = 0.0;
        double total_time_lookup = 0.0;

        for (int r = 0; r < runs; r++) {
            list_clear(head);

            // Заполняем список до N элементов
            for (int i = 0; i < n; i++)
                data_add_end(head, i, (double)i);

            // Замеряем ADD_ITERS вызовов add_end, берём среднее
            double start = wtime();
            for (int i = 0; i < ADD_ITERS; i++)
                data_add_end(head, n + i, 0.0);
            total_time_add += (wtime() - start) / ADD_ITERS * 1000.0;

            // Замеряем LOOKUP_ITERS вызовов lookup, берём среднее
            start = wtime();
            for (int i = 0; i < LOOKUP_ITERS; i++)
                data_lookup(head, rand() % n);
            total_time_lookup += (wtime() - start) / LOOKUP_ITERS * 1000.0;
        }

        printf("%-18d | %-24.8f | %-20.8f\n",
               n,
               total_time_add    / runs,
               total_time_lookup / runs);
    }

    list_clear(head);
    printf("--------------------------------------------------------------------\n");
}