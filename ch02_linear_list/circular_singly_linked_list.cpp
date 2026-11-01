// 练习：带头结点循环单链表
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct CNode { int data; CNode *next; };
using CList = CNode *;

// --- 函数声明与行为契约 ---
/** 申请头结点，next 指向自身；分配失败返回 false。 */
bool InitList(CList &L);

/** 在位序 [1,长度+1] 插入；遍历结束标志为回到头结点，不能用 nullptr 判断表尾。 */
bool ListInsert(CList L, int i, int e);

/** 删除并释放第 i 个数据结点；非法位序返回 false；不得删除头结点。 */
bool ListDelete(CList L, int i, int &e);

/** 返回数据结点数量；未初始化时返回 0。 */
int Length(CList L);

/** 释放所有结点并置空；空表、单元素表也应正确处理。 */
void DestroyList(CList &L);

// --- 参考实现 ---
bool InitList(CList &L) {
    CNode *p = static_cast<CNode *>(malloc(sizeof(CNode)));
    if (!p) return false;
    p->next = p;
    L = p;
    return true;
}

bool ListInsert(CList L, int i, int e) {
    if (!L || i < 1) return false;
    CNode *prev = L;
    for (int j = 1; j < i; ++j) {
        if (prev->next == L) return false;
        prev = prev->next;
    }
    CNode *p = static_cast<CNode *>(malloc(sizeof(CNode)));
    if (!p) return false;
    *p = {e, prev->next};
    prev->next = p;
    return true;
}

bool ListDelete(CList L, int i, int &e) {
    if (!L || i < 1) return false;
    CNode *prev = L;
    for (int j = 1; j < i; ++j) {
        if (prev->next == L) return false;
        prev = prev->next;
    }
    CNode *p = prev->next;
    if (p == L) return false;
    e = p->data;
    prev->next = p->next;
    free(p);
    return true;
}

int Length(CList L) {
    int n = 0;
    if (L) for (CNode *p = L->next; p != L; p = p->next) ++n;
    return n;
}

void DestroyList(CList &L) {
    if (!L) return;
    CNode *p = L->next;
    while (p != L) { CNode *next = p->next; free(p); p = next; }
    free(L);
    L = nullptr;
}

// --- 测试入口 ---
int main() {
    printf("--- 带头结点循环单链表 ---\n");

    CList L = nullptr; int e = -1;
    test(InitList(L)); test(L && L->next == L); test(Length(L) == 0);
    test(ListInsert(L,1,10)); test(ListInsert(L,2,20)); test(Length(L) == 2);
    test(L && L->next && L->next->next && L->next->next->next == L);
    test(!ListInsert(L,4,30)); test(!ListDelete(L,0,e));
    test(ListDelete(L,2,e) && e == 20); test(ListDelete(L,1,e) && e == 10);
    test(L && L->next == L); test(!ListDelete(L,1,e));
    DestroyList(L); test(!L);
    return 0;
}
