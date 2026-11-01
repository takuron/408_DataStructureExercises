// 练习：动态顺序表
// 参考答案：保留原练习契约和测试，可与 main 分支对照学习。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"

// --- 数据结构定义 ---
typedef struct SeqList {
    int *data;
    int length;
    int capacity;
} SeqList;

// --- 函数声明与行为契约 ---
/** 申请 capacity 个元素空间；capacity <= 0 或分配失败返回 false；成功后 length=0。 */
bool InitList(SeqList &L, int capacity);

/** 扩容并保留原元素；不缩容；非法容量或分配失败返回 false。 */
bool Reserve(SeqList &L, int capacity);

/** 在位序 [1,length+1] 插入；满时容量翻倍（先扩容）；非法位序返回 false。 */
bool ListInsert(SeqList &L, int i, int e);

/** 删除位序 [1,length] 的元素，由 e 带回；非法位序返回 false。 */
bool ListDelete(SeqList &L, int i, int &e);

/** 返回第一个匹配值的位序；未找到返回 0。 */
int LocateElem(const SeqList &L, int e);

/** 释放 data，指针置空，length 和 capacity 置零；允许重复销毁。 */
void DestroyList(SeqList &L);

// --- 参考实现 ---
bool InitList(SeqList &L, int capacity) {
    if (capacity <= 0) return false;
    int *data = static_cast<int *>(malloc(sizeof(int) * static_cast<size_t>(capacity)));
    if (!data) return false;
    L = {data, 0, capacity};
    return true;
}

bool Reserve(SeqList &L, int capacity) {
    if (capacity <= 0) return false;
    if (capacity <= L.capacity) return true;
    int *data = static_cast<int *>(realloc(L.data, sizeof(int) * static_cast<size_t>(capacity)));
    if (!data) return false;
    L.data = data;
    L.capacity = capacity;
    return true;
}

bool ListInsert(SeqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1 || !L.data) return false;
    if (L.length == L.capacity) {
        if (L.capacity > 2147483647 / 2 || !Reserve(L, L.capacity * 2)) return false;
    }
    for (int j = L.length; j >= i; --j) L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    ++L.length;
    return true;
}

bool ListDelete(SeqList &L, int i, int &e) {
    if (i < 1 || i > L.length) return false;
    e = L.data[i-1];
    for (int j = i; j < L.length; ++j) L.data[j-1] = L.data[j];
    --L.length;
    return true;
}

int LocateElem(const SeqList &L, int e) {
    for (int j = 0; j < L.length; ++j) if (L.data[j] == e) return j+1;
    return 0;
}

void DestroyList(SeqList &L) {
    free(L.data);
    L = {nullptr, 0, 0};
}

// --- 测试入口 ---
int main() {
    printf("--- 动态顺序表 ---\n");

    SeqList L{}; int e = -1;
    test(!InitList(L, 0));
    test(InitList(L, 2));
    test(ListInsert(L, 1, 10)); test(ListInsert(L, 2, 20));
    test(ListInsert(L, 2, 15));
    test(L.length == 3 && L.capacity >= 3);
    test(LocateElem(L, 15) == 2); test(LocateElem(L, 99) == 0);
    test(!Reserve(L, -1));
    test(!ListInsert(L, 0, 7));
    test(ListDelete(L, 2, e) && e == 15);
    test(!ListDelete(L, 9, e));
    DestroyList(L); DestroyList(L);
    test(L.data == nullptr && L.length == 0 && L.capacity == 0);
    return 0;
}
