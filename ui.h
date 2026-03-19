#ifndef UI_H
#define UI_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void print_all(tlist_head *head);
void load_from_file(tlist_head *head,const char *filename);
void run_experiment(tlist_head *head, int runs);
#endif