#include <stdio.h>
#include <time.h>
#include "h/BPlusTree.h"

int main() {
    printf("Hello, World!\n");
    clock_t c1 = clock();

    // 初始化
    BPlusTree T = b_init();

    int keys[] = {10, 15, 21, 37, 44, 51, 59, 85, 91, 100, 97, 72, 63};
    int i = sizeof(keys) / sizeof(keys[0]);
    while (i > 0) {
        // 插入
        T = b_insert(T, keys[--i]);
    }

    // 遍历
    b_travel(T);

    // 查找指定 key 所在叶子节点
    KeyType key = 91;
    BPlusTree P = b_find(T, key);
    if (P != NULL) {
        printf("\n\nkey: %d 所在叶子节点信息为：", key);
        for (int j = 0; j < P->keyNum; ++j) {
            printf("%d", P->keys[j]);
            if (j < P->keyNum - 1) {
                printf(",");
            }
        }
        printf("\n\n");
    }

    // 销毁
    b_destroy(T);

    clock_t c2 = clock();
    printf("\n用时： %lu秒\n", (c2 - c1) / CLOCKS_PER_SEC);

    return 0;
}