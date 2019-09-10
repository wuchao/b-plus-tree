//
// BPlusTree.h
// Created on 2019/9/1.
//

#ifndef B_PLUS_TREE_BPLUSTREE_H
#define B_PLUS_TREE_BPLUSTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define M (4)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)

typedef int KeyType;
typedef struct _BPlusNode *BPlusTree;
typedef struct _BPlusNode {
    int keyNum;
    KeyType keys[M + 1];
    BPlusTree children[M + 1];
    BPlusTree next;
} BPlusNode;

/* 初始化 */
extern BPlusTree b_init();

/* 插入 */
extern BPlusTree b_insert(BPlusTree T, KeyType Key);

/* 删除 */
extern BPlusTree b_remove(BPlusTree T, KeyType Key);

/* 销毁 */
extern BPlusTree b_destroy(BPlusTree T);

/* 遍历节点 */
extern void b_travel(BPlusTree T);

/* 遍历树叶节点的数据 */
extern void b_travel_data(BPlusTree T);

#endif //B_PLUS_TREE_BPLUSTREE_H
