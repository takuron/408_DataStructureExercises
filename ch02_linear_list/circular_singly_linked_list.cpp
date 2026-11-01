// 练习：带头结点循环单链表
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;
typedef CNode *CList;

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

// --- 在此处编写实现 ---
bool InitList(CList &L) {
    // TODO: 申请头结点，next 指向自身；分配失败返回 false。
    return false;
}

bool ListInsert(CList L, int i, int e) {
    // TODO: 在位序 [1,长度+1] 插入；遍历结束标志为回到头结点，不能用 nullptr 判断表尾。
    return false;
}

bool ListDelete(CList L, int i, int &e) {
    // TODO: 删除并释放第 i 个数据结点；非法位序返回 false；不得删除头结点。
    return false;
}

int Length(CList L) {
    // TODO: 返回数据结点数量；未初始化时返回 0。
    return 0;
}

void DestroyList(CList &L) {
    // TODO: 释放所有结点并置空；空表、单元素表也应正确处理。
    (void)L;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
