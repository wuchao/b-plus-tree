//
// BPlusTree.c
// Created on 2019/9/1.
//

#include "../h/BPlusTree.h"

static KeyType UNAVAILABLE = INT_MIN;

/**
 * 生成节点并初始化
 * @return
 */
static BPlusTree b_malloc_node() {
    BPlusTree NewNode = malloc(sizeof(BPlusNode));
    if (NewNode == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < M + 1; i++) {
        NewNode->keys[i] = UNAVAILABLE;
        NewNode->children[i] = NULL;
    }

    // 实际插入的子节点个数
    NewNode->keyNum = 0;
    NewNode->next = NULL;

    return NewNode;
}

/**
 * 初始化 B+ 树
 * @return
 */
extern BPlusTree b_init() {
    /**
     * 创建根结点
     */
    return b_malloc_node();
}

/**
 * 查找最左子节点
 * @param P
 * @return
 */
static BPlusTree find_left_most(BPlusTree P) {
    BPlusTree left = P;

    while (left != NULL && (left = left->children[0]) != NULL) {
    }

    return left;
}

/**
 * 查找最右子节点
 * @param P
 * @return
 */
static BPlusTree find_right_most(BPlusTree P) {
    BPlusTree right = P;

    while (right != NULL && (right = right->children[right->keyNum - 1]) != NULL) {
    }

    return right;
}


/**
 * 寻找一个兄弟节点，其存储的关键字个数未满，否则返回 NULL
 * @param Parent
 * @param i
 * @return
 */
static BPlusTree find_available_sibling(BPlusTree Parent, int i) {
    BPlusTree sibling = NULL;
    int Limit = M;

    if (i == 0) {
        if (Parent->children[1]->keyNum < Limit) {
            sibling = Parent->children[1];
        }
    } else if (Parent->children[i - 1]->keyNum < Limit) {
        sibling = Parent->children[i - 1];
    } else if (i + 1 < Parent->keyNum && Parent->children[i + 1]->keyNum < Limit) {
        sibling = Parent->children[i + 1];
    }

    return sibling;
}


/**
 * 查找兄弟节点，其关键字数大于 M/2 （兄弟节点位置大于 M/2）;没有返回 NULL
 * @param Parent
 * @param i
 * @param j
 * @return
 */
static BPlusTree find_sibling_key_num_greater_than_M_2(BPlusTree Parent, int i, int *j) {
    int Limit = LIMIT_M_2;
    BPlusTree Sibling = NULL;

    if (i == 0) {
        if (Parent->children[1]->keyNum > Limit) {
            Sibling = Parent->children[1];
            *j = 1;
        }
    } else {
        if (Parent->children[i - 1]->keyNum > Limit) {
            Sibling = Parent->children[i - 1];
            *j = i - 1;
        } else if (i + 1 < Parent->keyNum && Parent->children[i + 1]->keyNum > Limit) {
            Sibling = Parent->children[i + 1];
            *j = i + 1;
        }
    }

    return Sibling;
}

/**
 * 当要对 X 插入 key 的时候，i 是 X 在 Parent 的位置，j 是 key 要插入的位置
   当要对 Parent 插入 X 节点的时候，i 是要插入的位置，key 和 j 的值没有用
 * @param isKey
 * @param Parent
 * @param X
 * @param key
 * @param i
 * @param j
 * @return
 */
static BPlusTree insert_element(int isKey, BPlusTree Parent, BPlusTree X, KeyType key, int i, int j) {
    int k;

    if (isKey) {
        /* 插入 key */

        k = X->keyNum - 1;
        while (k >= j) {
            X->keys[k + 1] = X->keys[k];
            k--;
        }

        X->keys[j] = key;

        if (Parent != NULL) {
            Parent->keys[i] = X->keys[0];
        }

        X->keyNum++;

    } else {
        /* 插入节点 */

        /* 对树叶节点进行连接 */
        if (X->children[0] == NULL) {
            if (i > 0) {
                Parent->children[i - 1]->next = X;
            }
            X->next = Parent->children[i];
        }

        k = Parent->keyNum - 1;
        while (k >= i) {
            Parent->children[k + 1] = Parent->children[k];
            Parent->keys[k + 1] = Parent->keys[k];
            k--;
        }
        Parent->keys[i] = X->keys[0];
        Parent->children[i] = X;

        Parent->keyNum++;

    }

    return X;
}

static BPlusTree remove_element(int isKey, BPlusTree Parent, BPlusTree X, int i, int j) {

    int k, Limit;

    if (isKey) {
        Limit = X->keyNum;
        /* 删除key */
        k = j + 1;
        while (k < Limit) {
            X->keys[k - 1] = X->keys[k];
            k++;
        }

        X->keys[X->keyNum - 1] = UNAVAILABLE;

        Parent->keys[i] = X->keys[0];

        X->keyNum--;
    } else {
        /* 删除节点 */

        /* 修改树叶节点的链接 */
        if (X->children[0] == NULL && i > 0) {
            Parent->children[i - 1]->next = Parent->children[i + 1];
        }
        Limit = Parent->keyNum;
        k = i + 1;
        while (k < Limit) {
            Parent->children[k - 1] = Parent->children[k];
            Parent->keys[k - 1] = Parent->keys[k];
            k++;
        }

        Parent->children[Parent->keyNum - 1] = NULL;
        Parent->keys[Parent->keyNum - 1] = UNAVAILABLE;

        Parent->keyNum--;

    }
    return X;
}

