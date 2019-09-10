//
// main.c
// Created on 2019/9/1.
//

#include <stdio.h>
#include <time.h>
#include "../h/BPlusTree.h"

int main() {
    printf("Hello, World!\n");
    clock_t c1 = clock();

    BPlusTree T = b_init();
    int i;

    i = 10000000;
    while (i > 0) {
        T = b_insert(T, i--);
    }

    i = 5000001;
    while (i < 10000000) {
        T = b_insert(T, i++);
    }

    i = 10000000;
    while (i > 100) {
        T = b_remove(T, i--);
    }

    b_travel(T);
    b_destroy(T);

    clock_t c2 = clock();
    printf("\n用时： %lu秒\n", (c2 - c1) / CLOCKS_PER_SEC);

    return 0;
}