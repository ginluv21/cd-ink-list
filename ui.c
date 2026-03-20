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
void run_experiment(tlist_head *head, int runs) {
    if (runs <= 0) runs = 1; // Защита: если передали бред, делаем хотя бы 1 прогон

    printf("\n--- Экспериментальное исследование (Усреднение по %d прогонам) ---\n", runs);
    printf("Кол-во элементов | Время data_add_end (мс) | Время data_lookup (мс)\n");
    printf("-----------------------------------------------------------------\n");

    // Цикл от 50 000 до 500 000 с шагом 50 000
    for (int n = 50000; n <= 500000; n += 50000) {
        double total_time_add = 0.0;
        double total_time_lookup = 0.0;

        for (int r = 0; r < runs; r++) {
            list_clear(head); 
            clock_t start, end;

            start = clock(); 
            for (int i = 0; i < n; i++) {
                data_add_end(head, rand(), (double)rand()); 
            }
            end = clock(); 
            total_time_add += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

            start = clock();
            data_lookup(head, -1); 
            end = clock();
            total_time_lookup += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        }
        
        double avg_time_add = total_time_add / runs;
        double avg_time_lookup = total_time_lookup / runs;

        printf("%16d | %23.2f | %22.2f\n", n, avg_time_add, avg_time_lookup);
    }
    
    list_clear(head); 
    printf("-----------------------------------------------------------------\n");
}