/* Src和Dst是两个相邻的节点，i是Src在Parent中的位置；
 将Src的元素移动到Dst中 ,n是移动元素的个数*/
static BPlusTree MoveElement(BPlusTree Src, BPlusTree Dst, BPlusTree Parent, int i, int n) {
    KeyType TmpKey;
    BPlusTree Child;
    int j, SrcInFront;

    SrcInFront = 0;

    if (Src->keys[0] < Dst->keys[0])
        SrcInFront = 1;

    j = 0;
    /* 节点Src在Dst前面 */
    if (SrcInFront) {
        if (Src->children[0] != NULL) {
            while (j < n) {
                Child = Src->children[Src->keyNum - 1];
                remove_element(0, Src, Child, Src->keyNum - 1, UNAVAILABLE);
                insert_element(0, Dst, Child, UNAVAILABLE, 0, UNAVAILABLE);
                j++;
            }
        } else {
            while (j < n) {
                TmpKey = Src->keys[Src->keyNum - 1];
                remove_element(1, Parent, Src, i, Src->keyNum - 1);
                insert_element(1, Parent, Dst, TmpKey, i + 1, 0);
                j++;
            }

        }

        Parent->keys[i + 1] = Dst->keys[0];
        /* 将树叶节点重新连接 */
        if (Src->keyNum > 0)
            find_right_most(Src)->next = find_left_most(Dst);

    } else {
        if (Src->children[0] != NULL) {
            while (j < n) {
                Child = Src->children[0];
                remove_element(0, Src, Child, 0, UNAVAILABLE);
                insert_element(0, Dst, Child, UNAVAILABLE, Dst->keyNum, UNAVAILABLE);
                j++;
            }

        } else {
            while (j < n) {
                TmpKey = Src->keys[0];
                remove_element(1, Parent, Src, i, 0);
                insert_element(1, Parent, Dst, TmpKey, i - 1, Dst->keyNum);
                j++;
            }

        }

        Parent->keys[i] = Src->keys[0];
        if (Src->keyNum > 0)
            find_right_most(Dst)->next = find_left_most(Src);

    }

    return Parent;
}

static BPlusTree split_node(BPlusTree Parent, BPlusTree X, int i) {
    int j, k, Limit;
    BPlusTree NewNode;

    NewNode = b_malloc_node();

    k = 0;
    j = X->keyNum / 2;
    Limit = X->keyNum;
    while (j < Limit) {
        if (X->children[0] != NULL) {
            NewNode->children[k] = X->children[j];
            X->children[j] = NULL;
        }
        NewNode->keys[k] = X->keys[j];
        X->keys[j] = UNAVAILABLE;
        NewNode->keyNum++;
        X->keyNum--;
        j++;
        k++;
    }

    if (Parent != NULL)
        insert_element(0, Parent, NewNode, UNAVAILABLE, i + 1, UNAVAILABLE);
    else {
        /* 如果是X是根，那么创建新的根并返回 */
        Parent = b_malloc_node();
        insert_element(0, Parent, X, UNAVAILABLE, 0, UNAVAILABLE);
        insert_element(0, Parent, NewNode, UNAVAILABLE, 1, UNAVAILABLE);

        return Parent;
    }

    return X;
}

/* 合并节点,X少于M/2关键字，S有大于或等于M/2个关键字*/
static BPlusTree MergeNode(BPlusTree Parent, BPlusTree X, BPlusTree S, int i) {
    int Limit;

    /* S的关键字数目大于M/2 */
    if (S->keyNum > LIMIT_M_2) {
        /* 从S中移动一个元素到X中 */
        MoveElement(S, X, Parent, i, 1);
    } else {
        /* 将X全部元素移动到S中，并把X删除 */
        Limit = X->keyNum;
        MoveElement(X, S, Parent, i, Limit);
        remove_element(0, Parent, X, i, UNAVAILABLE);

        free(X);
        X = NULL;
    }

    return Parent;
}

/**
 * 递归插入
 * @param T
 * @param Key
 * @param i
 * @param Parent
 * @return
 */
