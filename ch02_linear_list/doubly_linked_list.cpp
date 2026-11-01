// 练习：带头结点双链表
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct DNode { int data; DNode *prior, *next; };
using DLinkList = DNode *;

// --- 函数声明与行为契约 ---
/** 创建头结点；空表时 prior、next 均为空。 */
bool InitList(DLinkList &L);

/** 在位序 [1,长度+1] 插入，维护前驱后继双向链接；失败返回 false。 */
bool ListInsert(DLinkList L, int i, int e);

/** 删除第 i 个数据结点（不得删除头结点），维护双向链接并释放。 */
bool ListDelete(DLinkList L, int i, int &e);

/** 释放包括头结点在内的全部结点，L 置空；循环结构不得无限遍历。 */
void DestroyList(DLinkList &L);

// --- 在此处编写实现 ---
bool InitList(DLinkList &L) {
    // TODO: 创建头结点；空表时 prior、next 均为空。
    return false;
}

bool ListInsert(DLinkList L, int i, int e) {
    // TODO: 在位序 [1,长度+1] 插入，维护前驱后继双向链接；失败返回 false。
    return false;
}

bool ListDelete(DLinkList L, int i, int &e) {
    // TODO: 删除第 i 个数据结点（不得删除头结点），维护双向链接并释放。
    return false;
}

void DestroyList(DLinkList &L) {
    // TODO: 释放包括头结点在内的全部结点，L 置空；循环结构不得无限遍历。
    (void)L;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 带头结点双链表 ---\n");

    DLinkList L = nullptr; int e = -1;
    test(InitList(L));
    test(L && !L->next && !L->prior);

    test(ListInsert(L, 1, 10)); test(ListInsert(L, 2, 20));
    test(L && L->next && L->next->next && L->next->next->prior == L->next);
    test(!ListInsert(L, 0, 5)); test(!ListDelete(L, 3, e));
    test(ListDelete(L, 1, e) && e == 10);
    test(ListDelete(L, 1, e) && e == 20);
    test(!ListDelete(L, 1, e));
    test(L && !L->next);
    DestroyList(L); test(!L);
    return 0;
}
