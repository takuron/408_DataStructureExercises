// 练习：带头结点循环双链表
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct DNode { int data; DNode *prior, *next; };
using DLinkList = DNode *;

// --- 函数声明与行为契约 ---
/** 创建头结点；空表时 prior、next 均指向头结点。 */
bool InitList(DLinkList &L);

/** 在位序 [1,长度+1] 插入，维护前驱后继双向链接；失败返回 false。 */
bool ListInsert(DLinkList L, int i, int e);

/** 删除第 i 个数据结点（不得删除头结点），维护双向链接并释放。 */
bool ListDelete(DLinkList L, int i, int &e);

/** 释放包括头结点在内的全部结点，L 置空；循环结构不得无限遍历。 */
void DestroyList(DLinkList &L);

// --- 参考实现 ---
bool InitList(DLinkList &L) {
    DNode *p = static_cast<DNode *>(malloc(sizeof(DNode)));
    if (!p) return false;
    p->prior = p->next = p;
    L = p;
    return true;
}

bool ListInsert(DLinkList L, int i, int e) {
    if (!L || i < 1) return false;
    DNode *prev = L;
    for (int j = 1; j < i; ++j) {
        if (prev->next == L) return false;
        prev = prev->next;
    }
    DNode *p = static_cast<DNode *>(malloc(sizeof(DNode)));
    if (!p) return false;
    *p = {e, prev, prev->next};
    if (prev->next) prev->next->prior = p;
    prev->next = p;
    return true;
}

bool ListDelete(DLinkList L, int i, int &e) {
    if (!L || i < 1) return false;
    DNode *prev = L;
    for (int j = 1; j < i; ++j) {
        if (prev->next == L) return false;
        prev = prev->next;
    }
    DNode *p = prev->next;
    if (p == L) return false;
    e = p->data;
    prev->next = p->next;
    if (p->next) p->next->prior = prev;
    free(p);
    return true;
}

void DestroyList(DLinkList &L) {
    if (!L) return;
    L->prior->next = nullptr;
    while (L) { DNode *p = L; L = L->next; free(p); }
}

// --- 测试入口 ---
int main() {
    printf("--- 带头结点循环双链表 ---\n");

    DLinkList L = nullptr; int e = -1;
    test(InitList(L));
    test(L && L->next == L && L->prior == L);

    test(ListInsert(L, 1, 10)); test(ListInsert(L, 2, 20));
    test(L && L->next && L->next->next && L->next->next->prior == L->next);
    test(!ListInsert(L, 0, 5)); test(!ListDelete(L, 3, e));
    test(ListDelete(L, 1, e) && e == 10);
    test(ListDelete(L, 1, e) && e == 20);
    test(!ListDelete(L, 1, e));
    test(L && L->next == L && L->prior == L);
    DestroyList(L); test(!L);
    return 0;
}
