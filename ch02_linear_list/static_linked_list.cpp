// 练习：静态链表（游标实现，选练）
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
// 0 为头结点，1 为备用链表头；-1 表示链尾；可存 MAX_SIZE-2 个数据。
typedef struct Component {
    int data, next;
} Component;
typedef struct StaticList {
    Component node[MAX_SIZE];
} StaticList;

// --- 函数声明与行为契约 ---
/** 数据链为空；把下标 [2,MAX_SIZE) 连成备用链。 */
void InitList(StaticList &L);

/** 从备用链取一个槽，插入数据链第 i 位；非法位序或备用链空返回 false。 */
bool ListInsert(StaticList &L, int i, int e);

/** 摘除第 i 个数据结点并归还备用链；非法位序返回 false。 */
bool ListDelete(StaticList &L, int i, int &e);

/** 返回首个匹配元素的逻辑位序（非游标）；未找到返回 0。 */
int LocateElem(const StaticList &L, int e);

// --- 在此处编写实现 ---
void InitList(StaticList &L) {
    // TODO: 数据链为空；把下标 [2,MAX_SIZE) 连成备用链。
    (void)L;
}

bool ListInsert(StaticList &L, int i, int e) {
    // TODO: 从备用链取一个槽，插入数据链第 i 位；非法位序或备用链空返回 false。
    return false;
}

bool ListDelete(StaticList &L, int i, int &e) {
    // TODO: 摘除第 i 个数据结点并归还备用链；非法位序返回 false。
    return false;
}

int LocateElem(const StaticList &L, int e) {
    // TODO: 返回首个匹配元素的逻辑位序（非游标）；未找到返回 0。
    return 0;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
int main() {
    printf("--- 静态链表（游标实现，选练） ---\n");

    StaticList L{}; int e = -1; InitList(L);
    test(L.node[0].next == -1); test(!ListDelete(L,1,e));
    test(ListInsert(L,1,10)); test(ListInsert(L,2,20)); test(LocateElem(L,20) == 2);
    test(ListDelete(L,1,e) && e == 10); test(LocateElem(L,20) == 1);
    InitList(L);
    for (int i = 1; i <= MAX_SIZE-2; ++i) test(ListInsert(L,i,i));
    test(!ListInsert(L,1,999)); test(ListDelete(L,1,e));
    test(ListInsert(L,1,999)); test(LocateElem(L,999) == 1);
    return 0;
}
