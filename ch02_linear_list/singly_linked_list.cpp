// 练习：带头结点单链表
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
struct LNode { int data; LNode *next; };
using LinkList = LNode *;

// --- 函数声明与行为契约 ---
/** 创建头结点，next=nullptr；分配失败返回 false。 */
bool InitList(LinkList &L);

/** i=0 返回头结点；i>=1 返回第 i 个数据结点；非法或越界返回 nullptr。 */
LNode *GetElem(LinkList L, int i);

/** 返回第一个值等于 e 的数据结点；未找到返回 nullptr。 */
LNode *LocateElem(LinkList L, int e);

/** 在位序 [1,长度+1] 插入；空指针、非法位序、分配失败返回 false。 */
bool ListInsert(LinkList L, int i, int e);

/** 删除第 i 个数据结点并释放，由 e 带回；失败返回 false。 */
bool ListDelete(LinkList L, int i, int &e);

/** 原地逆置数据结点；头结点保持不变；时间 O(n)、额外空间 O(1)。 */
void ReverseList(LinkList L);

/** 释放全部数据结点和头结点，L 置空；允许空表。 */
void DestroyList(LinkList &L);

// --- 参考实现 ---
bool InitList(LinkList &L) {
    LNode *p = static_cast<LNode *>(malloc(sizeof(LNode)));
    if (!p) return false;
    p->next = nullptr;
    L = p;
    return true;
}

LNode *GetElem(LinkList L, int i) {
    if (i < 0) return nullptr;
    while (L && i > 0) { L = L->next; --i; }
    return L;
}

LNode *LocateElem(LinkList L, int e) {
    for (LNode *p = L ? L->next : nullptr; p; p = p->next)
        if (p->data == e) return p;
    return nullptr;
}

bool ListInsert(LinkList L, int i, int e) {
    if (i < 1) return false;
    LNode *prev = GetElem(L, i-1);
    if (!prev) return false;
    LNode *p = static_cast<LNode *>(malloc(sizeof(LNode)));
    if (!p) return false;
    *p = {e, prev->next};
    prev->next = p;
    return true;
}

bool ListDelete(LinkList L, int i, int &e) {
    if (i < 1) return false;
    LNode *prev = GetElem(L, i-1);
    if (!prev || !prev->next) return false;
    LNode *p = prev->next;
    e = p->data;
    prev->next = p->next;
    free(p);
    return true;
}

void ReverseList(LinkList L) {
    if (!L) return;
    LNode *p = L->next;
    L->next = nullptr;
    while (p) {
        LNode *next = p->next;
        p->next = L->next;
        L->next = p;
        p = next;
    }
}

void DestroyList(LinkList &L) {
    while (L) { LNode *p = L; L = L->next; free(p); }
}

// --- 测试入口 ---
int main() {
    printf("--- 带头结点单链表 ---\n");

    LinkList L = nullptr; int e = -1;
    test(InitList(L)); test(GetElem(L, 0) == L && L != nullptr);
    test(ListInsert(L, 1, 10)); test(ListInsert(L, 2, 20));
    test(ListInsert(L, 2, 15));
    LNode *p = GetElem(L, 2); test(p && p->data == 15);
    test(LocateElem(L, 99) == nullptr); test(!ListInsert(L, 0, 1));
    ReverseList(L); p = GetElem(L, 1); test(p && p->data == 20);
    test(ListDelete(L, 2, e) && e == 15); test(!ListDelete(L, 5, e));
    DestroyList(L); test(L == nullptr); DestroyList(L);
    return 0;
}
