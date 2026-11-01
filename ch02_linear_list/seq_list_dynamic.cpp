// 练习：动态顺序表
// 只提供契约、桩函数和测试；请自行完成 TODO。
// 失败操作不得改变原结构或输出参数；动态申请的空间需在销毁时释放。
#include "common.h"
#include <cstdlib>

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

// --- 在此处编写实现 ---
bool InitList(SeqList &L, int capacity) {
    // TODO: 申请 capacity 个元素空间；capacity <= 0 或分配失败返回 false；成功后 length=0。
    if(capacity<=0) return false;
    L.length = 0;
    L.data = (int*)malloc(sizeof(int)*capacity);
    L.capacity = capacity;
    return true;
}

bool Reserve(SeqList &L, int capacity) {
    // TODO: 扩容并保留原元素；不缩容；非法容量或分配失败返回 false。
    if(capacity<=L.capacity)return false;

    int *newdata = (int*)malloc(sizeof(int)*capacity);
    for(int i =0;i<L.length;i++){
        newdata[i] = L.data[i];
    }
    free(L.data);
    L.data = newdata;
    L.capacity = capacity;
    return true;
}

bool ListInsert(SeqList &L, int i, int e) {
    // TODO: 在位序 [1,length+1] 插入；满时容量翻倍（先扩容）；非法位序返回 false。
    if(i<1||i>L.length+1) return false;
    if(L.length+1>L.capacity) {
        if(!Reserve(L, L.capacity*2)) return false;
    }

    for(int j = L.length-1; j>=i-1 ; j--)
        L.data[j+1] = L.data[j];

    L.data[i-1] = e;
    L.length++;
    return true;
}

bool ListDelete(SeqList &L, int i, int &e) {
    // TODO: 删除位序 [1,length] 的元素，由 e 带回；非法位序返回 false。
    if(i<1||i>L.length) return false;

    e = L.data[i-1];
    for(int j = i-1;j<L.length-1;j++)
        L.data[j] = L.data[j+1];
    L.length --;
    return true;

}

int LocateElem(const SeqList &L, int e) {
    // TODO: 返回第一个匹配值的位序；未找到返回 0。
    for(int i =0;i<L.length;i++)
        if(L.data[i]==e)return i+1;
    return 0;
}

void DestroyList(SeqList &L) {
    // TODO: 释放 data，指针置空，length 和 capacity 置零；允许重复销毁。
    free(L.data);
    L.data = nullptr;
    L.capacity = 0;
    L.length =0;
}

// --- 测试入口：未实现时出现 FAIL 是正常现象 ---
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