static BPlusTree insert_recursively(BPlusTree T, KeyType key, int i, BPlusTree Parent) {
    BPlusTree Sibling;
    int j = 0, Limit = M;

    /* 查找分支 */
    while (j < T->keyNum && key >= T->keys[j]) {
        /* 重复值不插入 */
        if (key == T->keys[j]) {
            return T;
        }
        j++;
    }

    if (j != 0 && T->children[0] != NULL) {
        j--;
    }

    if (T->children[0] == NULL) { // 树叶
        T = insert_element(1, Parent, T, key, i, j);
    } else { // 内部节点
        T->children[j] = insert_recursively(T->children[j], key, j, T);
    }

    /* 调整节点 */
    if (T->keyNum > Limit) {
        /* 根 */
        if (Parent == NULL) {
            /* 分裂节点 */
            T = split_node(Parent, T, i);
        } else {
            Sibling = find_available_sibling(Parent, i);
            if (Sibling != NULL) {
                /* 将T的一个元素（Key或者Child）移动的Sibing中 */
                MoveElement(T, Sibling, Parent, i, 1);
            } else {
                /* 分裂节点 */
                T = split_node(Parent, T, i);
            }
        }

    }

    if (Parent != NULL)
        Parent->keys[i] = T->keys[0];


    return T;
}

/**
 * 插入
 * @param T
 * @param key
 * @return
 */
extern BPlusTree b_insert(BPlusTree T, KeyType key) {
    return insert_recursively(T, key, 0, NULL);
}

static BPlusTree remove_recursively(BPlusTree T, KeyType Key, int i, BPlusTree Parent) {

    int j, NeedAdjust;
    BPlusTree Sibling, Tmp;

    Sibling = NULL;

    /* 查找分支 */
    j = 0;
    while (j < T->keyNum && Key >= T->keys[j]) {
        if (Key == T->keys[j])
            break;
        j++;
    }

    if (T->children[0] == NULL) {
        /* 没找到 */
        if (Key != T->keys[j] || j == T->keyNum)
            return T;
    } else if (j == T->keyNum || Key < T->keys[j]) j--;



    /* 树叶 */
    if (T->children[0] == NULL) {
        T = remove_element(1, Parent, T, i, j);
    } else {
        T->children[j] = remove_recursively(T->children[j], Key, j, T);
    }

    NeedAdjust = 0;
    /* 树的根或者是一片树叶，或者其儿子数在2到M之间 */
    if (Parent == NULL && T->children[0] != NULL && T->keyNum < 2)
        NeedAdjust = 1;
        /* 除根外，所有非树叶节点的儿子数在[M/2]到M之间。(符号[]表示向上取整) */
    else if (Parent != NULL && T->children[0] != NULL && T->keyNum < LIMIT_M_2)
        NeedAdjust = 1;
        /* （非根）树叶中关键字的个数也在[M/2]和M之间 */
    else if (Parent != NULL && T->children[0] == NULL && T->keyNum < LIMIT_M_2)
        NeedAdjust = 1;

    /* 调整节点 */
    if (NeedAdjust) {
        /* 根 */
        if (Parent == NULL) {
            if (T->children[0] != NULL && T->keyNum < 2) {
                Tmp = T;
                T = T->children[0];
                free(Tmp);
                return T;
            }

        } else {
            /* 查找兄弟节点，其关键字数目大于M/2 */
            Sibling = find_sibling_key_num_greater_than_M_2(Parent, i, &j);
            if (Sibling != NULL) {
                MoveElement(Sibling, T, Parent, j, 1);
            } else {
                if (i == 0)
                    Sibling = Parent->children[1];
                else
                    Sibling = Parent->children[i - 1];

                Parent = MergeNode(Parent, T, Sibling, i);
                T = Parent->children[i];
            }
        }

    }


    return T;
}

/* 删除 */
extern BPlusTree b_remove(BPlusTree T, KeyType Key) {
    return remove_recursively(T, Key, 0, NULL);
}

/* 销毁 */
extern BPlusTree b_destroy(BPlusTree T) {
    int i, j;
    if (T != NULL) {
        i = 0;
        while (i < T->keyNum + 1) {
            b_destroy(T->children[i]);
            i++;
        }

        printf("Destroy:(");
        j = 0;
        while (j < T->keyNum)/*  T->keys[i] != UNAVAILABLE*/
            printf("%d:", T->keys[j++]);
        printf(") ");
        free(T);
        T = NULL;
    }

    return T;
}

static void travel_recursively(BPlusTree T, int Level) {
    int i;
    if (T != NULL) {
        printf("  ");
        printf("[Level:%d]-->", Level);
        printf("(");
        i = 0;
        while (i < T->keyNum)/*  T->keys[i] != UNAVAILABLE*/
            printf("%d:", T->keys[i++]);
        printf(")");

        Level++;

        i = 0;
        while (i <= T->keyNum) {
            travel_recursively(T->children[i], Level);
            i++;
        }


    }
}

/* 遍历 */
extern void b_travel(BPlusTree T) {
    travel_recursively(T, 0);
    printf("\n");
}

/* 遍历树叶节点的数据 */
extern void b_travel_data(BPlusTree T) {
    BPlusTree Tmp;
    int i;
    if (T == NULL)
        return;
    printf("All Data:");
    Tmp = T;
    while (Tmp->children[0] != NULL)
        Tmp = Tmp->children[0];
    /* 第一片树叶 */
    while (Tmp != NULL) {
        i = 0;
        while (i < Tmp->keyNum)
            printf(" %d", Tmp->keys[i++]);
        Tmp = Tmp->next;
    }
}